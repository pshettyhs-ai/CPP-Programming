/*
 * File    : DynamicMemory.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Dynamic Memory Allocation — new, delete, memory leaks
 * Date    : Week 4 - Day 2
 *
 * Notes:
 *   Stack memory is automatic — variables are created/destroyed automatically.
 *   Heap memory (dynamic) is manual — YOU are responsible for freeing it.
 *   Forgetting delete = memory leak. Deleting twice = undefined behavior (crash).
 *   
 *   Modern C++: use smart pointers instead of raw new/delete whenever possible.
 *   (Covered in 10_Modern_CPP/SmartPointers.cpp)
 *
 *   In embedded: dynamic memory is often avoided completely because:
 *   - Heap fragmentation over time
 *   - Non-deterministic allocation time
 *   - Limited RAM
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "=== DYNAMIC MEMORY ALLOCATION ===" << endl;

    // ─────────────────────────────────────────
    // Stack vs Heap
    // ─────────────────────────────────────────
    cout << "\n--- Stack vs Heap ---" << endl;
    int stackVar = 100;       // lives on STACK, auto-destroyed when out of scope
    int* heapVar = new int;   // lives on HEAP, YOU must free it
    *heapVar = 200;

    cout << "Stack var: " << stackVar  << " (at " << &stackVar << ")" << endl;
    cout << "Heap var : " << *heapVar  << " (at " << heapVar   << ")" << endl;

    delete heapVar;           // free heap memory
    heapVar = nullptr;        // good practice: set to null after delete
    cout << "Heap memory freed." << endl;

    // ─────────────────────────────────────────
    // SINGLE OBJECT
    // ─────────────────────────────────────────
    cout << "\n--- new / delete for Single Object ---" << endl;

    double* dPtr = new double(3.14159);   // allocate AND initialize
    cout << "Dynamic double: " << *dPtr << endl;
    delete dPtr;
    dPtr = nullptr;

    string* sPtr = new string("Hello Heap!");
    cout << "Dynamic string: " << *sPtr << endl;
    delete sPtr;
    sPtr = nullptr;

    // ─────────────────────────────────────────
    // DYNAMIC ARRAYS
    // ─────────────────────────────────────────
    cout << "\n--- Dynamic Arrays ---" << endl;

    int size;
    cout << "Allocating array of size 5 dynamically..." << endl;
    size = 5;

    int* arr = new int[size];  // allocate array on heap

    // Initialize
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }

    // Access
    cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;   // IMPORTANT: use delete[] for arrays (not just delete)
    arr = nullptr;

    // ─────────────────────────────────────────
    // DYNAMIC 2D ARRAY
    // ─────────────────────────────────────────
    cout << "\n--- Dynamic 2D Array ---" << endl;

    int rows = 3, cols = 4;

    // Allocate: array of pointers, each pointing to a row
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Fill
    int val = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = val++;

    // Print
    cout << "2D dynamic matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout.width(4);
            cout << matrix[i][j];
        }
        cout << endl;
    }

    // Free: must delete each row first, then array of pointers
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;

    // ─────────────────────────────────────────
    // MEMORY LEAK DEMO (what NOT to do)
    // ─────────────────────────────────────────
    cout << "\n--- Memory Leak (what to AVOID) ---" << endl;
    cout << "BAD: allocating without freeing:" << endl;
    cout << "  int* leak = new int(42);" << endl;
    cout << "  // Forgot to delete leak! → Memory leak" << endl;
    cout << "" << endl;
    cout << "BAD: double delete:" << endl;
    cout << "  delete ptr;" << endl;
    cout << "  delete ptr;  // undefined behavior — crash!" << endl;
    cout << "" << endl;
    cout << "GOOD: always delete, then set to nullptr" << endl;
    cout << "BETTER: use smart pointers (unique_ptr, shared_ptr)" << endl;

    cout << "\n=== All memory properly freed. ===" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread DynamicMemory.cpp -o prog
 ================================================================

 === DYNAMIC MEMORY ALLOCATION ===

 --- Stack vs Heap ---
 Stack var: 100 (at 0x7ffd0a72b194)
 Heap var : 200 (at 0x55e357e662c0)
 Heap memory freed.

 --- new / delete for Single Object ---
 Dynamic double: 3.14159
 Dynamic string: Hello Heap!

 --- Dynamic Arrays ---
 Allocating array of size 5 dynamically...
 Dynamic array: 10 20 30 40 50 

 --- Dynamic 2D Array ---
 2D dynamic matrix:
    1   2   3   4
    5   6   7   8
    9  10  11  12

 --- Memory Leak (what to AVOID) ---
 BAD: allocating without freeing:
   int* leak = new int(42);
   // Forgot to delete leak! → Memory leak

 BAD: double delete:
   delete ptr;
   delete ptr;  // undefined behavior — crash!

 GOOD: always delete, then set to nullptr
 BETTER: use smart pointers (unique_ptr, shared_ptr)

 === All memory properly freed. ===

 ================================================================
*/

