# 🔷 STL Interview Questions

> *Pavan Shetty H S — STL deep dive prep*

---

## Q1. What is the difference between `vector` and `deque`?

| | `vector` | `deque` |
|--|----------|---------|
| Memory | Single contiguous block | Multiple fixed-size blocks |
| Random access | O(1) | O(1) |
| Insert/delete front | O(n) | O(1) |
| Insert/delete back | O(1) amortised | O(1) |
| Cache performance | Better | Slightly worse |
| Pointer stability | Invalidated on realloc | More stable |

Use `deque` when you need frequent insert/delete at **both** ends.

---

## Q2. How does `std::sort` work internally?

`std::sort` uses **Introsort** — a hybrid of:
1. **Quicksort** — main algorithm (great average performance)
2. **Heapsort** — used when recursion depth exceeds O(log n) (prevents O(n²) worst case)
3. **Insertion sort** — for small partitions (< ~16 elements, very fast in practice)

This gives guaranteed **O(n log n)** worst case with excellent practical performance.

---

## Q3. Difference between `find` and `binary_search`?

| | `find` | `binary_search` |
|--|--------|-----------------|
| Requires sorted? | No | Yes |
| Complexity | O(n) | O(log n) |
| Returns | Iterator to element | bool |
| Works on | Any iterator | Random access / sorted |

`binary_search` only tells you IF the element exists, not WHERE. Use `lower_bound` / `upper_bound` to find position.

---

## Q4. When should you use `reserve()` on a vector?

When you know approximately how many elements you'll add:

```cpp
vector<int> v;
// Without reserve: multiple reallocations as vector grows
for (int i = 0; i < 1000000; i++) v.push_back(i);  // ~20 reallocations

// With reserve: zero reallocations
v.reserve(1000000);
for (int i = 0; i < 1000000; i++) v.push_back(i);  // much faster!
```

`resize(n)` actually adds n elements (default-initialised). `reserve(n)` just allocates memory without adding elements.

---

## Q5. What is an iterator invalidation?

Certain operations invalidate existing iterators — using them after is undefined behaviour.

```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin() + 2;  // iterator to element 3

v.push_back(6);     // May reallocate! it is now INVALID if reallocation occurred
// *it is undefined behaviour

// Safe pattern: use indices instead of iterators when modifying
```

**Which operations invalidate iterators:**
- `vector::push_back` / `insert` — if reallocation occurs, ALL iterators
- `vector::erase` — iterators at/after erase point
- `deque::push_front/back` — all iterators; `erase` — some
- `list::insert` — none; `list::erase` — only the erased iterator

---

## Q6. Priority queue — max-heap vs min-heap?

```cpp
// Max-heap (default) — top() gives largest
priority_queue<int> maxPQ;
maxPQ.push(3); maxPQ.push(1); maxPQ.push(5);
cout << maxPQ.top();  // 5

// Min-heap — top() gives smallest
priority_queue<int, vector<int>, greater<int>> minPQ;
minPQ.push(3); minPQ.push(1); minPQ.push(5);
cout << minPQ.top();  // 1
```

---

## Q7. What is the difference between `emplace_back` and `push_back`?

- `push_back(obj)` — copies or moves an already-constructed object
- `emplace_back(args...)` — constructs the object in-place (no copy/move overhead)

```cpp
vector<pair<int,string>> v;
v.push_back({1, "hello"});         // constructs pair, then moves it in
v.emplace_back(2, "world");        // constructs pair directly in vector — more efficient
```

Always prefer `emplace_back` when possible.

---

## Q8. What does `std::move` actually do?

`std::move` doesn't move anything — it's just a **cast to rvalue reference**. It tells the compiler: "this object can be 'stolen' from".

The actual moving happens in the move constructor / move assignment.

```cpp
string s1 = "Hello, World!";
string s2 = move(s1);   // s1 is now empty, s2 has the content
// s1.size() == 0 after move
```
