/*
 * File    : AutoKeyword.cpp
 * Author  : Pavan Shetty H S
 * Topic   : auto, decltype, type deduction (C++11/14)
 * Date    : Week 10 - Day 2
 */

#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <string>
using namespace std;

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    cout << "=== AUTO KEYWORD ===" << endl;

    // Basic type deduction
    auto i   = 42;           // int
    auto d   = 3.14;         // double
    auto f   = 3.14f;        // float
    auto c   = 'X';          // char
    auto s   = string("Hi"); // string
    auto b   = true;         // bool

    cout << "auto int: "    << i << endl;
    cout << "auto double: " << d << endl;
    cout << "auto char: "   << c << endl;

    // With const and reference
    const auto ci = 100;
    auto& ri = i;   // auto& deduces int&
    ri = 99;        // modifies i through reference
    cout << "i after ri=99: " << i << endl;

    // Iterator simplification
    cout << "\n--- Iterators ---" << endl;
    vector<map<string, int>> data = {
        {{"a", 1}, {"b", 2}},
        {{"c", 3}, {"d", 4}}
    };

    // Without auto:
    // for (vector<map<string,int>>::iterator it = data.begin(); it != data.end(); ++it)
    // With auto:
    for (auto it = data.begin(); it != data.end(); ++it) {
        for (auto& [key, val] : *it) {
            cout << "  " << key << "=" << val << endl;
        }
    }

    // Return type deduction
    cout << "\n--- Auto return type ---" << endl;
    cout << "add(3, 4.5) = " << add(3, 4.5) << endl;   // int + double = double
    cout << "add(1, 2)   = " << add(1, 2)   << endl;   // int + int = int

    // decltype
    cout << "\n--- decltype ---" << endl;
    int x = 10;
    decltype(x) y = 20;    // y has same type as x (int)
    decltype(x + y) z = x + y;
    cout << "y=" << y << " z=" << z << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread AutoKeyword.cpp -o prog
 ================================================================

 === AUTO KEYWORD ===
 auto int: 42
 auto double: 3.14
 auto char: X
 i after ri=99: 99

 --- Iterators ---
   a=1
   b=2
   c=3
   d=4

 --- Auto return type ---
 add(3, 4.5) = 7.5
 add(1, 2)   = 3

 --- decltype ---
 y=20 z=30

 ================================================================
*/

