# 📝 06 — OOP Notes

> *Pavan Shetty H S — Weeks 5–7, the core of C++*

---

## The 4 OOP Pillars — Quick Summary

| Pillar | What It Means | C++ Feature |
|--------|---------------|-------------|
| **Encapsulation** | Bundle data + hide internals | `private`, getters/setters |
| **Abstraction** | Show WHAT, hide HOW | Abstract classes, pure virtual |
| **Inheritance** | Reuse parent class features | `:` inheritance, `public/protected` |
| **Polymorphism** | Same interface, different behaviour | `virtual`, overriding |

---

## Access Specifiers at a Glance

```
           │ Same Class │ Derived Class │ Outside
───────────┼────────────┼───────────────┼─────────
public     │     ✅     │      ✅       │    ✅
protected  │     ✅     │      ✅       │    ❌
private    │     ✅     │      ❌       │    ❌
```

---

## Inheritance Access Table

When you inherit with `public`, `protected`, or `private`:

```
Base member │ public inherit │ protected inherit │ private inherit
────────────┼────────────────┼───────────────────┼────────────────
public      │   public       │   protected       │   private
protected   │   protected    │   protected       │   private
private     │   (hidden)     │   (hidden)        │   (hidden)
```

Use `public` inheritance 90% of the time.

---

## Virtual Function & vtable (How It Actually Works)

When a class has `virtual` functions, the compiler creates a **vtable** (virtual table):
```
Animal vtable:
  [0] → Animal::sound()
  [1] → Animal::move()

Dog vtable:
  [0] → Dog::sound()     ← overridden!
  [1] → Animal::move()   ← inherited

Animal* ptr = new Dog();
ptr->sound();  // looks up Dog's vtable at [0] → calls Dog::sound()
```

This vtable lookup happens at **runtime** — that's why it's called dynamic dispatch.

---

## Common Mistakes I Made

- ❌ Forgot `virtual` destructor in base class → derived destructor never called (memory leak!)
- ❌ Called virtual function in constructor → behaviour is undefined/base version is called
- ❌ Diamond problem with multiple inheritance — use `virtual` base class
- ❌ Slicing: `Animal a = Dog()` → Dog-specific parts are "sliced off". Use pointers/refs.
- ❌ Forgot `override` keyword — had a typo in function name, silently created a new function instead of overriding

---

## When to Use What

| Situation | Solution |
|-----------|----------|
| Reuse code from existing class | Inheritance |
| Same operation, different types | Templates / Overloading |
| Same interface, different classes | Virtual functions |
| Sensitive data | Private + getters |
| Force derived class to implement | Pure virtual |

---

## Interview Questions I've Prepared

**Q: Difference between overloading and overriding?**
- Overloading: same name, different parameters, compile-time
- Overriding: same name+params, different class (base+derived), runtime

**Q: Why use virtual destructor?**
- Without it, `delete base_ptr` only calls base destructor, leaking derived resources

**Q: Can we instantiate an abstract class?**
- No. It has at least one pure virtual function (= 0).

**Q: What is object slicing?**
- When a derived object is assigned to a base object (not pointer), derived parts are lost

---
*Next: STL → 07_STL/*
