/*
 * File    : MergeSort.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Merge Sort — O(n log n), stable, divide and conquer
 * Date    : Week 13 - Day 2
 *
 * Notes:
 *   Merge sort is my favourite sorting algorithm. Clean and elegant.
 *   The idea: split the array in half, sort each half, merge them.
 *   It's stable (equal elements keep their relative order).
 *   Downside: O(n) extra space for the merge step.
 */

#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left,  arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left,    mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    cout << "=== MERGE SORT ===" << endl;

    vector<int> arr = {38, 27, 43, 3, 9, 82, 10, 45, 1, 55};

    cout << "Original: ";
    for (int x : arr) cout << x << " "; cout << endl;

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted  : ";
    for (int x : arr) cout << x << " "; cout << endl;

    cout << "\nComplexity: O(n log n) always | Space: O(n) | Stable: Yes" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread MergeSort.cpp -o prog
 ================================================================

 === MERGE SORT ===
 Original: 38 27 43 3 9 82 10 45 1 55 
 Sorted  : 1 3 9 10 27 38 43 45 55 82 

 Complexity: O(n log n) always | Space: O(n) | Stable: Yes

 ================================================================
*/

