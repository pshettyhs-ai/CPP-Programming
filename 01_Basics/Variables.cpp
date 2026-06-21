/*
 * File    : Variables.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Variables — declaration, scope, storage class
 * Date    : Week 1 - Day 2 (continued)
 */

#include <iostream>
using namespace std;

// Global variable — accessible everywhere in this file
int globalVar = 100;

// Constants — two ways
const double PI = 3.14159;   // C++ const (preferred)
#define MAX_SIZE 50           // C-style macro (avoid when possible)

// Static variable demo
void counterFunction() {
    static int count = 0;  // initialized only once, persists between calls
    count++;
    cout << "Function called " << count << " time(s)" << endl;
}

int main() {

    cout << "--- Variable Scope Demo ---" << endl;

    int localVar = 42;  // local to main

    {
        // Block scope
        int blockVar = 99;
        cout << "Inside block: blockVar = " << blockVar << endl;
        cout << "Inside block: localVar = " << localVar << endl;   // accessible
        cout << "Inside block: globalVar = " << globalVar << endl; // accessible
    }
    // blockVar is NOT accessible here — goes out of scope
    cout << "After block: localVar = " << localVar << endl;

    // Variable shadowing
    int globalVar = 200;  // shadows the global globalVar
    cout << "\nLocal globalVar (shadowed): " << globalVar << endl;
    cout << "Actual global (using ::)  : " << ::globalVar << endl; // scope resolution

    // Constants
    cout << "\nPI = " << PI << endl;
    cout << "MAX_SIZE = " << MAX_SIZE << endl;
    // PI = 3.0;  // Error! Cannot modify const

    // Multiple declarations
    int x, y, z;
    x = y = z = 0;  // chain assignment

    // Static variable demo
    cout << "\n--- Static Variable (persists across calls) ---" << endl;
    counterFunction();
    counterFunction();
    counterFunction();

    // Variable types and initialization styles
    cout << "\n--- Initialization Styles ---" << endl;
    int a = 5;          // copy initialization (C-style)
    int b(10);          // direct initialization
    int c{15};          // brace initialization (C++11, prevents narrowing)
    auto d = 3.14;      // type deduction

    cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;

    // Brace init prevents accidental narrowing:
    // int e{3.14};  // ERROR: narrowing conversion — great for catching bugs

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Variables.cpp -o prog
 ================================================================

 --- Variable Scope Demo ---
 Inside block: blockVar = 99
 Inside block: localVar = 42
 Inside block: globalVar = 100
 After block: localVar = 42

 Local globalVar (shadowed): 200
 Actual global (using ::)  : 100

 PI = 3.14159
 MAX_SIZE = 50

 --- Static Variable (persists across calls) ---
 Function called 1 time(s)
 Function called 2 time(s)
 Function called 3 time(s)

 --- Initialization Styles ---
 a=5 b=10 c=15 d=3.14

 ================================================================
*/

