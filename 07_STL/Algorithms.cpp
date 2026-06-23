/*
 * File    : Algorithms.cpp
 * Author  : Pavan Shetty H S
 * Topic   : STL Algorithms — sort, find, transform, etc.
 * Date    : Week 8 - Day 5
 *
 * Notes:
 *   STL algorithms work on ranges (begin, end).
 *   They're heavily optimized and tested — always prefer them over
 *   manual loops. The <algorithm> header has 100+ functions.
 *   Combined with lambdas (C++11), they become extremely powerful.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

void print(const vector<int>& v, string label = "") {
    if (!label.empty()) cout << label << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    cout << "=== STL ALGORITHMS ===" << endl;

    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6, 2, 8, 1};

    // Sorting
    cout << "\n--- Sorting ---" << endl;
    vector<int> v1 = v;
    sort(v1.begin(), v1.end());
    print(v1, "Ascending ");

    sort(v1.begin(), v1.end(), greater<int>());
    print(v1, "Descending");

    sort(v1.begin(), v1.end(), [](int a, int b){ return abs(a - 5) < abs(b - 5); });
    print(v1, "By dist from 5");

    // Searching
    cout << "\n--- Searching ---" << endl;
    vector<int> vs = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = find(vs.begin(), vs.end(), 6);
    cout << "find(6): index " << (it - vs.begin()) << endl;

    // binary_search — needs sorted range
    cout << "binary_search(6): " << binary_search(vs.begin(), vs.end(), 6) << endl;

    auto lb = lower_bound(vs.begin(), vs.end(), 4); // first element >= 4
    auto ub = upper_bound(vs.begin(), vs.end(), 7); // first element >  7
    cout << "lower_bound(4): " << *lb << " at index " << (lb - vs.begin()) << endl;
    cout << "upper_bound(7): " << *ub << " at index " << (ub - vs.begin()) << endl;

    // Counting
    cout << "\n--- Counting ---" << endl;
    vector<int> vc = v;
    cout << "count(2) = " << count(vc.begin(), vc.end(), 2) << endl;
    cout << "count_if(even) = " << count_if(vc.begin(), vc.end(),
                                            [](int x){ return x % 2 == 0; }) << endl;

    // Transforming
    cout << "\n--- Transforming ---" << endl;
    vector<int> vt = {1, 2, 3, 4, 5};
    vector<int> squared(vt.size());
    transform(vt.begin(), vt.end(), squared.begin(), [](int x){ return x * x; });
    print(squared, "Squares");

    // Removing duplicates
    cout << "\n--- Remove Duplicates ---" << endl;
    vector<int> vd = {1, 1, 2, 3, 3, 4, 5, 5};
    auto newEnd = unique(vd.begin(), vd.end());
    vd.erase(newEnd, vd.end());
    print(vd, "Unique");

    // Numeric algorithms
    cout << "\n--- Numeric ---" << endl;
    vector<int> vn = {1, 2, 3, 4, 5};
    cout << "sum: "     << accumulate(vn.begin(), vn.end(), 0)  << endl;
    cout << "product: " << accumulate(vn.begin(), vn.end(), 1,
                                      multiplies<int>())          << endl;
    cout << "max: " << *max_element(vn.begin(), vn.end())        << endl;
    cout << "min: " << *min_element(vn.begin(), vn.end())        << endl;

    // Fill, generate, iota
    cout << "\n--- Fill / Generate / Iota ---" << endl;
    vector<int> vf(5);
    fill(vf.begin(), vf.end(), 42);
    print(vf, "fill(42)");

    iota(vf.begin(), vf.end(), 10);  // 10, 11, 12, 13, 14
    print(vf, "iota(10)");

    int counter = 0;
    generate(vf.begin(), vf.end(), [&counter]{ return counter++ * 3; });
    print(vf, "generate(*3)");

    // Reverse and rotate
    cout << "\n--- Reverse / Rotate ---" << endl;
    vector<int> vr = {1, 2, 3, 4, 5};
    reverse(vr.begin(), vr.end());
    print(vr, "Reversed");

    rotate(vr.begin(), vr.begin() + 2, vr.end());
    print(vr, "Rotated by 2");

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Algorithms.cpp -o prog
 ================================================================

 === STL ALGORITHMS ===

 --- Sorting ---
 Ascending : 1 1 2 2 3 4 5 6 7 8 8 9 
 Descending: 9 8 8 7 6 5 4 3 2 2 1 1 
 By dist from 5: 5 6 4 7 3 8 8 2 2 9 1 1 

 --- Searching ---
 find(6): index 5
 binary_search(6): 1
 lower_bound(4): 4 at index 3
 upper_bound(7): 8 at index 7

 --- Counting ---
 count(2) = 2
 count_if(even) = 6

 --- Transforming ---
 Squares: 1 4 9 16 25 

 --- Remove Duplicates ---
 Unique: 1 2 3 4 5 

 --- Numeric ---
 sum: 15
 product: 120
 max: 5
 min: 1

 --- Fill / Generate / Iota ---
 fill(42): 42 42 42 42 42 
 iota(10): 10 11 12 13 14 
 generate(*3): 0 3 6 9 12 

 --- Reverse / Rotate ---
 Reversed: 5 4 3 2 1 
 Rotated by 2: 3 2 1 5 4 

 ================================================================
*/

