/*
 * File    : Arrays.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Arrays — static, dynamic, common operations
 * Date    : Week 3 - Day 4
 */

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== ARRAYS IN C++ ===" << endl;

    // 1. Declaration and initialisation
    int arr1[5];              // uninitialised — garbage values!
    int arr2[5] = {10, 20, 30, 40, 50};
    int arr3[] = {1, 2, 3};  // size deduced (3)
    int arr4[5] = {1, 2};    // rest are 0: {1, 2, 0, 0, 0}

    cout << "\n--- Traversal ---" << endl;
    for (int i = 0; i < 5; i++) cout << arr2[i] << " ";
    cout << endl;

    // 2. Common operations
    int data[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n = sizeof(data) / sizeof(data[0]);   // get array size
    cout << "Size (sizeof trick): " << n << endl;

    // Sort
    sort(data, data + n);
    cout << "Sorted: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    // Max, min, sum
    int maxVal = *max_element(data, data + n);
    int minVal = *min_element(data, data + n);
    int sum = 0;
    for (int x : data) sum += x;
    cout << "Max=" << maxVal << " Min=" << minVal << " Sum=" << sum << endl;

    // 3. Passing array to function
    auto printArr = [](int* arr, int sz) {
        for (int i = 0; i < sz; i++) cout << arr[i] << " ";
        cout << endl;
    };
    cout << "Passed to lambda: "; printArr(arr2, 5);

    // 4. Reverse array
    int rev[] = {1, 2, 3, 4, 5};
    reverse(rev, rev + 5);
    cout << "Reversed: ";
    for (int x : rev) cout << x << " "; cout << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Arrays.cpp -o prog
 ================================================================

 === ARRAYS IN C++ ===

 --- Traversal ---
 10 20 30 40 50 
 Size (sizeof trick): 9
 Sorted: 1 2 3 4 5 6 7 8 9 
 Max=9 Min=1 Sum=45
 Passed to lambda: 10 20 30 40 50 
 Reversed: 5 4 3 2 1 

 ================================================================
*/

