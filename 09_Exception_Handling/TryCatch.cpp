/*
 * File    : TryCatch.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Exception handling — try, catch, throw, exception hierarchy
 * Date    : Week 9 - Day 1
 *
 * Notes:
 *   Exceptions = runtime errors that "bubble up" the call stack.
 *   Much cleaner than returning error codes (which people ignore anyway).
 *   Key rule: catch by const reference to avoid slicing and copies.
 */

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

double divide(double a, double b) {
    if (b == 0) throw runtime_error("Division by zero!");
    return a / b;
}

int accessArray(int arr[], int size, int idx) {
    if (idx < 0 || idx >= size)
        throw out_of_range("Index " + to_string(idx) + " out of range [0," + to_string(size-1) + "]");
    return arr[idx];
}

int convertToInt(string s) {
    try {
        return stoi(s);
    } catch (const invalid_argument& e) {
        throw invalid_argument("'" + s + "' is not a valid integer.");
    } catch (const out_of_range& e) {
        throw out_of_range("Number too large for int.");
    }
}

int main() {
    cout << "=== EXCEPTION HANDLING ===" << endl;

    // 1. Basic try-catch
    cout << "\n--- Basic ---" << endl;
    try {
        double result = divide(10, 0);
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << endl;
    }

    // 2. Multiple catch blocks
    cout << "\n--- Multiple Catches ---" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    for (int idx : {2, 7, -1}) {
        try {
            cout << "arr[" << idx << "] = " << accessArray(arr, 5, idx) << endl;
        } catch (const out_of_range& e) {
            cout << "Range error: " << e.what() << endl;
        } catch (...) {
            cout << "Unknown error!" << endl;
        }
    }

    // 3. Exception hierarchy
    cout << "\n--- Standard Exception Hierarchy ---" << endl;
    try {
        throw invalid_argument("bad arg");
    } catch (const logic_error& e) {   // invalid_argument inherits from logic_error
        cout << "logic_error caught: " << e.what() << endl;
    }

    // 4. String-to-int conversion
    cout << "\n--- String Conversion ---" << endl;
    string tests[] = {"42", "abc", "99999999999"};
    for (auto& s : tests) {
        try {
            cout << "'" << s << "' → " << convertToInt(s) << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // 5. Re-throw
    cout << "\n--- Re-throw ---" << endl;
    try {
        try {
            throw runtime_error("original error");
        } catch (const runtime_error& e) {
            cout << "Inner catch: " << e.what() << endl;
            throw;  // re-throw same exception
        }
    } catch (const runtime_error& e) {
        cout << "Outer catch: " << e.what() << endl;
    }

    cout << "\nProgram continues normally after exceptions." << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread TryCatch.cpp -o prog
 ================================================================

 === EXCEPTION HANDLING ===

 --- Basic ---
 Caught: Division by zero!

 --- Multiple Catches ---
 arr[2] = 3
 arr[7] = Range error: Index 7 out of range [0,4]
 arr[-1] = Range error: Index -1 out of range [0,4]

 --- Standard Exception Hierarchy ---
 logic_error caught: bad arg

 --- String Conversion ---
 '42' → 42
 'abc' → Error: 'abc' is not a valid integer.
 '99999999999' → Error: Number too large for int.

 --- Re-throw ---
 Inner catch: original error
 Outer catch: original error

 Program continues normally after exceptions.

 ================================================================
*/

