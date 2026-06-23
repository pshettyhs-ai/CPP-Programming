/*
 * File    : BubbleSort.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Bubble Sort + Selection Sort + Insertion Sort
 * Date    : Week 13 - Day 1
 *
 * Notes:
 *   These three are the "simple" sorts — O(n²) worst case.
 *   Not used in production for large data, but important to understand
 *   as they form the conceptual basis for understanding sorting.
 *   
 *   For real use: std::sort() which uses Introsort (hybrid of quicksort,
 *   heapsort, and insertion sort — O(n log n) guaranteed)
 */

#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int>& arr, string label = "") {
    if (!label.empty()) cout << label << ": ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// BUBBLE SORT — O(n²) avg, O(n) best (already sorted)
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // optimisation: early exit if no swaps
    }
    printArray(arr, "Bubble  ");
}

// SELECTION SORT — O(n²) always, minimum swaps
void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
    printArray(arr, "Select  ");
}

// INSERTION SORT — O(n²) avg, O(n) best, stable, good for small/nearly sorted
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    printArray(arr, "Insert  ");
}

int main() {
    cout << "=== SIMPLE SORTING ALGORITHMS ===" << endl;

    vector<int> data = {64, 34, 25, 12, 22, 11, 90, 1, 55, 43};
    printArray(data, "Original");

    cout << "\nResults:" << endl;
    bubbleSort(data);
    selectionSort(data);
    insertionSort(data);

    cout << "\n--- Complexity Summary ---" << endl;
    cout << "Algorithm  | Best  | Average | Worst | Space | Stable" << endl;
    cout << "-----------|-------|---------|-------|-------|-------" << endl;
    cout << "Bubble     | O(n)  | O(n²)   | O(n²) | O(1)  | Yes" << endl;
    cout << "Selection  | O(n²) | O(n²)   | O(n²) | O(1)  | No" << endl;
    cout << "Insertion  | O(n)  | O(n²)   | O(n²) | O(1)  | Yes" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread BubbleSort.cpp -o prog
 ================================================================

 === SIMPLE SORTING ALGORITHMS ===
 Original: 64 34 25 12 22 11 90 1 55 43 

 Results:
 Bubble  : 1 11 12 22 25 34 43 55 64 90 
 Select  : 1 11 12 22 25 34 43 55 64 90 
 Insert  : 1 11 12 22 25 34 43 55 64 90 

 --- Complexity Summary ---
 Algorithm  | Best  | Average | Worst | Space | Stable
 -----------|-------|---------|-------|-------|-------
 Bubble     | O(n)  | O(n²)   | O(n²) | O(1)  | Yes
 Selection  | O(n²) | O(n²)   | O(n²) | O(1)  | No
 Insertion  | O(n)  | O(n²)   | O(n²) | O(1)  | Yes

 ================================================================
*/

