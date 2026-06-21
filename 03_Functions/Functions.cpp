/*
 * File    : Functions.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Functions — declaration, definition, pass by value/ref/pointer
 * Date    : Week 3 - Day 1
 *
 * Notes:
 *   Pass by value vs pass by reference was confusing at first.
 *   The key insight: pass by value copies the data, pass by reference
 *   gives the function direct access to the original variable.
 *   In embedded, I always pass large structs by pointer/reference
 *   to avoid copying on the stack.
 */

#include <iostream>
#include <string>
using namespace std;

// Function declarations (prototypes) — defined below main
int add(int a, int b);
void swapByValue(int a, int b);
void swapByReference(int& a, int& b);
void swapByPointer(int* a, int* b);
int factorial(int n);
double circleArea(double radius);
string greet(string name, string title = "Mr.");  // default argument

// Overloaded functions — same name, different parameters
int    multiply(int a, int b);
double multiply(double a, double b);
int    multiply(int a, int b, int c);

// Inline function (hint to compiler to expand inline, avoids function call overhead)
inline int square(int x) { return x * x; }

int main() {
    cout << "=== FUNCTIONS IN C++ ===" << endl;

    // 1. Basic function call
    cout << "\n--- Basic Function ---" << endl;
    int result = add(15, 27);
    cout << "add(15, 27) = " << result << endl;

    // 2. Pass by value vs reference vs pointer
    cout << "\n--- Pass by Value, Reference, Pointer ---" << endl;
    int x = 10, y = 20;
    cout << "Before swap: x=" << x << ", y=" << y << endl;

    swapByValue(x, y);
    cout << "After swapByValue: x=" << x << ", y=" << y << " (unchanged!)" << endl;

    swapByReference(x, y);
    cout << "After swapByReference: x=" << x << ", y=" << y << " (swapped!)" << endl;

    swapByPointer(&x, &y);
    cout << "After swapByPointer: x=" << x << ", y=" << y << " (swapped back!)" << endl;

    // 3. Default arguments
    cout << "\n--- Default Arguments ---" << endl;
    cout << greet("Pavan") << endl;           // uses default "Mr."
    cout << greet("Priya", "Ms.") << endl;    // overrides default

    // 4. Function overloading
    cout << "\n--- Function Overloading ---" << endl;
    cout << "multiply(3, 4)       = " << multiply(3, 4)         << endl;
    cout << "multiply(2.5, 3.0)   = " << multiply(2.5, 3.0)     << endl;
    cout << "multiply(2, 3, 4)    = " << multiply(2, 3, 4)      << endl;

    // 5. Inline function
    cout << "\n--- Inline Function ---" << endl;
    cout << "square(7) = " << square(7) << endl;

    // 6. Math examples
    cout << "\n--- Real-world Examples ---" << endl;
    cout << "factorial(6) = " << factorial(6) << endl;
    cout << "circleArea(5.0) = " << circleArea(5.0) << endl;

    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

void swapByValue(int a, int b) {
    // These are copies — original variables unaffected
    int temp = a;
    a = b;
    b = temp;
    cout << "Inside swapByValue: a=" << a << ", b=" << b << " (local only)" << endl;
}

void swapByReference(int& a, int& b) {
    // & means a and b ARE the original variables (just aliases)
    int temp = a;
    a = b;
    b = temp;
}

void swapByPointer(int* a, int* b) {
    // * dereferences the pointer to access the actual value
    int temp = *a;
    *a = *b;
    *b = temp;
}

int factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

double circleArea(double radius) {
    const double PI = 3.14159265358979;
    return PI * radius * radius;
}

string greet(string name, string title) {
    return "Hello, " + title + " " + name + "!";
}

int multiply(int a, int b)           { return a * b; }
double multiply(double a, double b)  { return a * b; }
int multiply(int a, int b, int c)    { return a * b * c; }

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Functions.cpp -o prog
 ================================================================

 === FUNCTIONS IN C++ ===

 --- Basic Function ---
 add(15, 27) = 42

 --- Pass by Value, Reference, Pointer ---
 Before swap: x=10, y=20
 Inside swapByValue: a=20, b=10 (local only)
 After swapByValue: x=10, y=20 (unchanged!)
 After swapByReference: x=20, y=10 (swapped!)
 After swapByPointer: x=10, y=20 (swapped back!)

 --- Default Arguments ---
 Hello, Mr. Pavan!
 Hello, Ms. Priya!

 --- Function Overloading ---
 multiply(3, 4)       = 12
 multiply(2.5, 3.0)   = 7.5
 multiply(2, 3, 4)    = 24

 --- Inline Function ---
 square(7) = 49

 --- Real-world Examples ---
 factorial(6) = 720
 circleArea(5.0) = 78.5398

 ================================================================
*/

