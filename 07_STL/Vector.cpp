/*
 * File    : Vector.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::vector — the most used STL container
 * Date    : Week 8 - Day 1
 *
 * Notes:
 *   vector = dynamic array that grows automatically.
 *   It stores elements contiguously in memory (like arrays) so
 *   random access is O(1), just like arrays. But it can resize.
 *   
 *   When vector is full and you push_back(), it allocates a new
 *   larger block (usually 2x), copies everything, frees old memory.
 *   This is why reserve() is important when you know the size upfront.
 */

#include <iostream>
#include <vector>
#include <algorithm>  // sort, find, etc.
#include <numeric>    // accumulate
using namespace std;

int main() {
    cout << "=== std::vector ===" << endl;

    // ── Creation ──────────────────────────
    cout << "\n--- Creating Vectors ---" << endl;
    vector<int> v1;                        // empty
    vector<int> v2(5, 0);                  // 5 elements, all 0
    vector<int> v3 = {10, 20, 30, 40, 50}; // initializer list
    vector<string> names = {"Pavan", "Rahul", "Priya"};

    cout << "v2 (5 zeros): ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    cout << "v3: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // ── Adding elements ───────────────────
    cout << "\n--- Adding Elements ---" << endl;
    v1.push_back(100);
    v1.push_back(200);
    v1.push_back(300);
    v1.push_back(400);

    v1.insert(v1.begin() + 1, 150);  // insert 150 at index 1
    cout << "v1 after inserts: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // ── Accessing elements ────────────────
    cout << "\n--- Accessing Elements ---" << endl;
    cout << "v3[2]       = " << v3[2]      << " (no bounds check)" << endl;
    cout << "v3.at(2)    = " << v3.at(2)   << " (throws if out of range)" << endl;
    cout << "v3.front()  = " << v3.front() << endl;
    cout << "v3.back()   = " << v3.back()  << endl;

    // ── Size and capacity ─────────────────
    cout << "\n--- Size and Capacity ---" << endl;
    cout << "v3.size()     = " << v3.size()     << " (actual elements)" << endl;
    cout << "v3.capacity() = " << v3.capacity() << " (allocated memory)" << endl;
    cout << "v3.empty()    = " << v3.empty()    << endl;

    // Reserve to avoid reallocations
    vector<int> large;
    large.reserve(1000);  // allocate for 1000 without adding elements
    cout << "After reserve(1000): capacity=" << large.capacity() << " size=" << large.size() << endl;

    // ── Removing elements ─────────────────
    cout << "\n--- Removing Elements ---" << endl;
    vector<int> rem = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "Before: "; for (int x : rem) cout << x << " "; cout << endl;

    rem.pop_back();  // remove last
    rem.erase(rem.begin() + 2);  // remove index 2
    rem.erase(rem.begin() + 1, rem.begin() + 3);  // remove range [1,3)

    cout << "After:  "; for (int x : rem) cout << x << " "; cout << endl;

    // ── Algorithms with vector ────────────
    cout << "\n--- Algorithms ---" << endl;
    vector<int> nums = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    cout << "Original: "; for (int x : nums) cout << x << " "; cout << endl;

    sort(nums.begin(), nums.end());  // ascending
    cout << "Sorted:   "; for (int x : nums) cout << x << " "; cout << endl;

    sort(nums.begin(), nums.end(), greater<int>());  // descending
    cout << "Reversed: "; for (int x : nums) cout << x << " "; cout << endl;

    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum: " << sum << endl;

    auto it = find(nums.begin(), nums.end(), 5);
    if (it != nums.end())
        cout << "Found 5 at index: " << (it - nums.begin()) << endl;

    // ── 2D vector ─────────────────────────
    cout << "\n--- 2D Vector (matrix) ---" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    for (auto& row : matrix) {
        for (int val : row) {
            cout.width(4);
            cout << val;
        }
        cout << endl;
    }

    // ── Iterators ─────────────────────────
    cout << "\n--- Iterators ---" << endl;
    vector<int> iv = {10, 20, 30, 40, 50};
    for (auto it = iv.begin(); it != iv.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Reverse iterator
    for (auto rit = iv.rbegin(); rit != iv.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Vector.cpp -o prog
 ================================================================

 === std::vector ===

 --- Creating Vectors ---
 v2 (5 zeros): 0 0 0 0 0 
 v3: 10 20 30 40 50 

 --- Adding Elements ---
 v1 after inserts: 100 150 200 300 400 

 --- Accessing Elements ---
 v3[2]       = 30 (no bounds check)
 v3.at(2)    = 30 (throws if out of range)
 v3.front()  = 10
 v3.back()   = 50

 --- Size and Capacity ---
 v3.size()     = 5 (actual elements)
 v3.capacity() = 5 (allocated memory)
 v3.empty()    = 0
 After reserve(1000): capacity=1000 size=0

 --- Removing Elements ---
 Before: 1 2 3 4 5 6 7 8 
 After:  1 5 6 7 

 --- Algorithms ---
 Original: 5 2 8 1 9 3 7 4 6 
 Sorted:   1 2 3 4 5 6 7 8 9 
 Reversed: 9 8 7 6 5 4 3 2 1 
 Sum: 45
 Found 5 at index: 4

 --- 2D Vector (matrix) ---
    1   2   3
    4   5   6
    7   8   9

 --- Iterators ---
 10 20 30 40 50 
 50 40 30 20 10 

 ================================================================
*/

