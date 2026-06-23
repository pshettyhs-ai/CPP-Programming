# 📝 12 — Algorithms Notes

## Sorting Algorithm Decision

```
Small data (< 50 elements)     → Insertion Sort
General purpose                → std::sort() (Introsort)
Need stable sort               → std::stable_sort() or Merge Sort
Already nearly sorted          → Insertion Sort
Limited memory (in-place)      → Quick Sort or Heap Sort
Linked list                    → Merge Sort
Integers in known range        → Counting Sort (O(n+k))
```

## Big-O Quick Reference

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n logn) | O(n logn) | O(n logn) | O(n) |
| Quick Sort | O(n logn) | O(n logn) | O(n²) | O(logn) |
| Heap Sort | O(n logn) | O(n logn) | O(n logn) | O(1) |
| Binary Search | O(1) | O(logn) | O(logn) | O(1) |

## Key Insight: Why is QuickSort usually faster than MergeSort in practice?
Even though both are O(n log n) average, QuickSort has:
- Better cache locality (in-place, contiguous memory access)
- Smaller constant factor
- Doesn't need extra O(n) memory

MergeSort is preferred when stability is needed or for linked lists.
