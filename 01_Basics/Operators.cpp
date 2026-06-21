/*
 * File    : Operators.cpp
 * Author  : Pavan Shetty H S
 * Topic   : All Operators in C++
 * Date    : Week 1 - Day 3
 *
 * Notes:
 *   Most of this was familiar from C. The new things for me were:
 *   - Spaceship operator <=> (C++20, not covered here yet)
 *   - How operator precedence works in complex expressions
 *   - Bitwise ops — very important for embedded systems
 *
 *   Mistake I made early: used = instead of == in if conditions.
 *   Compiler doesn't always warn about this. Always double-check.
 */

#include <iostream>
#include <iomanip>  // for setw() formatting
using namespace std;

int main() {

    cout << "==============================" << endl;
    cout << "   OPERATORS IN C++" << endl;
    cout << "==============================" << endl;

    int a = 15, b = 4;
    cout << "\na = " << a << ", b = " << b << endl;

    // ─────────────────────────────────────────
    // 1. ARITHMETIC OPERATORS
    // ─────────────────────────────────────────
    cout << "\n--- 1. Arithmetic Operators ---" << endl;
    cout << "a + b  = " << (a + b)  << endl;   // Addition
    cout << "a - b  = " << (a - b)  << endl;   // Subtraction
    cout << "a * b  = " << (a * b)  << endl;   // Multiplication
    cout << "a / b  = " << (a / b)  << endl;   // Integer division (3, not 3.75!)
    cout << "a % b  = " << (a % b)  << endl;   // Modulus (remainder)

    // Floating point division
    cout << "(float)a / b = " << (float)a / b << " (actual division)" << endl;

    // ─────────────────────────────────────────
    // 2. INCREMENT / DECREMENT
    // ─────────────────────────────────────────
    cout << "\n--- 2. Increment/Decrement Operators ---" << endl;
    int x = 10;
    cout << "x = " << x << endl;
    cout << "x++ = " << x++ << " (post: use then increment, x is now " << x << ")" << endl;
    cout << "++x = " << ++x << " (pre:  increment then use, x is now " << x << ")" << endl;
    cout << "x-- = " << x-- << " (post: use then decrement, x is now " << x << ")" << endl;
    cout << "--x = " << --x << " (pre:  decrement then use, x is now " << x << ")" << endl;

    // ─────────────────────────────────────────
    // 3. ASSIGNMENT OPERATORS
    // ─────────────────────────────────────────
    cout << "\n--- 3. Assignment Operators ---" << endl;
    int n = 20;
    cout << "n = 20 → n = " << n << endl;
    n += 5;  cout << "n += 5  → n = " << n << endl;
    n -= 3;  cout << "n -= 3  → n = " << n << endl;
    n *= 2;  cout << "n *= 2  → n = " << n << endl;
    n /= 4;  cout << "n /= 4  → n = " << n << endl;
    n %= 4;  cout << "n %= 4  → n = " << n << endl;

    // ─────────────────────────────────────────
    // 4. COMPARISON OPERATORS
    // ─────────────────────────────────────────
    cout << "\n--- 4. Comparison (Relational) Operators ---" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a == b : " << (a == b) << endl;  // Equal to
    cout << "a != b : " << (a != b) << endl;  // Not equal
    cout << "a >  b : " << (a >  b) << endl;  // Greater than
    cout << "a <  b : " << (a <  b) << endl;  // Less than
    cout << "a >= b : " << (a >= b) << endl;  // Greater or equal
    cout << "a <= b : " << (a <= b) << endl;  // Less or equal

    // ─────────────────────────────────────────
    // 5. LOGICAL OPERATORS
    // ─────────────────────────────────────────
    cout << "\n--- 5. Logical Operators ---" << endl;
    bool t = true, f = false;
    cout << "true && false : " << (t && f) << " (AND — both must be true)" << endl;
    cout << "true || false : " << (t || f) << " (OR  — at least one true)" << endl;
    cout << "!true         : " << (!t)     << " (NOT — flips the value)" << endl;

    // Short-circuit evaluation
    cout << "\nShort-circuit: in (false && func()), func() is NOT called" << endl;
    cout << "Short-circuit: in (true  || func()), func() is NOT called" << endl;

    // ─────────────────────────────────────────
    // 6. BITWISE OPERATORS (very useful in embedded!)
    // ─────────────────────────────────────────
    cout << "\n--- 6. Bitwise Operators ---" << endl;
    unsigned int p = 0b00001100;  // 12
    unsigned int q = 0b00001010;  // 10

    cout << "p = " << p << " (binary: 00001100)" << endl;
    cout << "q = " << q << " (binary: 00001010)" << endl;
    cout << "p & q  = " << (p & q)  << " (AND — bit is 1 if both 1)" << endl;
    cout << "p | q  = " << (p | q)  << " (OR  — bit is 1 if either 1)" << endl;
    cout << "p ^ q  = " << (p ^ q)  << " (XOR — bit is 1 if different)" << endl;
    cout << "~p     = " << (~p)     << " (NOT — flips all bits)" << endl;
    cout << "p << 2 = " << (p << 2) << " (left shift, multiply by 4)" << endl;
    cout << "p >> 1 = " << (p >> 1) << " (right shift, divide by 2)" << endl;

    // ─────────────────────────────────────────
    // 7. TERNARY OPERATOR
    // ─────────────────────────────────────────
    cout << "\n--- 7. Ternary Operator ---" << endl;
    int age = 20;
    string status = (age >= 18) ? "Adult" : "Minor";
    cout << "Age " << age << " is: " << status << endl;

    // ─────────────────────────────────────────
    // 8. SIZEOF OPERATOR
    // ─────────────────────────────────────────
    cout << "\n--- 8. sizeof Operator ---" << endl;
    cout << "sizeof(int)    = " << sizeof(int)    << " bytes" << endl;
    cout << "sizeof(double) = " << sizeof(double) << " bytes" << endl;
    cout << "sizeof(char)   = " << sizeof(char)   << " bytes" << endl;

    // ─────────────────────────────────────────
    // 9. OPERATOR PRECEDENCE DEMO
    // ─────────────────────────────────────────
    cout << "\n--- 9. Operator Precedence ---" << endl;
    int result1 = 2 + 3 * 4;        // 14, not 20 (* before +)
    int result2 = (2 + 3) * 4;      // 20 (parentheses first)
    cout << "2 + 3 * 4   = " << result1 << " (* before +)" << endl;
    cout << "(2+3) * 4   = " << result2 << " (parens first)" << endl;

    cout << "\n==============================" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Operators.cpp -o prog
 ================================================================

 ==============================
    OPERATORS IN C++
 ==============================

 a = 15, b = 4

 --- 1. Arithmetic Operators ---
 a + b  = 19
 a - b  = 11
 a * b  = 60
 a / b  = 3
 a % b  = 3
 (float)a / b = 3.75 (actual division)

 --- 2. Increment/Decrement Operators ---
 x = 10
 x++ = 10 (post: use then increment, x is now 11)
 ++x = 12 (pre:  increment then use, x is now 12)
 x-- = 12 (post: use then decrement, x is now 11)
 --x = 10 (pre:  decrement then use, x is now 10)

 --- 3. Assignment Operators ---
 n = 20 → n = 20
 n += 5  → n = 25
 n -= 3  → n = 22
 n *= 2  → n = 44
 n /= 4  → n = 11
 n %= 4  → n = 3

 --- 4. Comparison (Relational) Operators ---
 a = 15, b = 4
 a == b : 0
 a != b : 1
 a >  b : 1
 a <  b : 0
 a >= b : 1
 a <= b : 0

 --- 5. Logical Operators ---
 true && false : 0 (AND — both must be true)
 true || false : 1 (OR  — at least one true)
 !true         : 0 (NOT — flips the value)

 Short-circuit: in (false && func()), func() is NOT called
 Short-circuit: in (true  || func()), func() is NOT called

 --- 6. Bitwise Operators ---
 p = 12 (binary: 00001100)
 q = 10 (binary: 00001010)
 p & q  = 8 (AND — bit is 1 if both 1)
 p | q  = 14 (OR  — bit is 1 if either 1)
 p ^ q  = 6 (XOR — bit is 1 if different)
 ~p     = 4294967283 (NOT — flips all bits)
 p << 2 = 48 (left shift, multiply by 4)
 p >> 1 = 6 (right shift, divide by 2)

 --- 7. Ternary Operator ---
 Age 20 is: Adult

 --- 8. sizeof Operator ---
 sizeof(int)    = 4 bytes
 sizeof(double) = 8 bytes
 sizeof(char)   = 1 bytes

 --- 9. Operator Precedence ---
 2 + 3 * 4   = 14 (* before +)
 (2+3) * 4   = 20 (parens first)

 ==============================

 ================================================================
*/

