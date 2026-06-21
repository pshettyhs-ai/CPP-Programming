/*
 * File    : DefaultArguments.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Default Arguments & Function Overloading
 * Date    : Week 3 - Day 3
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Default arguments must be at the END of the parameter list
void printBox(int width, int height = 3, char fill = '*') {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) cout << fill;
        cout << endl;
    }
}

// Logging function with defaults
void log(string msg, string level = "INFO", bool timestamp = false) {
    if (timestamp) cout << "[12:34:56] ";
    cout << "[" << level << "] " << msg << endl;
}

// Overloaded area functions
double area(double radius) {
    return 3.14159 * radius * radius;  // circle
}
double area(double length, double width) {
    return length * width;             // rectangle
}
double area(double base, double height, bool isTriangle) {
    return 0.5 * base * height;        // triangle
}

int main() {
    cout << "=== DEFAULT ARGUMENTS & OVERLOADING ===" << endl;

    // Default arguments
    cout << "\n--- Default Arguments ---" << endl;
    cout << "printBox(5)         → "; printBox(5);
    cout << "printBox(6, 2)      → "; printBox(6, 2);
    cout << "printBox(8, 2, '#') → "; printBox(8, 2, '#');

    cout << "\n--- Logging with Defaults ---" << endl;
    log("Application started");
    log("User not found", "ERROR");
    log("Request received", "DEBUG", true);

    // Overloading
    cout << "\n--- Function Overloading ---" << endl;
    cout << "Circle area (r=5): "       << area(5.0)        << endl;
    cout << "Rectangle area (4x6): "    << area(4.0, 6.0)   << endl;
    cout << "Triangle area (b=3,h=8): " << area(3.0, 8.0, true) << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread DefaultArguments.cpp -o prog
 ================================================================

 === DEFAULT ARGUMENTS & OVERLOADING ===

 --- Default Arguments ---
 printBox(5)         → *****
 *****
 *****
 printBox(6, 2)      → ******
 ******
 printBox(8, 2, '#') → ########
 ########

 --- Logging with Defaults ---
 [INFO] Application started
 [ERROR] User not found
 [12:34:56] [DEBUG] Request received

 --- Function Overloading ---
 Circle area (r=5): 78.5397
 Rectangle area (4x6): 24
 Triangle area (b=3,h=8): 12

 ================================================================
*/

