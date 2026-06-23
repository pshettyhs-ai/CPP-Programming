# 📝 05 — Pointers Notes

> *Pavan Shetty H S — Week 4, most challenging week so far*

---

## The Mental Model That Helped Me

Think of memory as a big array of boxes. Each box has:
- An **address** (like a house number)
- A **value** (what's stored inside)

A pointer is just a variable that holds an address. That's it.

```
Memory:
Address:  1000   1004   1008   1012
Value:    [42]   [ptr]  [...]  [...]
            ↑      │
           num     └──> 1000 (stores the address of num)

int num = 42;     // value at address 1000
int* ptr = &num;  // ptr stores 1000 (the address)
*ptr              // "go to address 1000 and read the value" = 42
```

---

## The 4 const + pointer combinations

This tripped me up for a while. Mnemonic: read right-to-left.

```cpp
int*       const p;   // const pointer → address fixed, value changeable
const int* p;         // pointer to const → address changeable, value fixed
int const* p;         // same as above (different syntax)
const int* const p;   // both fixed — fully const
```

---

## Memory Areas in C++

```
┌─────────────────────────┐
│     Code/Text Segment   │  ← your compiled code
├─────────────────────────┤
│     Data Segment        │  ← global & static variables
├─────────────────────────┤
│     Stack               │  ← local variables, function calls
│     ↓ grows downward    │    (fast, auto-managed, limited size)
├─────────────────────────┤
│     ↑ grows upward      │
│     Heap                │  ← dynamic memory (new/delete)
└─────────────────────────┘   (slower, manual, large but can fragment)
```

---

## Smart Pointer Decision Tree

```
Need a pointer?
    │
    ├── One owner? ──────────────► unique_ptr  ← default choice
    │
    ├── Multiple owners? ─────────► shared_ptr
    │
    └── Non-owning observer? ─────► weak_ptr (avoids circular ref)
```

**Rule**: never use raw `new`/`delete` in modern C++ unless you have a specific reason.

---

## Common Pointer Bugs (I've hit all of these)

| Bug | Description | How to Avoid |
|-----|-------------|--------------|
| Null dereference | `*ptr` when `ptr == nullptr` | Always check before deref |
| Dangling pointer | Using pointer after `delete` | Set to `nullptr` after delete |
| Memory leak | `new` without `delete` | Use smart pointers |
| Double delete | `delete ptr` twice | Set to `nullptr`, use RAII |
| Buffer overflow | `arr[n+1]` out of bounds | Use vectors, check bounds |

---

## Embedded Connection

In embedded C/C++ (STM32, Arduino):
```c
// GPIO register access via pointer
volatile uint32_t* GPIOA_ODR = (uint32_t*)0x40020014;
*GPIOA_ODR |= (1 << 5);   // Set PA5 high

// This is literally just pointer dereference!
```
`volatile` keyword tells compiler: this memory can change unexpectedly (hardware registers). Don't optimize away reads/writes.

---
*Next: OOP → 06_OOP/*
