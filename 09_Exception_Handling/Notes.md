# 📝 09 — Exception Handling Notes

> *Pavan Shetty H S — Week 9*

---

## Standard Exception Hierarchy

```
std::exception
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   └── std::out_of_range
├── std::runtime_error
│   ├── std::range_error
│   ├── std::overflow_error
│   └── std::underflow_error
└── std::bad_alloc       (thrown by new when out of memory)
└── std::bad_cast        (thrown by dynamic_cast on fail)
```

## Key Rules

1. **Throw by value, catch by const reference**
   ```cpp
   throw MyException("msg");          // throw by value
   catch (const MyException& e) { }   // catch by const ref
   ```

2. **Catch more specific exceptions first** (more derived first)
   ```cpp
   catch (const invalid_argument& e) { }  // specific first
   catch (const logic_error& e)      { }  // then base
   catch (const exception& e)        { }  // then std base
   catch (...)                        { }  // catch-all last
   ```

3. **Never throw from a destructor** — if an exception is already propagating,
   throwing another causes `std::terminate()`

4. **Use `noexcept`** on functions that should never throw
   ```cpp
   void swap(T& a, T& b) noexcept { ... }
   ```

## RAII and Exceptions

The beauty of RAII: even when exceptions are thrown, destructors still run, so resources are always cleaned up:

```cpp
void process() {
    FileGuard f("data.txt");       // opens file
    DatabaseConn db("localhost");  // opens connection
    // ... something throws here
    // BOTH f and db are still properly destroyed!
}
```

## When NOT to Use Exceptions

- Performance-critical code (exception handling has overhead)
- Embedded systems without exception support
- Expected/common error conditions (use return codes instead)
- Constructor failure alternatives: use static factory methods

---
*Next: Modern C++ → 10_Modern_CPP/*
