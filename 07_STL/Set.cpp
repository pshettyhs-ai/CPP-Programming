/*
 * File    : Set.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::set, std::multiset, std::unordered_set
 * Date    : Week 8 - Day 4
 */

#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    cout << "=== SET CONTAINERS ===" << endl;

    // set — sorted, unique
    cout << "\n--- std::set ---" << endl;
    set<int> s = {5, 2, 8, 1, 9, 3, 5, 2};  // duplicates removed
    cout << "Set (auto-sorted, no dups): ";
    for (int x : s) cout << x << " "; cout << endl;

    s.insert(6);
    s.insert(3);   // duplicate — ignored
    cout << "After insert 6 and 3: ";
    for (int x : s) cout << x << " "; cout << endl;

    cout << "count(5): " << s.count(5) << " (1=exists, 0=not)" << endl;
    cout << "count(99): " << s.count(99) << endl;

    s.erase(5);
    cout << "After erase(5): ";
    for (int x : s) cout << x << " "; cout << endl;

    // set operations — union, intersection, difference
    cout << "\n--- Set Operations ---" << endl;
    set<int> A = {1, 2, 3, 4, 5};
    set<int> B = {3, 4, 5, 6, 7};

    // Intersection
    cout << "A ∩ B: ";
    for (int x : A) if (B.count(x)) cout << x << " "; cout << endl;

    // Union
    cout << "A ∪ B: ";
    set<int> uni(A.begin(), A.end());
    uni.insert(B.begin(), B.end());
    for (int x : uni) cout << x << " "; cout << endl;

    // unordered_set — O(1) average lookup
    cout << "\n--- unordered_set ---" << endl;
    unordered_set<string> words = {"hello", "world", "cpp", "pavan"};
    cout << "Contains 'cpp': "    << words.count("cpp")    << endl;
    cout << "Contains 'python': " << words.count("python") << endl;

    // Remove duplicates from vector using set
    cout << "\n--- Remove Duplicates ---" << endl;
    vector<int> v = {4, 2, 7, 2, 4, 1, 9, 7, 3};
    cout << "Original: "; for (int x : v) cout << x << " "; cout << endl;
    set<int> unique_s(v.begin(), v.end());
    cout << "Unique:   "; for (int x : unique_s) cout << x << " "; cout << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Set.cpp -o prog
 ================================================================

 === SET CONTAINERS ===

 --- std::set ---
 Set (auto-sorted, no dups): 1 2 3 5 8 9 
 After insert 6 and 3: 1 2 3 5 6 8 9 
 count(5): 1 (1=exists, 0=not)
 count(99): 0
 After erase(5): 1 2 3 6 8 9 

 --- Set Operations ---
 A ∩ B: 3 4 5 
 A ∪ B: 1 2 3 4 5 6 7 

 --- unordered_set ---
 Contains 'cpp': 1
 Contains 'python': 0

 --- Remove Duplicates ---
 Original: 4 2 7 2 4 1 9 7 3 
 Unique:   1 2 3 4 7 9 

 ================================================================
*/

