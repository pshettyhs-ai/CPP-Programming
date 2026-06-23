/*
 * File    : List.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::list — doubly linked list
 * Date    : Week 8 - Day 2
 */

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== std::list ===" << endl;

    list<int> lst = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Initial: "; for (int x : lst) cout << x << " "; cout << endl;

    // O(1) insert at front and back
    lst.push_front(0);
    lst.push_back(10);
    cout << "After push: "; for (int x : lst) cout << x << " "; cout << endl;

    // Sort
    lst.sort();
    cout << "Sorted: "; for (int x : lst) cout << x << " "; cout << endl;

    // Remove duplicates (needs sorted first)
    lst.unique();
    cout << "Unique: "; for (int x : lst) cout << x << " "; cout << endl;

    // Remove all matching values
    lst.remove(1);
    cout << "Remove 1: "; for (int x : lst) cout << x << " "; cout << endl;

    // Reverse
    lst.reverse();
    cout << "Reversed: "; for (int x : lst) cout << x << " "; cout << endl;

    // list is NOT good for random access — O(n)
    cout << "\nNote: list doesn't support random access (no lst[5])" << endl;
    cout << "Use it only when you need O(1) insert/delete at arbitrary positions" << endl;
    cout << "In practice, vector is usually faster even for those cases (cache effects)" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread List.cpp -o prog
 ================================================================

 === std::list ===
 Initial: 3 1 4 1 5 9 2 6 
 After push: 0 3 1 4 1 5 9 2 6 10 
 Sorted: 0 1 1 2 3 4 5 6 9 10 
 Unique: 0 1 2 3 4 5 6 9 10 
 Remove 1: 0 2 3 4 5 6 9 10 
 Reversed: 10 9 6 5 4 3 2 0 

 Note: list doesn't support random access (no lst[5])
 Use it only when you need O(1) insert/delete at arbitrary positions
 In practice, vector is usually faster even for those cases (cache effects)

 ================================================================
*/

