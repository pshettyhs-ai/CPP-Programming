/*
 * File    : HelloWorld.cpp
 * Author  : Pavan Shetty H S
 * Topic   : First C++ program + understanding compilation
 * Date    : Week 1 - Day 1
 *
 * Notes:
 *   This looks simple but there's actually a lot happening here.
 *   When I first started C++, I just typed this and moved on.
 *   But later I went back and properly understood what each line means.
 *   Leaving detailed comments here for future reference.
 *
 * Compilation:
 *   g++ -std=c++17 HelloWorld.cpp -o hello
 *   ./hello
 */

// This includes the standard input/output stream library
// Without this, cout won't work. It's part of the C++ Standard Library.
#include <iostream>

// 'std' is a namespace. cout and endl live inside it.
// Using this means I don't have to write std::cout every time.
// But in larger projects, 'using namespace std' is avoided because
// it can cause naming conflicts. Learnt this the hard way.
using namespace std;

// Every C++ program must have a main() function.
// The OS calls main() when you run the program.
// It returns int — 0 means success, non-zero means error.
int main() {

    // cout = "character output" — prints to terminal
    // << is the insertion/stream operator
    // endl flushes the buffer AND adds newline
    // "\n" just adds newline (slightly faster, no flush)
    cout << "Hello, World!" << endl;

    // A bit more exploration:
    cout << "Hello from Pavan Shetty H S!" << endl;
    cout << "Learning C++ step by step." << endl;

    // You can chain multiple << operators
    cout << "Name: " << "Pavan" << " | " << "Language: " << "C++" << endl;

    // Difference between endl and \n
    cout << "Line 1\n";   // faster, just newline
    cout << "Line 2" << endl;  // adds newline + flushes buffer

    // Return 0 to indicate successful execution
    return 0;
}

/*
 * Expected Output:
 * ─────────────────────────────
 * Hello, World!
 * Hello from Pavan Shetty H S!
 * Learning C++ step by step.
 * Name: Pavan | Language: C++
 * Line 1
 * Line 2
 * ─────────────────────────────
 *
 * Compilation Process (what actually happens):
 * 1. Preprocessor → handles #include, #define, etc.
 * 2. Compiler     → converts .cpp to assembly (.s)
 * 3. Assembler    → converts assembly to object file (.o)
 * 4. Linker       → links .o with libraries → executable
 *
 * This is why sometimes errors say "undefined reference" —
 * that's a linker error, not a compiler error!
 */

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread HelloWorld.cpp -o prog
 ================================================================

 Hello, World!
 Hello from Pavan Shetty H S!
 Learning C++ step by step.
 Name: Pavan | Language: C++
 Line 1
 Line 2

 ================================================================
*/

