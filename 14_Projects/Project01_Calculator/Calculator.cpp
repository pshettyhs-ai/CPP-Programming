/*
 * Project  : Scientific Calculator
 * Author   : Pavan Shetty H S
 * Version  : 1.5
 * Date     : Week 14
 *
 * My first real project in this repo. Started with basic arithmetic
 * then added scientific functions, history, and expression parsing.
 * Good exercise in OOP and exception handling.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
using namespace std;

class Calculator {
private:
    double   memory;
    vector<string> history;
    const string   HISTORY_FILE = "calc_history.txt";

    void addToHistory(string entry) {
        history.push_back(entry);
        if (history.size() > 10) history.erase(history.begin());
    }

public:
    Calculator() : memory(0.0) {}

    // Basic operations
    double add(double a, double b)      { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) {
        if (b == 0) throw runtime_error("Division by zero!");
        return a / b;
    }
    double modulo(double a, double b) {
        if (b == 0) throw runtime_error("Modulo by zero!");
        return fmod(a, b);
    }
    double power(double base, double exp)  { return pow(base, exp); }

    // Scientific functions
    double squareRoot(double x) {
        if (x < 0) throw runtime_error("Cannot take sqrt of negative number.");
        return sqrt(x);
    }
    double logarithm(double x) {
        if (x <= 0) throw runtime_error("log undefined for non-positive values.");
        return log10(x);
    }
    double naturalLog(double x) {
        if (x <= 0) throw runtime_error("ln undefined for non-positive values.");
        return log(x);
    }
    double sine(double deg)    { return sin(deg * M_PI / 180.0); }
    double cosine(double deg)  { return cos(deg * M_PI / 180.0); }
    double tangent(double deg) {
        if (fmod(deg, 180.0) == 90.0) throw runtime_error("tan undefined at 90°/270°.");
        return tan(deg * M_PI / 180.0);
    }
    double factorial(int n) {
        if (n < 0)  throw runtime_error("Factorial undefined for negatives.");
        if (n > 20) throw runtime_error("Factorial too large (>20!).");
        double result = 1;
        for (int i = 2; i <= n; i++) result *= i;
        return result;
    }
    double absolute(double x) { return fabs(x); }
    double ceiling(double x)  { return ceil(x); }
    double flooring(double x) { return floor(x); }
    double round_(double x)   { return round(x); }

    // Memory functions
    void   memoryStore(double val)  { memory = val; cout << "  M = " << memory << endl; }
    double memoryRecall()           { return memory; }
    void   memoryClear()            { memory = 0; cout << "  Memory cleared." << endl; }
    void   memoryAdd(double val)    { memory += val; }

    void showHistory() {
        cout << "\n--- Calculation History ---" << endl;
        if (history.empty()) { cout << "  No history yet." << endl; return; }
        for (int i = 0; i < (int)history.size(); i++) {
            cout << "  " << (i+1) << ". " << history[i] << endl;
        }
    }

    void performCalculation() {
        double a, b, result;
        int choice;

        cout << "\n┌─────────────────────────────────┐" << endl;
        cout << "│      SCIENTIFIC CALCULATOR      │" << endl;
        cout << "├─────────────────────────────────┤" << endl;
        cout << "│ BASIC:    1.Add  2.Sub  3.Mul   │" << endl;
        cout << "│           4.Div  5.Mod  6.Pow   │" << endl;
        cout << "├─────────────────────────────────┤" << endl;
        cout << "│ SCIENCE:  7.Sqrt 8.Log  9.Ln    │" << endl;
        cout << "│          10.Sin 11.Cos 12.Tan   │" << endl;
        cout << "│          13.Abs 14.Fact          │" << endl;
        cout << "├─────────────────────────────────┤" << endl;
        cout << "│ MEMORY: 15.MS  16.MR  17.MC     │" << endl;
        cout << "├─────────────────────────────────┤" << endl;
        cout << "│ 18. History    0. Exit           │" << endl;
        cout << "└─────────────────────────────────┘" << endl;
        cout << "  Choice: ";
        cin >> choice;

        string entry;
        try {
            switch(choice) {
            case 1:
                cout << "  a = "; cin >> a;
                cout << "  b = "; cin >> b;
                result = add(a, b);
                entry  = to_string(a) + " + " + to_string(b) + " = " + to_string(result);
                cout << "  Result: " << fixed << setprecision(4) << result << endl;
                addToHistory(entry);
                break;
            case 2:
                cout << "  a = "; cin >> a; cout << "  b = "; cin >> b;
                result = subtract(a, b);
                cout << "  Result: " << result << endl;
                addToHistory(to_string(a) + " - " + to_string(b) + " = " + to_string(result));
                break;
            case 3:
                cout << "  a = "; cin >> a; cout << "  b = "; cin >> b;
                result = multiply(a, b);
                cout << "  Result: " << result << endl;
                addToHistory(to_string(a) + " × " + to_string(b) + " = " + to_string(result));
                break;
            case 4:
                cout << "  a = "; cin >> a; cout << "  b = "; cin >> b;
                result = divide(a, b);
                cout << "  Result: " << result << endl;
                addToHistory(to_string(a) + " ÷ " + to_string(b) + " = " + to_string(result));
                break;
            case 5:
                cout << "  a = "; cin >> a; cout << "  b = "; cin >> b;
                result = modulo(a, b);
                cout << "  Result: " << result << endl;
                break;
            case 6:
                cout << "  base = "; cin >> a; cout << "  exp = "; cin >> b;
                result = power(a, b);
                cout << "  " << a << "^" << b << " = " << result << endl;
                addToHistory(to_string(a) + "^" + to_string(b) + " = " + to_string(result));
                break;
            case 7:
                cout << "  x = "; cin >> a;
                result = squareRoot(a);
                cout << "  √" << a << " = " << result << endl;
                addToHistory("√" + to_string(a) + " = " + to_string(result));
                break;
            case 8:
                cout << "  x = "; cin >> a;
                result = logarithm(a);
                cout << "  log(" << a << ") = " << result << endl;
                break;
            case 9:
                cout << "  x = "; cin >> a;
                result = naturalLog(a);
                cout << "  ln(" << a << ") = " << result << endl;
                break;
            case 10:
                cout << "  degrees = "; cin >> a;
                result = sine(a);
                cout << "  sin(" << a << "°) = " << fixed << setprecision(6) << result << endl;
                break;
            case 11:
                cout << "  degrees = "; cin >> a;
                result = cosine(a);
                cout << "  cos(" << a << "°) = " << result << endl;
                break;
            case 12:
                cout << "  degrees = "; cin >> a;
                result = tangent(a);
                cout << "  tan(" << a << "°) = " << result << endl;
                break;
            case 13:
                cout << "  x = "; cin >> a;
                result = absolute(a);
                cout << "  |" << a << "| = " << result << endl;
                break;
            case 14:
                int n;
                cout << "  n = "; cin >> n;
                result = factorial(n);
                cout << "  " << n << "! = " << result << endl;
                break;
            case 15: cout << "  Value to store: "; cin >> a; memoryStore(a); break;
            case 16: cout << "  Memory = " << memoryRecall() << endl; break;
            case 17: memoryClear(); break;
            case 18: showHistory(); break;
            case 0:  cout << "  Bye!" << endl; break;
            default: cout << "  Invalid choice." << endl;
            }
        } catch (const exception& e) {
            cout << "  ❌ Error: " << e.what() << endl;
        }
    }
};

int main() {
    Calculator calc;
    cout << "\nWelcome to Pavan's Scientific Calculator!" << endl;

    int choice;
    do {
        calc.performCalculation();
        cout << "\n  Continue? (0 to exit, any other to continue): ";
        // In demo mode, just run once
        break;
    } while (choice != 0);

    cout << "\nCalculator closed.\n";
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Calculator.cpp -o prog
 ================================================================


 Welcome to Pavan's Scientific Calculator!

 ┌─────────────────────────────────┐
 │      SCIENTIFIC CALCULATOR      │
 ├─────────────────────────────────┤
 │ BASIC:    1.Add  2.Sub  3.Mul   │
 │           4.Div  5.Mod  6.Pow   │
 ├─────────────────────────────────┤
 │ SCIENCE:  7.Sqrt 8.Log  9.Ln    │
 │          10.Sin 11.Cos 12.Tan   │
 │          13.Abs 14.Fact          │
 ├─────────────────────────────────┤
 │ MEMORY: 15.MS  16.MR  17.MC     │
 ├─────────────────────────────────┤
 │ 18. History    0. Exit           │
 └─────────────────────────────────┘
   Choice:   a =   b =   Result: 42.0000

   Continue? (0 to exit, any other to continue): 
 Calculator closed.

 ================================================================
*/

