/*
 * File    : DataTypes.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Variables and Data Types in C++
 * Date    : Week 1 - Day 2
 *
 * Notes:
 *   Coming from embedded C, I already knew most of this.
 *   But C++ has some extra types like bool, auto, and string
 *   that are different from plain C. Also learnt about type
 *   modifiers (short, long, unsigned) and sizeof() here.
 *
 *   Important observation: size of data types can vary by
 *   platform/compiler! Always check with sizeof() if it matters.
 *   In embedded systems this is critical — use int8_t, uint32_t etc.
 */

#include <iostream>
#include <string>
#include <limits>   // for numeric_limits — shows min/max values
#include <climits>  // INT_MAX, INT_MIN etc.
using namespace std;

int main() {

    cout << "======================================" << endl;
    cout << "   C++ DATA TYPES EXPLORATION" << endl;
    cout << "======================================" << endl;

    // ─────────────────────────────────────────
    // INTEGER TYPES
    // ─────────────────────────────────────────
    cout << "\n--- Integer Types ---" << endl;

    short s = 32767;           // 2 bytes: -32768 to 32767
    int i = 2147483647;        // 4 bytes: ~ ±2.1 billion
    long l = 2147483647L;      // 4 or 8 bytes depending on platform
    long long ll = 9223372036854775807LL;  // 8 bytes: huge range

    cout << "short       : " << s  << " (size: " << sizeof(s)  << " bytes)" << endl;
    cout << "int         : " << i  << " (size: " << sizeof(i)  << " bytes)" << endl;
    cout << "long        : " << l  << " (size: " << sizeof(l)  << " bytes)" << endl;
    cout << "long long   : " << ll << " (size: " << sizeof(ll) << " bytes)" << endl;

    // Unsigned — no negative values, double the positive range
    unsigned int ui = 4294967295U;  // 0 to 4,294,967,295
    cout << "unsigned int: " << ui << " (size: " << sizeof(ui) << " bytes)" << endl;

    // ─────────────────────────────────────────
    // FLOATING POINT TYPES
    // ─────────────────────────────────────────
    cout << "\n--- Floating Point Types ---" << endl;

    float  f   = 3.14159f;       // 4 bytes, ~7 digits precision
    double d   = 3.14159265358;  // 8 bytes, ~15 digits precision
    long double ld = 3.14159265358979323846L; // 16 bytes (on most systems)

    cout << "float       : " << f  << " (size: " << sizeof(f)  << " bytes)" << endl;
    cout << "double      : " << d  << " (size: " << sizeof(d)  << " bytes)" << endl;
    cout << "long double : " << ld << " (size: " << sizeof(ld) << " bytes)" << endl;

    // Precision demo — why float can be inaccurate
    float x = 0.1f + 0.2f;
    cout << "\nfloat 0.1 + 0.2 = " << x << " (not exactly 0.3!)" << endl;
    // This is a classic floating point precision issue

    // ─────────────────────────────────────────
    // CHARACTER TYPE
    // ─────────────────────────────────────────
    cout << "\n--- Character Type ---" << endl;

    char c1 = 'A';
    char c2 = 65;   // ASCII value — same as 'A'
    char c3 = '\n'; // escape character

    cout << "char 'A'    : " << c1 << " (ASCII: " << (int)c1 << ")" << endl;
    cout << "char 65     : " << c2 << " (ASCII: " << (int)c2 << ")" << endl;
    cout << "char size   : " << sizeof(c1) << " byte" << endl;

    // ─────────────────────────────────────────
    // BOOLEAN TYPE
    // ─────────────────────────────────────────
    cout << "\n--- Boolean Type ---" << endl;

    bool b1 = true;
    bool b2 = false;
    bool b3 = (5 > 3);  // expression result

    cout << "true        : " << b1 << " (stored as 1)" << endl;
    cout << "false       : " << b2 << " (stored as 0)" << endl;
    cout << "5 > 3       : " << b3 << endl;
    cout << "bool size   : " << sizeof(b1) << " byte" << endl;

    // ─────────────────────────────────────────
    // STRING TYPE (C++ specific, not in C)
    // ─────────────────────────────────────────
    cout << "\n--- String Type ---" << endl;

    string name = "Pavan Shetty H S";
    string role = "Aspiring Software Engineer";

    cout << "Name   : " << name << endl;
    cout << "Role   : " << role << endl;
    cout << "Length : " << name.length() << " characters" << endl;

    // ─────────────────────────────────────────
    // AUTO KEYWORD (C++11)
    // ─────────────────────────────────────────
    cout << "\n--- auto keyword (C++11) ---" << endl;

    auto autoInt    = 42;
    auto autoDouble = 3.14;
    auto autoStr    = string("Hello");
    auto autoBool   = true;

    cout << "auto int    : " << autoInt    << " (type deduced at compile time)" << endl;
    cout << "auto double : " << autoDouble << endl;
    cout << "auto string : " << autoStr    << endl;

    // ─────────────────────────────────────────
    // TYPE LIMITS
    // ─────────────────────────────────────────
    cout << "\n--- Type Limits ---" << endl;
    cout << "INT_MAX     : " << INT_MAX  << endl;
    cout << "INT_MIN     : " << INT_MIN  << endl;
    cout << "CHAR_MAX    : " << CHAR_MAX << endl;

    // ─────────────────────────────────────────
    // TYPE CASTING
    // ─────────────────────────────────────────
    cout << "\n--- Type Casting ---" << endl;

    int  intVal   = 42;
    double doubleVal = (double)intVal;   // C-style cast
    double doubleVal2 = static_cast<double>(intVal); // C++ style (preferred)

    cout << "int to double (C-style)  : " << doubleVal  << endl;
    cout << "int to double (C++ style): " << doubleVal2 << endl;

    // Narrowing cast — data loss!
    double bigDecimal = 9.99;
    int    truncated  = (int)bigDecimal;
    cout << "9.99 cast to int: " << truncated << " (decimal part lost!)" << endl;

    cout << "\n======================================" << endl;
    cout << "   Tip: Use <cstdint> types in" << endl;
    cout << "   embedded: int8_t, uint32_t etc." << endl;
    cout << "======================================" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread DataTypes.cpp -o prog
 ================================================================

 ======================================
    C++ DATA TYPES EXPLORATION
 ======================================

 --- Integer Types ---
 short       : 32767 (size: 2 bytes)
 int         : 2147483647 (size: 4 bytes)
 long        : 2147483647 (size: 8 bytes)
 long long   : 9223372036854775807 (size: 8 bytes)
 unsigned int: 4294967295 (size: 4 bytes)

 --- Floating Point Types ---
 float       : 3.14159 (size: 4 bytes)
 double      : 3.14159 (size: 8 bytes)
 long double : 3.14159 (size: 16 bytes)

 float 0.1 + 0.2 = 0.3 (not exactly 0.3!)

 --- Character Type ---
 char 'A'    : A (ASCII: 65)
 char 65     : A (ASCII: 65)
 char size   : 1 byte

 --- Boolean Type ---
 true        : 1 (stored as 1)
 false       : 0 (stored as 0)
 5 > 3       : 1
 bool size   : 1 byte

 --- String Type ---
 Name   : Pavan Shetty H S
 Role   : Aspiring Software Engineer
 Length : 16 characters

 --- auto keyword (C++11) ---
 auto int    : 42 (type deduced at compile time)
 auto double : 3.14
 auto string : Hello

 --- Type Limits ---
 INT_MAX     : 2147483647
 INT_MIN     : -2147483648
 CHAR_MAX    : 127

 --- Type Casting ---
 int to double (C-style)  : 42
 int to double (C++ style): 42
 9.99 cast to int: 9 (decimal part lost!)

 ======================================
    Tip: Use <cstdint> types in
    embedded: int8_t, uint32_t etc.
 ======================================

 ================================================================
*/

