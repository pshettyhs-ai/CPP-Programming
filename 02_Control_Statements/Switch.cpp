/*
 * File    : Switch.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Switch statement — when to use it over if-else
 * Date    : Week 2 - Day 1
 *
 * Notes:
 *   Switch is faster than if-else chain for known discrete values.
 *   The compiler can generate a jump table for switch.
 *   Always remember: break is NOT automatic! Forgetting it causes
 *   fall-through (which is sometimes intentional but usually a bug).
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "=== SWITCH STATEMENT ===" << endl;

    // 1. Basic switch with int
    int day = 3;
    cout << "\nDay " << day << " is: ";
    switch (day) {
        case 1: cout << "Monday";    break;
        case 2: cout << "Tuesday";   break;
        case 3: cout << "Wednesday"; break;
        case 4: cout << "Thursday";  break;
        case 5: cout << "Friday";    break;
        case 6: cout << "Saturday";  break;
        case 7: cout << "Sunday";    break;
        default: cout << "Invalid day";
    }
    cout << endl;

    // 2. Fall-through (intentional — no break between cases)
    int month = 4;
    int days;
    switch (month) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            days = 31;
            break;
        case 4: case 6: case 9: case 11:
            days = 30;
            break;
        case 2:
            days = 28;  // ignoring leap year for now
            break;
        default:
            days = -1;
    }
    cout << "Month " << month << " has " << days << " days" << endl;

    // 3. Switch with char
    char grade = 'B';
    cout << "\nGrade " << grade << ": ";
    switch (grade) {
        case 'A': cout << "Excellent!";   break;
        case 'B': cout << "Very Good!";   break;
        case 'C': cout << "Good.";        break;
        case 'D': cout << "Needs work.";  break;
        case 'F': cout << "Failed!";      break;
        default : cout << "Invalid grade";
    }
    cout << endl;

    // 4. Menu-driven program style (common use case)
    int choice = 2;
    cout << "\nCalculator operation " << choice << ":\n";
    float x = 10, y = 3;
    switch (choice) {
        case 1: cout << x << " + " << y << " = " << x + y; break;
        case 2: cout << x << " - " << y << " = " << x - y; break;
        case 3: cout << x << " * " << y << " = " << x * y; break;
        case 4:
            if (y != 0) cout << x << " / " << y << " = " << x / y;
            else cout << "Division by zero!";
            break;
        default: cout << "Invalid choice";
    }
    cout << endl;

    // NOTE: switch works with int, char, enum — NOT with strings or floats
    // For strings use if-else chain

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Switch.cpp -o prog
 ================================================================

 === SWITCH STATEMENT ===

 Day 3 is: Wednesday
 Month 4 has 30 days

 Grade B: Very Good!

 Calculator operation 2:
 10 - 3 = 7

 ================================================================
*/

