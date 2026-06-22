/*
 * File    : Polymorphism.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Polymorphism — compile-time and runtime
 * Date    : Week 6 - Day 2
 *
 * Notes:
 *   Polymorphism = "many forms" — same interface, different behaviour.
 *
 *   Compile-time (static): function overloading, operator overloading
 *   Runtime (dynamic)    : virtual functions, function overriding
 *
 *   The vtable (virtual table) is how C++ implements dynamic dispatch.
 *   Each class with virtual functions has a vtable — a table of function pointers.
 *   When you call a virtual function through a base pointer, C++ looks up the
 *   actual function in the vtable at runtime.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ─────────────────────────────────────────
// COMPILE-TIME POLYMORPHISM
// ─────────────────────────────────────────

// 1. Function Overloading
class Calculator {
public:
    int    add(int a, int b)          { return a + b; }
    double add(double a, double b)    { return a + b; }
    int    add(int a, int b, int c)   { return a + b + c; }
    string add(string a, string b)    { return a + b; }  // string concatenation
};

// 2. Operator Overloading
class Vector2D {
public:
    float x, y;
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Overload +
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    // Overload -
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    // Overload *  (scalar)
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    // Overload ==
    bool operator==(const Vector2D& other) const {
        return (x == other.x && y == other.y);
    }
    // Overload << for cout
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// ─────────────────────────────────────────
// RUNTIME POLYMORPHISM — Virtual Functions
// ─────────────────────────────────────────
class Employee {
protected:
    string name;
    double baseSalary;
public:
    Employee(string n, double s) : name(n), baseSalary(s) {}

    virtual double calculateSalary() { return baseSalary; }  // virtual!

    virtual void display() {
        cout << "Employee: " << name << " | Salary: ₹" << calculateSalary() << endl;
    }

    virtual string getType() { return "Employee"; }

    virtual ~Employee() {}  // virtual destructor — IMPORTANT for proper cleanup
};

class Manager : public Employee {
    double bonus;
public:
    Manager(string n, double s, double b) : Employee(n, s), bonus(b) {}

    double calculateSalary() override { return baseSalary + bonus; }  // override keyword (C++11)

    void display() override {
        cout << "Manager: " << name << " | Base: ₹" << baseSalary
             << " | Bonus: ₹" << bonus << " | Total: ₹" << calculateSalary() << endl;
    }
    string getType() override { return "Manager"; }
};

class Developer : public Employee {
    int    overtimeHours;
    double hourlyRate;
public:
    Developer(string n, double s, int oh, double hr)
        : Employee(n, s), overtimeHours(oh), hourlyRate(hr) {}

    double calculateSalary() override {
        return baseSalary + (overtimeHours * hourlyRate);
    }
    void display() override {
        cout << "Developer: " << name << " | Base: ₹" << baseSalary
             << " | Overtime: " << overtimeHours << "hrs | Total: ₹" << calculateSalary() << endl;
    }
    string getType() override { return "Developer"; }
};

class Intern : public Employee {
    int months;
public:
    Intern(string n, double monthly, int m)
        : Employee(n, monthly), months(m) {}

    double calculateSalary() override { return baseSalary; }  // just base stipend
    void display() override {
        cout << "Intern: " << name << " | Stipend: ₹" << baseSalary
             << "/month for " << months << " months" << endl;
    }
    string getType() override { return "Intern"; }
};

int main() {
    cout << "=== POLYMORPHISM ===" << endl;

    // ── Compile-time ──────────────────────
    cout << "\n--- Function Overloading ---" << endl;
    Calculator calc;
    cout << "add(3, 4)        = " << calc.add(3, 4)          << endl;
    cout << "add(1.5, 2.5)    = " << calc.add(1.5, 2.5)      << endl;
    cout << "add(1, 2, 3)     = " << calc.add(1, 2, 3)       << endl;
    cout << "add(Hi, World!)  = " << calc.add("Hi, ", "World!") << endl;

    cout << "\n--- Operator Overloading ---" << endl;
    Vector2D v1(3.0f, 4.0f), v2(1.0f, 2.0f);
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << (v1 + v2) << endl;
    cout << "v1 - v2 = " << (v1 - v2) << endl;
    cout << "v1 * 2  = " << (v1 * 2)  << endl;
    cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << endl;

    // ── Runtime polymorphism ──────────────
    cout << "\n--- Runtime Polymorphism (Virtual Functions) ---" << endl;

    // Vector of base class pointers — this is the KEY to runtime polymorphism
    vector<Employee*> employees;
    employees.push_back(new Manager  ("Suresh K",    80000, 20000));
    employees.push_back(new Developer("Pavan S",     60000, 15, 200));
    employees.push_back(new Intern   ("Ananya R",    15000, 6));
    employees.push_back(new Employee ("Ravi M",      45000));

    cout << "\nPayroll Report:" << endl;
    cout << "─────────────────────────────────────" << endl;
    double totalPayroll = 0;
    for (Employee* emp : employees) {
        emp->display();          // calls the CORRECT version based on actual type!
        totalPayroll += emp->calculateSalary();
    }
    cout << "─────────────────────────────────────" << endl;
    cout << "Total Payroll: ₹" << totalPayroll << endl;

    // Without virtual, all would print Employee::display()
    // With virtual, each object's actual type's display() is called
    cout << "\nObject types at runtime:" << endl;
    for (Employee* emp : employees) {
        cout << "  " << emp->getType() << endl;
    }

    // Cleanup — virtual destructor ensures derived destructors are called
    for (Employee* emp : employees) delete emp;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Polymorphism.cpp -o prog
 ================================================================

 === POLYMORPHISM ===

 --- Function Overloading ---
 add(3, 4)        = 7
 add(1.5, 2.5)    = 4
 add(1, 2, 3)     = 6
 add(Hi, World!)  = Hi, World!

 --- Operator Overloading ---
 v1 = (3, 4)
 v2 = (1, 2)
 v1 + v2 = (4, 6)
 v1 - v2 = (2, 2)
 v1 * 2  = (6, 8)
 v1 == v2: false

 --- Runtime Polymorphism (Virtual Functions) ---

 Payroll Report:
 ─────────────────────────────────────
 Manager: Suresh K | Base: ₹80000 | Bonus: ₹20000 | Total: ₹100000
 Developer: Pavan S | Base: ₹60000 | Overtime: 15hrs | Total: ₹63000
 Intern: Ananya R | Stipend: ₹15000/month for 6 months
 Employee: Ravi M | Salary: ₹45000
 ─────────────────────────────────────
 Total Payroll: ₹223000

 Object types at runtime:
   Manager
   Developer
   Intern
   Employee

 ================================================================
*/

