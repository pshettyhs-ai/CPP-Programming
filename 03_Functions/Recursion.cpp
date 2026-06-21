/*
 * File    : Recursion.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Recursion — how it works, when to use it, pitfalls
 * Date    : Week 3 - Day 2
 *
 * Notes:
 *   Recursion clicked for me when I thought of it as:
 *   "The function calls itself with a simpler version of the problem
 *    until it hits a base case it can answer directly."
 *
 *   Key components:
 *   1. Base case     — the simplest case where recursion stops
 *   2. Recursive case — the function calling itself with simpler input
 *
 *   Common mistake: forgetting the base case → stack overflow!
 */

#include <iostream>
using namespace std;

// --- Basic Recursion Examples ---

// 1. Factorial
long long factorial(int n) {
    if (n <= 1) return 1;         // base case
    return n * factorial(n - 1);  // recursive case
}

// 2. Fibonacci
int fibonacci(int n) {
    if (n <= 0) return 0;           // base case 1
    if (n == 1) return 1;           // base case 2
    return fibonacci(n-1) + fibonacci(n-2);  // recursive case
    // Warning: this is O(2^n) — very slow for large n!
}

// 3. Power function
double power(double base, int exp) {
    if (exp == 0) return 1;              // base case: x^0 = 1
    if (exp < 0)  return 1.0 / power(base, -exp);  // negative exponent
    return base * power(base, exp - 1); // recursive case
}

// 4. Sum of digits
int sumOfDigits(int n) {
    if (n < 10) return n;               // base case: single digit
    return (n % 10) + sumOfDigits(n / 10);  // last digit + rest
}

// 5. Reverse a string
string reverseString(string s) {
    if (s.length() <= 1) return s;      // base case
    return reverseString(s.substr(1)) + s[0];  // move first char to end
}

// 6. Binary search (recursive)
int binarySearch(int arr[], int low, int high, int target) {
    if (low > high) return -1;          // base case: not found
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid; // base case: found
    if (arr[mid] > target)  return binarySearch(arr, low, mid - 1, target);
    else                    return binarySearch(arr, mid + 1, high, target);
}

// 7. Tower of Hanoi — classic recursion problem
int hanoiMoves = 0;
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "  Move disk 1 from " << from << " to " << to << endl;
        hanoiMoves++;
        return;
    }
    towerOfHanoi(n - 1, from, aux, to);   // move n-1 disks to aux
    cout << "  Move disk " << n << " from " << from << " to " << to << endl;
    hanoiMoves++;
    towerOfHanoi(n - 1, aux, to, from);   // move n-1 disks from aux to dest
}

int main() {
    cout << "=== RECURSION ===" << endl;

    // Factorial
    cout << "\n--- Factorial ---" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }

    // Fibonacci
    cout << "\n--- Fibonacci Sequence ---" << endl;
    cout << "First 10: ";
    for (int i = 0; i < 10; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    cout << "(Note: this recursive version is O(2^n) - very slow for n>30)" << endl;

    // Power
    cout << "\n--- Power Function ---" << endl;
    cout << "2^10 = " << power(2, 10) << endl;
    cout << "3^5  = " << power(3, 5)  << endl;
    cout << "2^-3 = " << power(2, -3) << endl;

    // Sum of digits
    cout << "\n--- Sum of Digits ---" << endl;
    cout << "sumOfDigits(12345) = " << sumOfDigits(12345) << endl;
    cout << "sumOfDigits(9999)  = " << sumOfDigits(9999)  << endl;

    // Reverse string
    cout << "\n--- Reverse String ---" << endl;
    cout << "reverse('hello') = " << reverseString("hello") << endl;
    cout << "reverse('Pavan') = " << reverseString("Pavan") << endl;

    // Binary search
    cout << "\n--- Binary Search (Recursive) ---" << endl;
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int idx = binarySearch(arr, 0, 9, 23);
    cout << "Search 23 → found at index " << idx << endl;
    cout << "Search 50 → found at index " << binarySearch(arr, 0, 9, 50) << endl;

    // Tower of Hanoi
    cout << "\n--- Tower of Hanoi (3 disks) ---" << endl;
    towerOfHanoi(3, 'A', 'C', 'B');
    cout << "Total moves for 3 disks: " << hanoiMoves << " (should be 2^3 - 1 = 7)" << endl;

    cout << "\n--- Key Points ---" << endl;
    cout << "- Always have a base case or you'll get a stack overflow" << endl;
    cout << "- Recursion uses the call stack — each call uses memory" << endl;
    cout << "- Sometimes iteration is better (fibonacci is classic example)" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Recursion.cpp -o prog
 ================================================================

 === RECURSION ===

 --- Factorial ---
 0! = 1
 1! = 1
 2! = 2
 3! = 6
 4! = 24
 5! = 120
 6! = 720
 7! = 5040
 8! = 40320
 9! = 362880
 10! = 3628800

 --- Fibonacci Sequence ---
 First 10: 0 1 1 2 3 5 8 13 21 34 
 (Note: this recursive version is O(2^n) - very slow for n>30)

 --- Power Function ---
 2^10 = 1024
 3^5  = 243
 2^-3 = 0.125

 --- Sum of Digits ---
 sumOfDigits(12345) = 15
 sumOfDigits(9999)  = 36

 --- Reverse String ---
 reverse('hello') = olleh
 reverse('Pavan') = navaP

 --- Binary Search (Recursive) ---
 Search 23 → found at index 5
 Search 50 → found at index -1

 --- Tower of Hanoi (3 disks) ---
   Move disk 1 from A to C
   Move disk 2 from A to B
   Move disk 1 from C to B
   Move disk 3 from A to C
   Move disk 1 from B to A
   Move disk 2 from B to C
   Move disk 1 from A to C
 Total moves for 3 disks: 7 (should be 2^3 - 1 = 7)

 --- Key Points ---
 - Always have a base case or you'll get a stack overflow
 - Recursion uses the call stack — each call uses memory
 - Sometimes iteration is better (fibonacci is classic example)

 ================================================================
*/

