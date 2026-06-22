# 📝 07 — STL Notes

> *Pavan Shetty H S — Week 8, things finally clicking*

---

## STL Container Quick Reference

| Container | Access | Insert (end) | Insert (middle) | Search | Ordered? |
|-----------|--------|-------------|-----------------|--------|----------|
| `vector` | O(1) | O(1)* | O(n) | O(n) | No |
| `list` | O(n) | O(1) | O(1) | O(n) | No |
| `deque` | O(1) | O(1) | O(n) | O(n) | No |
| `set` | O(log n) | O(log n) | — | O(log n) | Yes |
| `map` | O(log n) | O(log n) | — | O(log n) | Yes |
| `unordered_set` | O(1) avg | O(1) avg | — | O(1) avg | No |
| `unordered_map` | O(1) avg | O(1) avg | — | O(1) avg | No |
| `stack` | O(1) top | O(1) | — | — | LIFO |
| `queue` | O(1) front | O(1) | — | — | FIFO |
| `priority_queue` | O(1) top | O(log n) | — | — | Heap |

*Amortised — occasionally O(n) when resizing

---

## When to Use Which Container

```
Single elements, need order → vector (default choice)
Need fast insert/remove at both ends → deque
Need fast insert/remove in middle → list
Need unique sorted elements → set
Need key-value sorted → map
Need fastest possible lookup → unordered_map / unordered_set
Need LIFO behaviour → stack
Need FIFO behaviour → queue
Need max/min always ready → priority_queue
```

---

## STL Algorithm Categories

- **Non-modifying**: `find`, `count`, `equal`, `search`
- **Modifying**: `copy`, `transform`, `fill`, `replace`, `remove`
- **Sorting**: `sort`, `stable_sort`, `nth_element`, `partial_sort`
- **Numeric**: `accumulate`, `inner_product`, `iota`
- **Heap**: `make_heap`, `push_heap`, `pop_heap`

---

## Common Patterns

**Check if element exists in vector:**
```cpp
auto it = find(v.begin(), v.end(), val);
bool found = (it != v.end());
```

**Count occurrences:**
```cpp
int count = count(v.begin(), v.end(), val);
```

**Remove element from vector:**
```cpp
v.erase(remove(v.begin(), v.end(), val), v.end());  // erase-remove idiom
```

**Sort with custom comparator:**
```cpp
sort(v.begin(), v.end(), [](auto& a, auto& b){ return a.score > b.score; });
```

---

## Things That Confused Me

**Q: When does vector reallocate?**  
When `size == capacity`, the next `push_back` triggers reallocation (~2x capacity).  
Use `reserve(n)` upfront to prevent this.

**Q: Why use `at()` vs `[]`?**  
`[]` has no bounds checking — accessing out of bounds is undefined behaviour.  
`at()` throws `std::out_of_range` if index is invalid. Use `at()` when unsure.

**Q: Why is `list` rarely used?**  
Linked list elements are not contiguous in memory → cache unfriendly.  
Even though insert/delete is O(1), the cache misses make it slower than vector in practice.

---
*Next: File Handling → 08_File_Handling/*
