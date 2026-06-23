# 🔷 Coding Practice Questions

> *Pavan Shetty H S — Problems I solved while prepping*

---

## Array Problems

### Q1. Two Sum
Find two numbers in array that add to target.
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement))
            return {seen[complement], i};
        seen[nums[i]] = i;
    }
    return {};
}
// Time: O(n), Space: O(n)
```

### Q2. Find Maximum in Rotated Sorted Array
```cpp
int findMax(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else                      hi = mid;
    }
    return nums[lo];
}
```

### Q3. Check if string is palindrome (ignoring non-alphanumeric)
```cpp
bool isPalindrome(string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        while (l < r && !isalnum(s[l])) l++;
        while (l < r && !isalnum(s[r])) r--;
        if (tolower(s[l]) != tolower(s[r])) return false;
        l++; r--;
    }
    return true;
}
```

---

## String Problems

### Q4. Count character frequency
```cpp
map<char, int> charFreq(string s) {
    map<char, int> freq;
    for (char c : s) freq[c]++;
    return freq;
}
```

### Q5. Reverse words in a sentence
```cpp
string reverseWords(string s) {
    istringstream iss(s);
    vector<string> words;
    string word;
    while (iss >> word) words.push_back(word);
    reverse(words.begin(), words.end());
    string result;
    for (int i = 0; i < words.size(); i++) {
        if (i) result += " ";
        result += words[i];
    }
    return result;
}
```

---

## Linked List Problems

### Q6. Detect cycle in linked list (Floyd's algorithm)
```cpp
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

### Q7. Reverse a linked list
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

---

## Tree Problems

### Q8. Check if BST is valid
```cpp
bool isValidBST(TreeNode* root, long lo = LONG_MIN, long hi = LONG_MAX) {
    if (!root) return true;
    if (root->val <= lo || root->val >= hi) return false;
    return isValidBST(root->left,  lo, root->val) &&
           isValidBST(root->right, root->val, hi);
}
```

### Q9. Level-order traversal (BFS)
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            auto node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}
```

---

## Complexity Review (my personal notes)

Things I had to remind myself:
- Accessing `unordered_map` — O(1) average, O(n) worst (hash collision)
- `push_back` on vector — O(1) amortised (not always!)
- `sort` — O(n log n), not O(n²)
- Binary search needs **sorted** array — caught me out once
- DFS uses stack (recursion or explicit), BFS uses queue
