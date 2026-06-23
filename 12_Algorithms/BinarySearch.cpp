/*
 * File    : BinarySearch.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Binary Search — O(log n), requires sorted array
 * Date    : Week 13 - Day 4
 */

#include <iostream>
#include <vector>
using namespace std;

// Iterative — no stack overhead
int binarySearchIter(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoids overflow vs (low+high)/2
        if      (arr[mid] == target) return mid;
        else if (arr[mid] <  target) low  = mid + 1;
        else                         high = mid - 1;
    }
    return -1;
}

// Recursive
int binarySearchRec(const vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if      (arr[mid] == target) return mid;
    else if (arr[mid] <  target) return binarySearchRec(arr, mid+1, high, target);
    else                         return binarySearchRec(arr, low, mid-1, target);
}

int main() {
    cout << "=== BINARY SEARCH ===" << endl;

    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};

    cout << "Array: ";
    for (int x : arr) cout << x << " "; cout << endl;

    int targets[] = {13, 1, 21, 10};
    for (int t : targets) {
        int idx = binarySearchIter(arr, t);
        if (idx != -1) cout << "Search " << t << " → found at index " << idx << endl;
        else           cout << "Search " << t << " → not found" << endl;
    }

    cout << "\nComplexity: O(log n) | Space: O(1) iterative, O(log n) recursive" << endl;
    cout << "Requirement: ARRAY MUST BE SORTED" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread BinarySearch.cpp -o prog
 ================================================================

 === BINARY SEARCH ===
 Array: 1 3 5 7 9 11 13 15 17 19 21 
 Search 13 → found at index 6
 Search 1 → found at index 0
 Search 21 → found at index 10
 Search 10 → not found

 Complexity: O(log n) | Space: O(1) iterative, O(log n) recursive
 Requirement: ARRAY MUST BE SORTED

 ================================================================
*/

