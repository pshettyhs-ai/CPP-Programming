/*
 * File    : InlineFunctions.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Inline functions — what they are, when to use them
 * Date    : Week 3 - Day 3
 *
 * Notes:
 *   inline tells the compiler to substitute the function body at call site.
 *   This avoids function call overhead (no stack frame push/pop).
 *   Good for tiny, frequently called functions.
 *   The compiler can IGNORE the inline hint though — it decides.
 *   In embedded systems, __attribute__((always_inline)) forces it.
 */

#include <iostream>
using namespace std;

// Regular function — has call overhead
int squareRegular(int x) {
    return x * x;
}

// Inline function — compiler may expand in-place
inline int squareInline(int x) {
    return x * x;
}

inline int maxOf(int a, int b) {
    return (a > b) ? a : b;
}

inline double toRadians(double degrees) {
    return degrees * 3.14159265358979 / 180.0;
}

// Template inline (common pattern)
template<typename T>
inline T absolute(T val) {
    return (val < 0) ? -val : val;
}

int main() {
    cout << "=== INLINE FUNCTIONS ===" << endl;

    cout << "squareRegular(7)  = " << squareRegular(7)  << endl;
    cout << "squareInline(7)   = " << squareInline(7)   << endl;
    cout << "maxOf(15, 9)      = " << maxOf(15, 9)      << endl;
    cout << "toRadians(90)     = " << toRadians(90)     << endl;
    cout << "absolute(-42)     = " << absolute(-42)     << endl;
    cout << "absolute(-3.14)   = " << absolute(-3.14)   << endl;

    cout << "\nNote: inline is a suggestion to the compiler." << endl;
    cout << "It can ignore it for complex functions." << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread InlineFunctions.cpp -o prog
 ================================================================

 === INLINE FUNCTIONS ===
 squareRegular(7)  = 49
 squareInline(7)   = 49
 maxOf(15, 9)      = 15
 toRadians(90)     = 1.5708
 absolute(-42)     = 42
 absolute(-3.14)   = 3.14

 Note: inline is a suggestion to the compiler.
 It can ignore it for complex functions.

 ================================================================
*/

