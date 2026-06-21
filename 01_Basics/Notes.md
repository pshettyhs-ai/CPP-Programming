# 📝 01 — Basics Notes

> *Personal notes by Pavan Shetty H S — written while learning, not from a textbook*

---

## 🧠 What I Learnt This Week

### The Compilation Process (properly understood this time)

When you run `g++ hello.cpp -o hello`, four things happen under the hood:

```
Source Code (.cpp)
       │
       ▼
 Preprocessor     → handles #include, #define, removes comments
       │
       ▼
  Compiler         → converts to assembly code (.s)
       │
       ▼
  Assembler        → converts to machine code (.o object file)
       │
       ▼
   Linker          → links .o files + libraries → final executable
```

**Why this matters:** When you see "undefined reference to main" — that's a *linker* error, not a compiler error. Different stage, different problem.

---

## 📌 Key Observations

### Data Types
- `int` is 4 bytes on most modern systems, but **not guaranteed**
- In embedded (STM32, Arduino), always use `uint8_t`, `int32_t` etc. from `<cstdint>` — platform-independent sizes
- `float` has ~7 significant digits of precision. Don't use it for money calculations
- `auto` is resolved at **compile time**, not runtime — it's not like Python's dynamic typing

### Variables
- Uninitialized local variables have **garbage values** — this has bitten me in embedded code
- Global variables are zero-initialized automatically
- `static` local variable: initialized once, value persists across function calls

### Common Mistakes I Made
- ❌ `int x = 3.7` → silently truncates to 3. Use `{3.7}` brace init to get a warning
- ❌ Using `==` comparison on floats — never works reliably due to precision
- ❌ Forgetting `endl` flushes the buffer, `\n` doesn't — matters when debugging embedded output
- ❌ Integer overflow: `int x = 2147483647; x++;` → wraps to negative silently

### Operators
- Integer division: `7 / 2 = 3` (not 3.5!) — must cast to float first
- `++i` (pre-increment) is slightly faster than `i++` (post-increment) for complex types
- Bitwise ops are essential for embedded — use them for register manipulation, flags, masks

---

## 🔍 Things That Confused Me

**Q: Why does `cout << true` print `1` and not `true`?**  
A: Because by default, `bool` output is numeric. Use `boolalpha` manipulator: `cout << boolalpha << true` → prints "true"

**Q: When to use `const` vs `#define`?**  
A: Prefer `const` always. `#define` is just text substitution — no type safety, no debugging info, can't be scoped. `const` is a proper typed constant.

**Q: `endl` vs `\n` — which to use?**  
A: `\n` is faster (doesn't flush). Use `endl` only when you *need* the buffer flushed (like logging to a file). For regular console output, `\n` is fine.

---

## 💡 Embedded Systems Connection

These basics matter more in embedded than people think:
- **Bit manipulation operators** (`&`, `|`, `^`, `~`, `<<`, `>>`) — used *constantly* for GPIO, registers
- **Data type sizes** — critical, always use fixed-width types
- **Volatile keyword** — (covered later) — tells compiler not to optimize away hardware register reads

---

## ✅ Exercises Completed

- [x] Print name and college in formatted output
- [x] Calculate area of circle using `const double PI`
- [x] Show all type sizes on my machine
- [x] Demonstrate integer overflow with a loop
- [x] Bit manipulation: set, clear, toggle a specific bit in a variable

---

## 📚 Resources I Used

- *The C++ Programming Language* by Bjarne Stroustrup (too dense, read selectively)
- cppreference.com — my go-to for standard library docs
- learncpp.com — excellent structured lessons
- Stack Overflow — for when things didn't work

---

*Next: Control Statements → 02_Control_Statements/*
