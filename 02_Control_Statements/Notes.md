# 📝 02 — Control Statements Notes

> *Pavan Shetty H S — Week 2 observations*

---

## Key Takeaways

### Switch vs if-else
- Switch generates a **jump table** — O(1) lookup vs O(n) chain of if-else
- Use switch for **known discrete values** (menu choices, day numbers, grades)
- Switch does NOT work with strings or floats — use if-else for those
- **Always add `break`** unless fall-through is intentional (and comment it!)

### Loop Choice Guide
| Situation | Use |
|-----------|-----|
| Known count | `for` |
| Unknown count, check before | `while` |
| Unknown count, run at least once | `do-while` |
| Iterate over container | range-based `for` |

### Common Bugs
- ❌ Forgot `break` in switch → unexpected fall-through
- ❌ `i <= n` vs `i < n` — off-by-one error (super common)
- ❌ Infinite loop from `while (true)` with no `break` condition
- ❌ Modifying loop variable inside the loop body

### Interesting: Loop Unrolling
Compiler can "unroll" loops for performance. If you write a loop that runs 4 times, the compiler might replace it with 4 sequential statements. This is why micro-optimizing loops manually is usually unnecessary.

---

*Next: Functions → 03_Functions/*
