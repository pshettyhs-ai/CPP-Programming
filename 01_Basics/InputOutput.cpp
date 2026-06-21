/*
 * File    : InputOutput.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Input and Output in C++
 * Date    : Week 1 - Day 4
 *
 * Notes:
 *   cin, cout, and printf — when to use which?
 *   For now I mostly use cout, but printf is faster and I use it
 *   in embedded code. cin can fail silently which tripped me up
 *   a few times. Added cin.clear() and cin.ignore() handling here.
 */

#include <iostream>
#include <iomanip>    // setw, setprecision, fixed, left, right
#include <string>
#include <limits>     // numeric_limits
using namespace std;

int main() {

    cout << "==============================" << endl;
    cout << "   INPUT / OUTPUT IN C++" << endl;
    cout << "==============================" << endl;

    // ─────────────────────────────────────────
    // BASIC OUTPUT with cout
    // ─────────────────────────────────────────
    cout << "\n--- Basic cout Output ---" << endl;
    cout << "Simple string output" << endl;
    cout << "Integer: " << 42 << endl;
    cout << "Double : " << 3.14159 << endl;
    cout << "Char   : " << 'A' << endl;
    cout << "Bool   : " << true << endl;  // prints 1

    // Chaining output
    string name = "Pavan";
    int age = 21;
    cout << "Name: " << name << ", Age: " << age << endl;

    // ─────────────────────────────────────────
    // FORMATTED OUTPUT with iomanip
    // ─────────────────────────────────────────
    cout << "\n--- Formatted Output (iomanip) ---" << endl;

    // Width and alignment
    cout << setw(10) << "Name"  << setw(10) << "Score" << endl;
    cout << setw(10) << "Pavan" << setw(10) << 95      << endl;
    cout << setw(10) << "Rahul" << setw(10) << 88      << endl;
    cout << setw(10) << "Priya" << setw(10) << 92      << endl;

    // Left alignment
    cout << "\n" << left;
    cout << setw(12) << "Product" << setw(10) << "Price" << endl;
    cout << setw(12) << "Laptop"  << setw(10) << 65000  << endl;
    cout << setw(12) << "Phone"   << setw(10) << 22000  << endl;

    cout << right;  // reset to right

    // Decimal precision
    cout << "\n--- Decimal Precision ---" << endl;
    double pi = 3.14159265358979;
    cout << "Default : " << pi << endl;
    cout << fixed << setprecision(2) << "2 decimal: " << pi << endl;
    cout << fixed << setprecision(5) << "5 decimal: " << pi << endl;
    cout << setprecision(6);  // reset

    // ─────────────────────────────────────────
    // BASIC INPUT with cin
    // ─────────────────────────────────────────
    cout << "\n--- cin Input Demo (interactive) ---" << endl;
    cout << "(Skipping actual input in demo mode — showing how it works)\n" << endl;

    // This is how you'd take input:
    // int userAge;
    // cout << "Enter your age: ";
    // cin >> userAge;
    // cout << "You entered: " << userAge << endl;

    // ─────────────────────────────────────────
    // READING A FULL LINE with getline
    // ─────────────────────────────────────────
    cout << "--- getline vs cin ---" << endl;
    cout << "cin >> only reads until first space." << endl;
    cout << "getline() reads the entire line including spaces." << endl;
    cout << "Common mistake: forgetting cin.ignore() before getline()" << endl;

    // Correct way to use getline after cin:
    // cin >> number;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear buffer
    // getline(cin, fullName);  // now works correctly

    // ─────────────────────────────────────────
    // ESCAPE CHARACTERS
    // ─────────────────────────────────────────
    cout << "\n--- Escape Characters ---" << endl;
    cout << "Tab:\tColumn1\tColumn2" << endl;
    cout << "Newline:\n(new line)" << endl;
    cout << "Backslash: \\" << endl;
    cout << "Quote: \"Hello\"" << endl;
    cout << "Alert bell: \a (might beep)" << endl;

    // ─────────────────────────────────────────
    // NUMBER FORMATTING
    // ─────────────────────────────────────────
    cout << "\n--- Number Formatting ---" << endl;
    int num = 255;
    cout << "Decimal    : " << dec << num << endl;   // 255
    cout << "Hexadecimal: " << hex << num << endl;   // ff
    cout << "Octal      : " << oct << num << endl;   // 377
    cout << dec;  // reset back to decimal

    // ─────────────────────────────────────────
    // PRINTF (C-style, still useful)
    // ─────────────────────────────────────────
    cout << "\n--- printf (C-style) ---" << endl;
    printf("Name: %s, Age: %d, GPA: %.2f\n", "Pavan", 21, 3.85);
    printf("Hex: 0x%X, Oct: %o\n", 255, 255);

    cout << "\n==============================" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread InputOutput.cpp -o prog
 ================================================================

 ==============================
    INPUT / OUTPUT IN C++
 ==============================

 --- Basic cout Output ---
 Simple string output
 Integer: 42
 Double : 3.14159
 Char   : A
 Bool   : 1
 Name: Pavan, Age: 21

 --- Formatted Output (iomanip) ---
       Name     Score
      Pavan        95
      Rahul        88
      Priya        92

 Product     Price     
 Laptop      65000     
 Phone       22000     

 --- Decimal Precision ---
 Default : 3.14159
 2 decimal: 3.14
 5 decimal: 3.14159

 --- cin Input Demo (interactive) ---
 (Skipping actual input in demo mode — showing how it works)

 --- getline vs cin ---
 cin >> only reads until first space.
 getline() reads the entire line including spaces.
 Common mistake: forgetting cin.ignore() before getline()

 --- Escape Characters ---
 Tab:	Column1	Column2
 Newline:
 (new line)
 Backslash: \
 Quote: "Hello"
 Alert bell:  (might beep)

 --- Number Formatting ---
 Decimal    : 255
 Hexadecimal: ff
 Octal      : 377

 --- printf (C-style) ---
 Name: Pavan, Age: 21, GPA: 3.85
 Hex: 0xFF, Oct: 377

 ==============================

 ================================================================
*/

