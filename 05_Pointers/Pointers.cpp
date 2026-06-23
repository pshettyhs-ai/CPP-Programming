/*
 * File    : Pointers.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Pointers — the most important concept in C/C++
 * Date    : Week 4 - Day 1
 *
 * Notes:
 *   Pointers were already familiar from embedded C (HAL drivers use them
 *   everywhere). But C++ adds some extra rules and safer alternatives.
 *   Core idea: a pointer is a variable that stores a memory address.
 *
 *   Coming from Arduino: when you do digitalWrite(pin, HIGH), internally
 *   the HAL code uses pointers to write to hardware registers. So pointers
 *   are literally everywhere in embedded — you just don't always see them.
 */

#include <iostream>
using namespace std;

int main() {
    cout << "=== POINTERS IN C++ ===" << endl;

    // ─────────────────────────────────────────
    // BASICS
    // ─────────────────────────────────────────
    cout << "\n--- Pointer Basics ---" << endl;

    int num = 42;
    int* ptr = &num;    // ptr holds the address of num
                        // & = address-of operator
                        // * in declaration means "this is a pointer to int"

    cout << "num         = " << num   << endl;
    cout << "&num        = " << &num  << " (address of num in memory)" << endl;
    cout << "ptr         = " << ptr   << " (same address, stored in ptr)" << endl;
    cout << "*ptr        = " << *ptr  << " (dereferencing: value at that address)" << endl;

    // Modifying through pointer
    *ptr = 100;
    cout << "After *ptr = 100: num = " << num << " (changed through pointer!)" << endl;

    // ─────────────────────────────────────────
    // NULL / NULLPTR
    // ─────────────────────────────────────────
    cout << "\n--- nullptr (C++11) ---" << endl;
    int* nullPtr = nullptr;  // Modern C++ — use nullptr, not NULL or 0
    cout << "nullPtr = " << nullPtr << endl;

    // Always check before dereferencing
    if (nullPtr != nullptr) {
        cout << *nullPtr << endl;
    } else {
        cout << "Pointer is null — safe, not dereferencing" << endl;
    }

    // ─────────────────────────────────────────
    // POINTER TO DIFFERENT TYPES
    // ─────────────────────────────────────────
    cout << "\n--- Pointer Types ---" << endl;

    double dbl = 3.14;
    char   ch  = 'A';
    bool   bl  = true;

    double* dPtr = &dbl;
    char*   cPtr = &ch;
    bool*   bPtr = &bl;

    cout << "double*: " << *dPtr << endl;
    cout << "char*  : " << *cPtr << endl;
    cout << "bool*  : " << *bPtr << endl;

    // ─────────────────────────────────────────
    // VOID POINTER (generic pointer)
    // ─────────────────────────────────────────
    cout << "\n--- void* (generic pointer) ---" << endl;
    void* vPtr;
    int   intVal   = 99;
    float floatVal = 1.5f;

    vPtr = &intVal;
    cout << "void* storing int: " << *(int*)vPtr << endl;  // must cast

    vPtr = &floatVal;
    cout << "void* storing float: " << *(float*)vPtr << endl;

    // void* is used in C APIs (malloc returns void*) and callbacks

    // ─────────────────────────────────────────
    // POINTER AND ARRAY RELATIONSHIP
    // ─────────────────────────────────────────
    cout << "\n--- Pointers and Arrays ---" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int* aPtr = arr;  // array name IS a pointer to first element

    cout << "Array:   arr[0]=" << arr[0] << " arr[1]=" << arr[1] << endl;
    cout << "Via ptr: *aPtr=" << *aPtr << " *(aPtr+1)=" << *(aPtr+1) << endl;
    cout << "aPtr[2] = " << aPtr[2] << " (pointer subscript same as array subscript)" << endl;

    // ─────────────────────────────────────────
    // POINTER TO POINTER
    // ─────────────────────────────────────────
    cout << "\n--- Pointer to Pointer (**) ---" << endl;
    int   val   = 500;
    int*  p1    = &val;    // pointer to int
    int** p2    = &p1;     // pointer to pointer to int

    cout << "val   = " << val    << endl;
    cout << "*p1   = " << *p1    << endl;
    cout << "**p2  = " << **p2   << endl;
    cout << "Modifying via **p2: ";
    **p2 = 999;
    cout << "val is now " << val << endl;

    // ─────────────────────────────────────────
    // CONST AND POINTERS (4 combinations)
    // ─────────────────────────────────────────
    cout << "\n--- const with Pointers ---" << endl;

    int  x = 10, y = 20;

    int* const cp1 = &x;      // const pointer to int — address fixed, value can change
    *cp1 = 15;                 // OK
    // cp1 = &y;               // ERROR: can't change address

    const int* cp2 = &x;      // pointer to const int — address can change, value read-only
    cp2 = &y;                  // OK
    // *cp2 = 15;              // ERROR: can't change value

    const int* const cp3 = &x; // const pointer to const int — nothing can change
    cout << "cp1=" << *cp1 << " cp2=" << *cp2 << " cp3=" << *cp3 << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Pointers.cpp -o prog
 ================================================================

 === POINTERS IN C++ ===

 --- Pointer Basics ---
 num         = 42
 &num        = 0x7ffe0f2990f4 (address of num in memory)
 ptr         = 0x7ffe0f2990f4 (same address, stored in ptr)
 *ptr        = 42 (dereferencing: value at that address)
 After *ptr = 100: num = 100 (changed through pointer!)

 --- nullptr (C++11) ---
 nullPtr = 0
 Pointer is null — safe, not dereferencing

 --- Pointer Types ---
 double*: 3.14
 char*  : A
 bool*  : 1

 --- void* (generic pointer) ---
 void* storing int: 99
 void* storing float: 1.5

 --- Pointers and Arrays ---
 Array:   arr[0]=10 arr[1]=20
 Via ptr: *aPtr=10 *(aPtr+1)=20
 aPtr[2] = 30 (pointer subscript same as array subscript)

 --- Pointer to Pointer (**) ---
 val   = 500
 *p1   = 500
 **p2  = 500
 Modifying via **p2: val is now 999

 --- const with Pointers ---
 cp1=15 cp2=20 cp3=15

 ================================================================
*/

