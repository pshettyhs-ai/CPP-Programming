/*
 * File    : BreakContinue.cpp
 * Author  : Pavan Shetty H S
 * Topic   : break, continue, and goto (and why goto is avoided)
 * Date    : Week 2 - Day 2
 */

#include <iostream>
using namespace std;

int main() {
    cout << "=== BREAK, CONTINUE, GOTO ===" << endl;

    // 1. break — exits the loop entirely
    cout << "\n--- break ---" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            cout << "Found 6! Breaking out." << endl;
            break;
        }
        cout << i << " ";
    }
    cout << endl;

    // Find first negative number
    int arr[] = {3, 7, 2, -4, 8, -1, 5};
    for (int val : arr) {
        if (val < 0) {
            cout << "First negative: " << val << endl;
            break;
        }
    }

    // 2. continue — skips current iteration, goes to next
    cout << "\n--- continue ---" << endl;
    cout << "Even numbers 1-10: ";
    for (int i = 1; i <= 10; i++) {
        if (i % 2 != 0) continue;  // skip odd numbers
        cout << i << " ";
    }
    cout << endl;

    // Skip multiples of 3
    cout << "Numbers 1-15, skip multiples of 3: ";
    for (int i = 1; i <= 15; i++) {
        if (i % 3 == 0) continue;
        cout << i << " ";
    }
    cout << endl;

    // 3. break in nested loops — only breaks innermost
    cout << "\n--- break in nested loops ---" << endl;
    bool found = false;
    int target = 15;
    for (int i = 1; i <= 5 && !found; i++) {
        for (int j = 1; j <= 5; j++) {
            if (i * j == target) {
                cout << "Found: " << i << " x " << j << " = " << target << endl;
                found = true;
                break;  // breaks inner, outer terminates via !found
            }
        }
    }

    // 4. goto — technically exists but universally avoided
    cout << "\n--- goto (shown for awareness, rarely used) ---" << endl;
    int k = 0;
    loop_start:  // label
        if (k < 3) {
            cout << "goto loop k=" << k << endl;
            k++;
            goto loop_start;
        }
    // Note: goto can lead to "spaghetti code" — avoid in modern C++
    // Exception: some embedded/C code uses it for error cleanup

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread BreakContinue.cpp -o prog
 ================================================================

 === BREAK, CONTINUE, GOTO ===

 --- break ---
 1 2 3 4 5 Found 6! Breaking out.

 First negative: -4

 --- continue ---
 Even numbers 1-10: 2 4 6 8 10 
 Numbers 1-15, skip multiples of 3: 1 2 4 5 7 8 10 11 13 14 

 --- break in nested loops ---
 Found: 3 x 5 = 15

 --- goto (shown for awareness, rarely used) ---
 goto loop k=0
 goto loop k=1
 goto loop k=2

 ================================================================
*/

