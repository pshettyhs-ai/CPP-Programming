# 📝 11 — Data Structures Notes

## When to Use Each Structure

```
Need fast random access, mostly append at end → vector
Need insert/delete anywhere quickly → list (but cache misses!)
LIFO behaviour → stack
FIFO behaviour → queue
Priority access (always get max/min) → priority_queue
Sorted key-value, in-order iteration → map
Fastest key-value lookup → unordered_map
Hierarchical data, tree problems → BST / Tree
Graph connectivity, path-finding → Graph + BFS/DFS
```

## Complexity Quick Reference

| Structure | Access | Search | Insert | Delete |
|-----------|--------|--------|--------|--------|
| Array | O(1) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1) | O(1) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) |
| Hash Table | O(1)* | O(1)* | O(1)* | O(1)* |
| Heap | O(1) top | O(n) | O(log n) | O(log n) |

*Average case

## Tree Traversal Summary

```
       4
      / \
     2   6
    / \ / \
   1  3 5  7

Inorder   (LNR): 1 2 3 4 5 6 7 → sorted!
Preorder  (NLR): 4 2 1 3 6 5 7 → useful for copying
Postorder (LRN): 1 3 2 5 7 6 4 → useful for deletion
Level-order: 4 2 6 1 3 5 7    → BFS
```
