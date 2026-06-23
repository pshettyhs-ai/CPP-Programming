# 🔷 OOP Interview Questions

> *Pavan Shetty H S — Deep OOP concept prep*

---

## Q1. Explain the difference between Abstraction and Encapsulation.

**Encapsulation** = bundling data + methods, hiding internal state  
**Abstraction** = hiding *implementation complexity*, exposing only *interface*

They work together but are distinct:
- Encapsulation is the *mechanism* (using private/public)
- Abstraction is the *design goal* (what you hide and why)

```cpp
// Encapsulation: data is private, controlled access
class BankAccount {
private:
    double balance;   // hidden
public:
    void deposit(double amount) { balance += amount; }  // controlled
};

// Abstraction: hide HOW payment processing works
class PaymentProcessor {
public:
    virtual void processPayment(double amount) = 0;  // just the interface
};
```

---

## Q2. What are the differences between early binding and late binding?

| | Early Binding | Late Binding |
|--|---------------|--------------|
| Also called | Static dispatch | Dynamic dispatch |
| Resolved at | Compile time | Runtime |
| Functions | Normal, overloaded | Virtual functions |
| Mechanism | Direct call | vtable lookup |
| Speed | Faster | Slightly slower (vtable overhead) |

```cpp
class Animal { public: void speak() { cout << "Animal"; } };          // early
class Dog : Animal { public: virtual void bark() { cout << "Woof"; } }; // late (virtual)
```

---

## Q3. Can we call a virtual function from a constructor?

**Yes, but it behaves unexpectedly.** During construction, virtual dispatch is *not* polymorphic — it calls the class currently being constructed's version, not the derived class.

```cpp
class Base {
public:
    Base() { init(); }  // calls Base::init(), NOT Derived::init()!
    virtual void init() { cout << "Base init"; }
};
class Derived : public Base {
public:
    void init() override { cout << "Derived init"; }
};

Derived d;  // prints "Base init" — may not be what you expect
```

**Guideline:** Avoid calling virtual functions in constructors/destructors.

---

## Q4. What is the difference between composition and inheritance?

**Inheritance:** "IS-A" relationship — `Dog IS-A Animal`  
**Composition:** "HAS-A" relationship — `Car HAS-A Engine`

```cpp
// Inheritance (IS-A)
class Animal { public: void breathe() {} };
class Dog : public Animal {};  // Dog IS-A Animal

// Composition (HAS-A)
class Engine { public: void start() {} };
class Car {
    Engine engine;  // Car HAS-A Engine
public:
    void drive() { engine.start(); }
};
```

**Prefer composition over inheritance** — leads to more flexible design, less tight coupling.

---

## Q5. What is multiple inheritance? What problems does it cause?

Multiple inheritance = deriving from more than one base class.

**Diamond problem:** When two parents share a grandparent, creating ambiguity:
```
     A
    / \
   B   C
    \ /
     D  ← D has TWO copies of A's members!
```

**Solution:** Virtual inheritance:
```cpp
class A { public: int x; };
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};  // only ONE copy of A
D d; d.x = 5;  // no ambiguity
```

---

## Q6. What is the vtable? How does runtime polymorphism work?

Each class with virtual functions gets a **vtable** — a compile-time array of function pointers.

```
Dog vtable:
  [0] → Dog::sound()     (overridden)
  [1] → Animal::eat()    (inherited, not overridden)

Animal* ptr = new Dog();
// ptr has a vptr (virtual pointer) pointing to Dog's vtable
ptr->sound();
// compiler: call *(ptr->vptr)[0]  → calls Dog::sound()
```

This lookup happens at runtime, enabling true polymorphism.

---

## Q7. What is RTTI (Run-Time Type Identification)?

RTTI lets you query the actual type of an object at runtime.

```cpp
Animal* ptr = new Dog();

// typeid — get type info
cout << typeid(*ptr).name() << endl;  // "Dog" (mangled)

// dynamic_cast — safe downcast
Dog* dogPtr = dynamic_cast<Dog*>(ptr);
if (dogPtr) {
    dogPtr->fetch();  // safe to use
} else {
    cout << "Not a dog!" << endl;
}
```

`dynamic_cast` returns `nullptr` (for pointers) or throws (for references) if the cast fails. Only works with polymorphic types (must have at least one virtual function).

---

## Q8. What is operator overloading? What operators cannot be overloaded?

**Cannot overload:** `::` (scope), `.` (member access), `.*` (member pointer), `?:` (ternary), `sizeof`, `typeid`

```cpp
class Complex {
    double real, imag;
public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& o) const {
        return Complex(real + o.real, imag + o.imag);
    }

    bool operator==(const Complex& o) const {
        return real == o.real && imag == o.imag;
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};
```

---

## Q9. What is the difference between `delete` and `delete[]`?

- `delete ptr` — for single object (`new T`)
- `delete[] ptr` — for arrays (`new T[]`)

Mixing them is **undefined behaviour**:
```cpp
int* single = new int(5);
delete single;    // correct

int* arr = new int[10];
delete[] arr;     // correct — calls destructor for each element
delete arr;       // WRONG! UB — only one destructor called
```

---

## Q10. What is a copy constructor? When is it called?

A copy constructor creates a new object from an existing one.

Called when:
1. `Student s2 = s1;` (copy initialisation)
2. `Student s2(s1);` (direct initialisation)
3. Passing object by value to a function
4. Returning object by value from a function (sometimes — compiler may use RVO)

```cpp
class Student {
    string* name;
public:
    Student(const Student& other) {  // copy constructor
        name = new string(*other.name);  // DEEP copy — own copy of string
    }
    // Without this: both objects share same pointer → double delete!
};
```
