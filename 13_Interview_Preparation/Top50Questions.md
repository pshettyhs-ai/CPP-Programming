# 🎯 Top 50 C++ Interview Questions

> *Pavan Shetty H S — Notes from mock interviews and research*
> *These are the questions I've been asked or expect to be asked*

---

## 🔴 CORE C++ CONCEPTS (Q1–Q15)

### Q1. What is the difference between C and C++?

| Feature | C | C++ |
|---------|---|-----|
| Paradigm | Procedural | Multi-paradigm (OOP + Procedural) |
| OOP | ❌ | ✅ |
| Classes | ❌ | ✅ |
| Namespaces | ❌ | ✅ |
| Function overloading | ❌ | ✅ |
| References | ❌ | ✅ |
| Templates | ❌ | ✅ |
| Exception handling | ❌ | ✅ |
| `new`/`delete` | ❌ (uses malloc/free) | ✅ |

---

### Q2. What are the 4 OOP pillars? Give examples.

**1. Encapsulation** — Bundling data and methods, hiding internals
```cpp
class BankAccount {
private:
    double balance;  // hidden
public:
    void deposit(double amount) { balance += amount; }  // controlled access
};
```

**2. Abstraction** — Hiding implementation details, showing only interface
```cpp
class Shape {
public:
    virtual double area() = 0;  // pure virtual — forces implementation
};
```

**3. Inheritance** — Deriving new class from existing class
```cpp
class Animal { public: virtual void speak() {} };
class Dog : public Animal { public: void speak() override { cout << "Woof"; } };
```

**4. Polymorphism** — Same interface, different behaviour
```cpp
Animal* a = new Dog();
a->speak();  // calls Dog::speak() — runtime polymorphism
```

---

### Q3. What is a virtual function? Why is it needed?

A virtual function enables **runtime polymorphism** via **dynamic dispatch**.

Without `virtual`, base class function is always called even through derived pointer:
```cpp
class Base  { public: void show() { cout << "Base";    } };
class Child : public Base { public: void show() { cout << "Child"; } };

Base* ptr = new Child();
ptr->show();  // WITHOUT virtual → "Base" (wrong!)
              // WITH    virtual → "Child" (correct!)
```

The compiler uses a **vtable** (virtual function table) — a table of function pointers. Each class with virtual functions has one. When you call a virtual function through a base pointer, C++ looks up the actual function in the vtable at runtime.

---

### Q4. What is the difference between `override` and `overload`?

| | Overloading | Overriding |
|--|-------------|------------|
| Location | Same class | Base + Derived class |
| Parameters | Different | Same |
| Dispatch | Compile-time | Runtime (with virtual) |
| Keyword | None | `override` (C++11) |

```cpp
// Overloading — same name, different params
int add(int a, int b);
double add(double a, double b);  // overloaded

// Overriding — same name + params, different class
class Base  { virtual void show(); };
class Child : Base { void show() override; };  // overridden
```

---

### Q5. What is a pure virtual function? What is an abstract class?

A **pure virtual function** has `= 0` and no body in the base class.  
A class with at least one pure virtual function is an **abstract class**.  
Abstract classes **cannot be instantiated** — they serve as interfaces.

```cpp
class Shape {
public:
    virtual double area() = 0;  // pure virtual
    virtual void display() = 0; // pure virtual
    // Cannot do: Shape s;  → compile error!
};

class Circle : public Shape {
    double r;
public:
    double area() override { return 3.14159 * r * r; }
    void display() override { cout << "Circle"; }
};
```

---

### Q6. What is the difference between `struct` and `class` in C++?

Only one difference: **default access specifier**.
- `struct` → members are `public` by default
- `class` → members are `private` by default

And for inheritance:
- `struct Base {}; struct Child : Base {}` → public inheritance by default
- `class Base {}; class Child : Base {}` → private inheritance by default

Convention: use `struct` for plain data holders (POD types), `class` for OOP with behaviour.

---

### Q7. Explain constructors. How many types are there?

A constructor initialises an object when it's created. Same name as class, no return type.

**Types:**
1. **Default constructor** — no parameters: `Student() {}`
2. **Parameterized** — takes arguments: `Student(string n, int r) {}`
3. **Copy constructor** — creates from another object: `Student(const Student& s) {}`
4. **Move constructor** (C++11) — steals resources: `Student(Student&& s) {}`
5. **Delegating constructor** (C++11) — calls another constructor

**Rule of Five (C++11):**  
If you define any of: destructor, copy constructor, copy assignment, move constructor, move assignment — define all five.

---

### Q8. What is a destructor? Why make it virtual?

Destructor cleans up resources when object is destroyed. Called automatically.

**Make it virtual** when you have base class pointers to derived objects:
```cpp
class Base { public: ~Base() {} };   // NOT virtual
class Child : public Base { public: ~Child() { delete[] data; } };

Base* ptr = new Child();
delete ptr;   // Only Base::~Base() called! Child::~Child() NEVER called → MEMORY LEAK!

// Fix: make Base destructor virtual
class Base { public: virtual ~Base() {} };
delete ptr;   // Now calls Child::~Child() first, then Base::~Base() → correct!
```

---

### Q9. What are smart pointers? Why use them?

Smart pointers are RAII wrappers that automatically manage heap memory.

| Type | Ownership | Use When |
|------|-----------|----------|
| `unique_ptr` | Single owner | Default — one clear owner |
| `shared_ptr` | Shared, ref-counted | Multiple owners needed |
| `weak_ptr` | Non-owning observer | Break circular references |

```cpp
// Bad (manual):
int* ptr = new int(42);
// ... (might forget to delete, might throw exception)
delete ptr;

// Good (smart):
auto ptr = make_unique<int>(42);
// Automatically deleted when ptr goes out of scope!
```

---

### Q10. What is a memory leak? How to detect and prevent it?

A memory leak occurs when dynamically allocated memory is never freed.

```cpp
void leaky() {
    int* data = new int[1000];
    // Forgot to: delete[] data;
    // 4000 bytes leaked every time leaky() is called!
}
```

**Detection tools:** Valgrind (Linux), AddressSanitizer (`-fsanitize=address`)

**Prevention:**
- Use smart pointers (eliminates 90% of leaks)
- Use RAII (Resource Acquisition Is Initialisation)
- Follow Rule of Five
- Prefer stack allocation over heap when possible

---

### Q11. What is the difference between `new`/`delete` and `malloc`/`free`?

| Feature | new/delete | malloc/free |
|---------|------------|-------------|
| Language | C++ | C |
| Constructor called | ✅ | ❌ |
| Destructor called | ✅ | ❌ |
| Type-safe | ✅ | ❌ (void*) |
| Overloadable | ✅ | ❌ |
| On failure | throws `bad_alloc` | returns NULL |

**Never mix them:** don't `free()` what you `new`'d, don't `delete` what you `malloc`'d.

---

### Q12. What are templates in C++?

Templates enable generic programming — write code once, work with any type.

```cpp
// Function template
template<typename T>
T getMax(T a, T b) { return (a > b) ? a : b; }

getMax(3, 7);          // T = int
getMax(3.14, 2.71);    // T = double
getMax(string("a"), string("b"));  // T = string

// Class template
template<typename T>
class Stack {
    vector<T> data;
public:
    void push(T val) { data.push_back(val); }
    T    top()       { return data.back(); }
};

Stack<int>    intStack;
Stack<string> strStack;
```

---

### Q13. What is RAII?

**Resource Acquisition Is Initialisation** — acquire resources in constructor, release in destructor.

Guarantees cleanup even if exceptions are thrown.

```cpp
class FileGuard {
    FILE* file;
public:
    FileGuard(const char* path) { file = fopen(path, "r"); }
    ~FileGuard()                { if (file) fclose(file); }  // auto-cleanup!
};

void process() {
    FileGuard guard("data.txt");   // opens file
    // ... do stuff (might throw)
    // guard's destructor ALWAYS runs, even if exception thrown
}   // file automatically closed here
```

---

### Q14. What is object slicing?

When a derived object is assigned to a base object (not pointer/reference), the derived-specific parts are "sliced off".

```cpp
class Animal { public: int legs; };
class Dog : public Animal { public: string breed; };

Dog dog; dog.legs = 4; dog.breed = "Husky";
Animal a = dog;   // sliced! a.breed doesn't exist
// a only has 'legs' — breed is lost

// Fix: use pointer or reference
Animal* ptr = &dog;   // no slicing — pointer still points to Dog
Animal& ref = dog;    // no slicing — reference to actual Dog
```

---

### Q15. What is the diamond problem?

Occurs in multiple inheritance when two parent classes share a common grandparent.

```
       Person
      /       \
  Father      Mother
      \       /
        Child
```

Without fix, `Child` has two copies of `Person`. Fix: **virtual inheritance**.

```cpp
class Person  { public: string name; };
class Father  : virtual public Person {};  // virtual!
class Mother  : virtual public Person {};  // virtual!
class Child   : public Father, public Mother {};

Child c;
c.name = "Pavan";  // No ambiguity — only one Person
```

---

## 🟡 POINTERS & MEMORY (Q16–Q25)

### Q16. What is a dangling pointer?
A pointer that points to memory that has been freed/deleted.
```cpp
int* ptr = new int(10);
delete ptr;
// ptr is now dangling! Accessing *ptr is undefined behaviour
ptr = nullptr;  // fix: always set to nullptr after delete
```

### Q17. What is a null pointer dereference?
Accessing memory through a null pointer — causes crash (segfault).
```cpp
int* ptr = nullptr;
cout << *ptr;  // CRASH — undefined behaviour
// Always check: if (ptr != nullptr) { ... }
```

### Q18. What is a void pointer?
A generic pointer that can hold address of any type. Must cast before dereferencing.
```cpp
void* vptr;
int x = 42;
vptr = &x;
cout << *(int*)vptr;  // must cast to correct type
```

### Q19. Difference between `*ptr++` and `(*ptr)++`?
- `*ptr++` — dereference `ptr`, then increment the pointer (address)
- `(*ptr)++` — dereference `ptr`, then increment the value at that address

### Q20. What is a reference vs a pointer?

| | Pointer | Reference |
|--|---------|-----------|
| Null value | Can be null | Cannot be null |
| Reassignable | Can point to different things | Always bound to same variable |
| Syntax | `*`, `->`, `&` | Same as normal variable |
| Memory | Has its own address | No separate address |
| Use for | Optional params, arrays | Aliases, pass-by-ref |

---

## 🟢 STL & ALGORITHMS (Q21–Q30)

### Q21. What is the STL?
Standard Template Library — a set of C++ template classes for common data structures and algorithms.

Three components:
1. **Containers** — store data (vector, list, map, set...)
2. **Iterators** — traverse containers
3. **Algorithms** — operate on containers (sort, find, transform...)

### Q22. When to use `vector` vs `list`?
- **vector**: need random access (`v[5]`), mostly add/remove at end, cache-friendly
- **list**: frequent insert/delete in middle, don't need random access

In practice: vector wins almost always due to cache performance, even for middle insertions.

### Q23. Difference between `map` and `unordered_map`?

| | `map` | `unordered_map` |
|--|-------|-----------------|
| Internal | Red-Black Tree | Hash Table |
| Order | Sorted by key | No order |
| Lookup | O(log n) | O(1) average |
| Use when | Need sorted keys | Need fastest lookup |

### Q24. What is the erase-remove idiom?
```cpp
// Remove all even numbers from vector
v.erase(remove_if(v.begin(), v.end(), [](int x){ return x%2 == 0; }), v.end());
```
`remove_if` moves matching elements to the end, returns iterator to "new end".  
`erase` then actually removes those elements.

### Q25. What does `auto` do in C++11?
Tells compiler to deduce the type at compile time (not runtime!).
```cpp
auto x = 42;                     // int
auto it = v.begin();             // vector<int>::iterator
auto [key, val] = *map.begin();  // structured binding (C++17)
```

---

## 🔵 MODERN C++ (Q31–Q40)

### Q31. What is a lambda expression?
An anonymous function defined inline.
```cpp
auto add = [](int a, int b) { return a + b; };
auto result = add(3, 4);  // 7

// With capture
int threshold = 5;
auto isAbove = [threshold](int x) { return x > threshold; };
```

### Q32. What is move semantics? What problem does it solve?
Move semantics avoids expensive deep copies when working with temporary objects.
Instead of copying all data, we "steal" (move) the internal resources.

```cpp
vector<int> big(1000000);  // 1M elements
auto copy  = big;           // COPY — duplicates all 1M elements (slow)
auto moved = move(big);     // MOVE — steals internal pointer (fast)
// big is now empty (moved-from state)
```

### Q33. What are rvalue references (`&&`)?
References that bind to temporary (rvalue) objects. Enable move semantics.
```cpp
void process(string&&  s) { /* s is an rvalue ref — can steal from it */ }
void process(string const& s) { /* s is an lvalue ref */ }

process(string("temp"));  // binds to rvalue overload
```

### Q34. What is `constexpr`?
Tells compiler to evaluate expression at compile time (if possible).
```cpp
constexpr int sq(int x) { return x * x; }
constexpr int val = sq(10);  // computed at compile time — no runtime cost
```

### Q35. What is `nullptr` vs `NULL` vs `0`?
- `NULL` — C macro, expands to `0` or `0L` — integer type, no type safety
- `0` — integer literal, can cause ambiguity in overloaded functions
- `nullptr` — C++11, has type `nullptr_t`, type-safe, preferred

```cpp
void f(int);   void f(int*);
f(NULL);     // calls f(int)! Ambiguous/wrong
f(nullptr);  // calls f(int*) — correct
```

### Q36. What is `std::optional` (C++17)?
Represents a value that may or may not be present. Avoids null pointer and sentinel values.
```cpp
optional<string> findUser(int id) {
    if (id == 1) return "Pavan";
    return nullopt;
}
auto name = findUser(1);
if (name.has_value()) cout << *name;
```

---

## 🔴 ADVANCED (Q41–Q50)

### Q37. What is SFINAE?
Substitution Failure Is Not An Error. When template substitution fails, compiler tries other overloads instead of erroring. Used for compile-time type-based selection.

### Q38. What is the difference between `static_cast`, `dynamic_cast`, `reinterpret_cast`?

| Cast | Use | Check |
|------|-----|-------|
| `static_cast` | Known compatible types | Compile-time |
| `dynamic_cast` | Base→Derived (polymorphic) | Runtime (RTTI) |
| `reinterpret_cast` | Reinterpret bit pattern | None — dangerous |
| `const_cast` | Add/remove const | None |

### Q39. What is a function pointer? Lambda vs function pointer?
```cpp
int (*funcPtr)(int, int) = add;  // function pointer
funcPtr(3, 4);                   // call through pointer

// Lambda vs function pointer:
// Function pointers: only for stateless functions
// Lambdas: can capture state, more flexible
// std::function: wraps both (but has overhead)
```

### Q40. What is the Rule of Three/Five/Zero?

- **Rule of Three** (C++03): If you define destructor, copy constructor, or copy assignment, define all three.
- **Rule of Five** (C++11): Add move constructor and move assignment operator.
- **Rule of Zero**: Design classes that need none of them (use smart pointers and standard containers).

### Q41–Q50: Quick Answers

**Q41. What is inline?** Hint to compiler to expand function body at call site — avoids call overhead.

**Q42. What is `mutable`?** Allows a member variable to be modified even in `const` member functions.

**Q43. What is `explicit`?** Prevents implicit conversions through constructors. `explicit MyClass(int x)` — can't do `MyClass obj = 5;`

**Q44. What is an initializer list?** Syntax for initializing members before constructor body: `: member(val)`. More efficient than assigning in body.

**Q45. What is a friend function?** Non-member function with access to private/protected members. Used for operator overloading and utility functions.

**Q46. What is static in C++?** 
- Static variable: persists for program lifetime, shared across calls
- Static member: shared by all objects of the class
- Static function: can be called without object

**Q47. What is `volatile`?** Tells compiler not to optimize reads/writes to that variable — variable may change outside program control (e.g. hardware register).

**Q48. Difference between deep copy and shallow copy?**
- Shallow: copies pointer values (both point to same memory)
- Deep: copies actual pointed-to data (independent copies)

**Q49. What is name mangling?** C++ encodes function name + parameter types into a unique symbol name to support overloading. `extern "C"` disables it for C interoperability.

**Q50. What happens if exception is thrown in destructor?** Undefined behaviour if another exception is already propagating. Should never throw in destructors — use `noexcept`.

---

*Last reviewed: Current — keep updating after each interview/mock*
