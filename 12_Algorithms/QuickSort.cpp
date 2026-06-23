/*
 * File    : QuickSort.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Quick Sort — O(n log n) average, in-place
 * Date    : Week 13 - Day 3
 *
 * Notes:
 *   QuickSort picks a pivot, partitions array around it, recursively sorts.
 *   Average case O(n log n), but worst case O(n²) if pivot is always min/max.
 *   In-place (no extra space unlike merge sort) — hence preferred in practice.
 *   std::sort() in C++ uses introsort (quicksort + heapsort + insertion sort).
 */

#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // last element as pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low,    pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    cout << "=== QUICK SORT ===" << endl;

    vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 6, 2, 4};

    cout << "Original: ";
    for (int x : arr) cout << x << " "; cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted  : ";
    for (int x : arr) cout << x << " "; cout << endl;

    cout << "\nComplexity: O(n log n) avg, O(n²) worst | Space: O(log n) | Stable: No" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread QuickSort.cpp -o prog
 ================================================================

 === QUICK SORT ===
 Original: 10 7 8 9 1 5 3 6 2 4 
 Sorted  : 1 2 3 4 5 6 7 8 9 10 

 Complexity: O(n log n) avg, O(n²) worst | Space: O(log n) | Stable: No

 ================================================================
*/

