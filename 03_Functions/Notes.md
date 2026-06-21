# 📝 03 — Functions Notes

> *Pavan Shetty H S — Week 3*

---

## Core Concepts

### Pass By Value vs Reference vs Pointer

| Method | Syntax | Modifies Original? | Use When |
|--------|--------|--------------------|----------|
| By value | `void f(int x)` | No | Small types, no modification needed |
| By reference | `void f(int& x)` | Yes | Need to modify, cleaner syntax |
| By pointer | `void f(int* x)` | Yes (via `*x`) | Optional params, C interop, arrays |
| By const ref | `void f(const string& s)` | No | Large objects, read-only (efficient!) |

### When I Use Each
- **Primitives (int, float)**: pass by value unless I need to modify
- **Strings, vectors, structs**: pass by `const&` for efficiency
- **When I need to modify**: pass by `&`
- **C code or nullable params**: pass by pointer

### Recursion Mental Model
```
factorial(4)
  = 4 * factorial(3)
       = 3 * factorial(2)
            = 2 * factorial(1)
                 = 1   ← base case
            = 2 * 1 = 2
       = 3 * 2 = 6
  = 4 * 6 = 24
```
Each call waits for the inner call to return. The call stack grows with each recursive call.

### Stack Overflow from Recursion
If no base case (or base case never reached), stack fills up:
```
Stack: [main] [f(1000)] [f(999)] [f(998)] ... overflow!
```
Default stack size is usually 1–8 MB. Deep recursion = risk.

## Observations
- Function overloading is resolved at **compile time** — no runtime cost
- Default arguments: only set them in the **declaration** (in header), not definition
- `inline` is just a hint — modern compilers decide this themselves based on optimization level
- Recursion vs iteration: iterative is usually more efficient (no stack overhead), but recursion is more readable for tree/graph problems

## Debugging Experience
Had a bug where `swapByValue` wasn't swapping — spent 10 minutes wondering why before remembering it's a copy. Classic. Now I always think: "does this function need to modify the original?"

---
*Next: Arrays and Strings → 04_Arrays_and_Strings/*
