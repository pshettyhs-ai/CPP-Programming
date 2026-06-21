/*
 * File    : Loops.cpp
 * Author  : Pavan Shetty H S
 * Topic   : for, while, do-while loops + range-based for (C++11)
 * Date    : Week 2 - Day 2
 *
 * Notes:
 *   Use for-loop when you know the count ahead of time.
 *   Use while-loop when condition is checked before executing.
 *   Use do-while when you need at least one execution.
 *   Range-based for (C++11) is great for containers.
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== LOOPS IN C++ ===" << endl;

    // 1. for loop
    cout << "\n--- for Loop ---" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "i = " << i << endl;
    }

    // Nested for — multiplication table
    cout << "\nMultiplication Table (1-5):" << endl;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cout.width(4);
            cout << i * j;
        }
        cout << endl;
    }

    // 2. while loop
    cout << "\n--- while Loop ---" << endl;
    int n = 1;
    while (n <= 5) {
        cout << "n = " << n << endl;
        n++;
    }

    // while for input validation (common pattern)
    // while (userInput < 0 || userInput > 100) { cin >> userInput; }

    // 3. do-while loop
    cout << "\n--- do-while Loop ---" << endl;
    int count = 1;
    do {
        cout << "count = " << count << endl;
        count++;
    } while (count <= 3);

    cout << "do-while runs at least once even if condition is false:" << endl;
    int x = 100;
    do {
        cout << "Executed once! x = " << x << endl;
    } while (x < 10);  // false from the start, but still runs once

    // 4. Range-based for loop (C++11)
    cout << "\n--- Range-based for (C++11) ---" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    // With vector
    vector<string> names = {"Pavan", "Rahul", "Priya", "Arjun"};
    for (const string& name : names) {
        cout << "Hello, " << name << "!" << endl;
    }

    // Auto with range-based for
    for (auto val : arr) {
        cout << val * 2 << " ";
    }
    cout << endl;

    // 5. Infinite loop with manual break
    cout << "\n--- Controlled infinite loop ---" << endl;
    int i = 0;
    for (;;) {  // or while(true)
        cout << "Loop iteration " << i << endl;
        i++;
        if (i >= 3) break;
    }

    // Star pattern — fun exercise
    cout << "\n--- Star Triangle ---" << endl;
    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Loops.cpp -o prog
 ================================================================

 === LOOPS IN C++ ===

 --- for Loop ---
 i = 1
 i = 2
 i = 3
 i = 4
 i = 5

 Multiplication Table (1-5):
    1   2   3   4   5
    2   4   6   8  10
    3   6   9  12  15
    4   8  12  16  20
    5  10  15  20  25

 --- while Loop ---
 n = 1
 n = 2
 n = 3
 n = 4
 n = 5

 --- do-while Loop ---
 count = 1
 count = 2
 count = 3
 do-while runs at least once even if condition is false:
 Executed once! x = 100

 --- Range-based for (C++11) ---
 10 20 30 40 50 
 Hello, Pavan!
 Hello, Rahul!
 Hello, Priya!
 Hello, Arjun!
 20 40 60 80 100 

 --- Controlled infinite loop ---
 Loop iteration 0
 Loop iteration 1
 Loop iteration 2

 --- Star Triangle ---
 * 
 * * 
 * * * 
 * * * * 
 * * * * * 

 ================================================================
*/

