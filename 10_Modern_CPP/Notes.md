# 📝 10 — Modern C++ Notes

> *Pavan Shetty H S — Weeks 10-11, C++11/14/17 features*

---

## C++ Version Features at a Glance

### C++11 (The Big One)
- `auto` type deduction
- Range-based for loops
- Lambda expressions
- Move semantics + rvalue references (`&&`)
- Smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`)
- `nullptr`
- `override` and `final` keywords
- Uniform initialisation `{}`
- `constexpr`
- Threading (`std::thread`, `std::mutex`)
- Variadic templates

### C++14
- Generic lambdas (`auto` params)
- Lambda capture with init (`[x = std::move(y)]`)
- `make_unique`
- Return type deduction for functions

### C++17
- Structured bindings (`auto& [key, val]`)
- `if constexpr`
- `std::optional`, `std::variant`
- `std::filesystem`
- Fold expressions

---

## Lambda Capture Rules

```cpp
[]           // capture nothing
[=]          // capture all by value (copy)
[&]          // capture all by reference
[x]          // capture x by value
[&x]         // capture x by reference
[=, &x]      // capture all by value, x by reference
[this]       // capture this pointer (in member functions)
[x = expr]   // capture x with init (C++14)
```

---

## Move Semantics in Plain English

```
Copy: I'll make a duplicate of your book.
Move: I'll take your book. You have nothing now.

Buffer b1(1000);       // create b1 with 1000 elements
Buffer b2 = b1;        // COPY: b2 gets a duplicate. Both have data.
Buffer b3 = move(b1);  // MOVE: b3 steals b1's data. b1 is now empty.
```

**When to use `std::move`:**
- When you know you don't need the original anymore
- When passing a named variable to a function that accepts `&&`
- When storing into containers (`push_back(move(obj))`)

---

## auto Best Practices

**Use auto when:**
- Iterator types are complex
- Return type is obvious from context
- Template code

**Avoid auto when:**
- Type matters for readability (`int port = 8080;` is clearer than `auto port = 8080;`)
- Would hide important type information

---
*Next: Data Structures → 11_Data_Structures/*
