/*
 * File    : IfElse.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Decision Making — if, else if, else, nested if
 * Date    : Week 2 - Day 1
 */

#include <iostream>
using namespace std;

int main() {
    cout << "=== IF-ELSE STATEMENTS ===" << endl;

    // 1. Simple if
    int marks = 78;
    if (marks >= 60) {
        cout << "Passed!" << endl;
    }

    // 2. if-else
    int temperature = 38;
    if (temperature > 37) {
        cout << "Fever detected!" << endl;
    } else {
        cout << "Normal temperature." << endl;
    }

    // 3. if - else if - else ladder
    int score = 82;
    char grade;
    if      (score >= 90) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else                  grade = 'F';

    cout << "Score: " << score << " → Grade: " << grade << endl;

    // 4. Nested if
    int age = 22;
    bool hasLicense = true;
    if (age >= 18) {
        if (hasLicense) {
            cout << "You can drive." << endl;
        } else {
            cout << "Old enough, but no license." << endl;
        }
    } else {
        cout << "Too young to drive." << endl;
    }

    // 5. if with logical operators
    int num = 0;
    if (num > 0) {
        cout << "Positive" << endl;
    } else if (num < 0) {
        cout << "Negative" << endl;
    } else {
        cout << "Zero" << endl;
    }

    // 6. Ternary as shorthand
    int a = 10, b = 20;
    int maxVal = (a > b) ? a : b;
    cout << "Max of " << a << " and " << b << " is: " << maxVal << endl;

    // 7. Common pitfall: assignment in condition
    int x = 5;
    // if (x = 10) {}   ← This ASSIGNS 10 to x, doesn't compare!
    // if (x == 10) {}  ← This COMPARES x with 10 — correct
    // Tip: write "10 == x" (Yoda condition) to avoid the bug

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread IfElse.cpp -o prog
 ================================================================

 === IF-ELSE STATEMENTS ===
 Passed!
 Fever detected!
 Score: 82 → Grade: B
 You can drive.
 Zero
 Max of 10 and 20 is: 20

 ================================================================
*/

