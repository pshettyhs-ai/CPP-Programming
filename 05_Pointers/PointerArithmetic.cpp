/*
 * File    : PointerArithmetic.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Pointer Arithmetic — traversing memory
 * Date    : Week 4 - Day 2
 *
 * Notes:
 *   When you do ptr++, it doesn't add 1 to the address.
 *   It adds sizeof(type) bytes. So int* ptr++  adds 4 bytes,
 *   double* ptr++ adds 8 bytes. This is what makes pointer
 *   arithmetic work with arrays.
 *
 *   In embedded (STM32 HAL): register banks are contiguous,
 *   and the HAL uses pointer arithmetic to access them.
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "=== POINTER ARITHMETIC ===" << endl;

    // ─────────────────────────────────────────
    // INCREMENT / DECREMENT
    // ─────────────────────────────────────────
    cout << "\n--- Increment/Decrement ---" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;   // points to arr[0]

    cout << "ptr   → " << *ptr << " at " << ptr << endl;
    ptr++;  // advance by sizeof(int) = 4 bytes
    cout << "ptr++ → " << *ptr << " at " << ptr << endl;
    ptr++;
    cout << "ptr++ → " << *ptr << " at " << ptr << endl;
    ptr--;
    cout << "ptr-- → " << *ptr << " at " << ptr << endl;

    // ─────────────────────────────────────────
    // ADDITION / SUBTRACTION
    // ─────────────────────────────────────────
    cout << "\n--- Addition / Subtraction ---" << endl;
    int* p = arr;
    cout << "*(p+0) = " << *(p+0) << endl;
    cout << "*(p+1) = " << *(p+1) << endl;
    cout << "*(p+4) = " << *(p+4) << endl;

    // ─────────────────────────────────────────
    // DIFFERENCE BETWEEN POINTERS
    // ─────────────────────────────────────────
    cout << "\n--- Pointer Difference ---" << endl;
    int* start = arr;
    int* end   = arr + 5;
    cout << "end - start = " << (end - start) << " elements" << endl;

    // ─────────────────────────────────────────
    // TRAVERSING ARRAY WITH POINTER
    // ─────────────────────────────────────────
    cout << "\n--- Array Traversal via Pointer ---" << endl;
    cout << "Array: ";
    for (int* p = arr; p < arr + 5; p++) {
        cout << *p << " ";
    }
    cout << endl;

    // ─────────────────────────────────────────
    // DIFFERENT TYPE SIZES
    // ─────────────────────────────────────────
    cout << "\n--- Type Size Effect ---" << endl;
    char   charArr[]   = {'A', 'B', 'C'};
    double doubleArr[] = {1.1, 2.2, 3.3};

    char*   cPtr = charArr;
    double* dPtr = doubleArr;

    cout << "char*   +1 jumps: " << sizeof(char)   << " byte(s)" << endl;
    cout << "double* +1 jumps: " << sizeof(double) << " byte(s)" << endl;
    cout << "cPtr:  " << (void*)cPtr << " → " << (void*)(cPtr+1)
         << " (diff=" << ((char*)(cPtr+1) - (char*)cPtr) << ")" << endl;
    cout << "dPtr:  " << dPtr << " → " << (dPtr+1)
         << " (diff=" << ((char*)(dPtr+1) - (char*)dPtr) << ")" << endl;

    // ─────────────────────────────────────────
    // POINTER COMPARISON
    // ─────────────────────────────────────────
    cout << "\n--- Pointer Comparison ---" << endl;
    int* pFirst = &arr[0];
    int* pLast  = &arr[4];
    cout << "pFirst < pLast: " << (pFirst < pLast ? "true" : "false") << endl;
    cout << "pFirst == arr:  " << (pFirst == arr  ? "true" : "false") << endl;

    // ─────────────────────────────────────────
    // STRLEN IMPLEMENTATION USING POINTER
    // ─────────────────────────────────────────
    cout << "\n--- Custom strlen using pointer ---" << endl;
    auto myStrlen = [](const char* s) -> size_t {
        const char* p = s;
        while (*p != '\0') p++;
        return p - s;
    };
    cout << "myStrlen(\"hello\") = " << myStrlen("hello") << endl;
    cout << "myStrlen(\"Pavan\") = " << myStrlen("Pavan") << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread PointerArithmetic.cpp -o prog
 ================================================================

 === POINTER ARITHMETIC ===

 --- Increment/Decrement ---
 ptr   → 10 at 0x7ffe6592e360
 ptr++ → 20 at 0x7ffe6592e364
 ptr++ → 30 at 0x7ffe6592e368
 ptr-- → 20 at 0x7ffe6592e364

 --- Addition / Subtraction ---
 *(p+0) = 10
 *(p+1) = 20
 *(p+4) = 50

 --- Pointer Difference ---
 end - start = 5 elements

 --- Array Traversal via Pointer ---
 Array: 10 20 30 40 50 

 --- Type Size Effect ---
 char*   +1 jumps: 1 byte(s)
 double* +1 jumps: 8 byte(s)
 cPtr:  0x7ffe6592e3a5 → 0x7ffe6592e3a6 (diff=1)
 dPtr:  0x7ffe6592e380 → 0x7ffe6592e388 (diff=8)

 --- Pointer Comparison ---
 pFirst < pLast: true
 pFirst == arr:  true

 --- Custom strlen using pointer ---
 myStrlen("hello") = 5
 myStrlen("Pavan") = 5

 ================================================================
*/

