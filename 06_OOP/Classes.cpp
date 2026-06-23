/*
 * File    : Classes.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Classes and Objects — the foundation of OOP
 * Date    : Week 5 - Day 1
 *
 * Notes:
 *   A class is a blueprint. An object is an instance of that blueprint.
 *   Classes bundle data (attributes) + behaviour (methods) together.
 *   This is called ENCAPSULATION — one of the 4 OOP pillars.
 *
 *   Access specifiers:
 *   - public   : accessible from anywhere
 *   - private  : accessible only within the class (default for class)
 *   - protected: accessible in class + derived classes
 */

#include <iostream>
#include <string>
using namespace std;

// ─────────────────────────────────────────
// Class Definition
// ─────────────────────────────────────────
class Student {
private:
    // Private data members — cannot be accessed directly from outside
    string name;
    int    rollNumber;
    float  cgpa;
    string branch;

public:
    // ── Constructors ──────────────────────
    // Default constructor
    Student() {
        name       = "Unknown";
        rollNumber = 0;
        cgpa       = 0.0f;
        branch     = "Not Set";
        cout << "  [Default constructor called]" << endl;
    }

    // Parameterized constructor
    Student(string n, int roll, float gpa, string br) {
        name       = n;
        rollNumber = roll;
        cgpa       = gpa;
        branch     = br;
        cout << "  [Parameterized constructor called for " << name << "]" << endl;
    }

    // ── Setter Methods (mutators) ─────────
    void setName(string n)      { name = n; }
    void setRollNumber(int r)   { rollNumber = r; }
    void setCGPA(float g)       {
        if (g >= 0.0f && g <= 10.0f) cgpa = g;
        else cout << "  Warning: Invalid CGPA!" << endl;
    }
    void setBranch(string b)    { branch = b; }

    // ── Getter Methods (accessors) ────────
    string getName()       const { return name; }
    int    getRollNumber() const { return rollNumber; }
    float  getCGPA()       const { return cgpa; }
    string getBranch()     const { return branch; }

    // ── Utility Methods ───────────────────
    string getGrade() const {
        if      (cgpa >= 9.0f) return "Outstanding";
        else if (cgpa >= 8.0f) return "Excellent";
        else if (cgpa >= 7.0f) return "Good";
        else if (cgpa >= 6.0f) return "Average";
        else                   return "Below Average";
    }

    void display() const {
        cout << "  ┌────────────────────────────┐" << endl;
        cout << "  │ Name     : " << name          << endl;
        cout << "  │ Roll No  : " << rollNumber    << endl;
        cout << "  │ CGPA     : " << cgpa          << endl;
        cout << "  │ Branch   : " << branch        << endl;
        cout << "  │ Grade    : " << getGrade()    << endl;
        cout << "  └────────────────────────────┘" << endl;
    }

    // ── Static Method ─────────────────────
    // static: belongs to the class, not any object
    static void showInfo() {
        cout << "  [Student Management System v1.0]" << endl;
    }

    // ── Destructor ────────────────────────
    ~Student() {
        cout << "  [Destructor called for " << name << "]" << endl;
    }
};

// ─────────────────────────────────────────
// Another class example: BankAccount
// ─────────────────────────────────────────
class BankAccount {
private:
    string accountHolder;
    long   accountNumber;
    double balance;

public:
    BankAccount(string name, long accNo, double initialBalance = 0.0)
        : accountHolder(name), accountNumber(accNo), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "  Deposited: ₹" << amount << " | New Balance: ₹" << balance << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "  Invalid amount." << endl;
            return false;
        }
        if (amount > balance) {
            cout << "  Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        cout << "  Withdrawn: ₹" << amount << " | New Balance: ₹" << balance << endl;
        return true;
    }

    double getBalance() const { return balance; }

    void showDetails() const {
        cout << "  Account: " << accountHolder
             << " | No: " << accountNumber
             << " | Balance: ₹" << balance << endl;
    }
};

int main() {
    cout << "=== CLASSES AND OBJECTS ===" << endl;

    // ── Student class demo ────────────────
    cout << "\n--- Student Class ---" << endl;
    Student::showInfo();  // static method — called on class, not object

    cout << "\nCreating student objects:" << endl;
    Student s1;  // default constructor
    Student s2("Pavan Shetty H S", (int)22001, 8.9f, "Computer Science");

    cout << "\nUsing setters on s1:" << endl;
    s1.setName("Rahul Kumar");
    s1.setRollNumber((int)22002);
    s1.setCGPA(7.5f);
    s1.setBranch("Electronics");
    s1.setCGPA(11.0f);  // test validation

    cout << "\nDisplaying students:" << endl;
    cout << "Student 1:" << endl;
    s1.display();
    cout << "Student 2:" << endl;
    s2.display();

    // Array of objects
    cout << "\n--- Array of Objects ---" << endl;
    Student batch[3] = {
        Student("Arjun S", 1001, 8.2f, "Mech"),
        Student("Priya R", 1002, 9.1f, "CS"),
        Student("Kiran M", 1003, 7.8f, "ECE")
    };

    cout << "\nBatch results:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << batch[i].getName() << " → " << batch[i].getGrade() << endl;
    }

    // ── BankAccount demo ──────────────────
    cout << "\n--- BankAccount Class ---" << endl;
    BankAccount acc("Pavan Shetty H S", 1001001001, 5000.0);
    acc.showDetails();
    acc.deposit(10000);
    acc.withdraw(3000);
    acc.withdraw(20000);  // should fail

    // ── Object pointers ───────────────────
    cout << "\n--- Object via Pointer ---" << endl;
    Student* sPtr = new Student("Dynamic Student", 9999, 8.0f, "IT");
    sPtr->display();   // arrow operator for pointer-to-object
    delete sPtr;

    cout << "\n--- Objects going out of scope (destructors) ---" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Classes.cpp -o prog
 ================================================================

 === CLASSES AND OBJECTS ===

 --- Student Class ---
   [Student Management System v1.0]

 Creating student objects:
   [Default constructor called]
   [Parameterized constructor called for Pavan Shetty H S]

 Using setters on s1:
   Warning: Invalid CGPA!

 Displaying students:
 Student 1:
   ┌────────────────────────────┐
   │ Name     : Rahul Kumar
   │ Roll No  : 22002
   │ CGPA     : 7.5
   │ Branch   : Electronics
   │ Grade    : Good
   └────────────────────────────┘
 Student 2:
   ┌────────────────────────────┐
   │ Name     : Pavan Shetty H S
   │ Roll No  : 22001
   │ CGPA     : 8.9
   │ Branch   : Computer Science
   │ Grade    : Excellent
   └────────────────────────────┘

 --- Array of Objects ---
   [Parameterized constructor called for Arjun S]
   [Parameterized constructor called for Priya R]
   [Parameterized constructor called for Kiran M]

 Batch results:
 Arjun S → Excellent
 Priya R → Outstanding
 Kiran M → Good

 --- BankAccount Class ---
   Account: Pavan Shetty H S | No: 1001001001 | Balance: ₹5000
   Deposited: ₹10000 | New Balance: ₹15000
   Withdrawn: ₹3000 | New Balance: ₹12000
   Insufficient funds!

 --- Object via Pointer ---
   [Parameterized constructor called for Dynamic Student]
   ┌────────────────────────────┐
   │ Name     : Dynamic Student
   │ Roll No  : 9999
   │ CGPA     : 8
   │ Branch   : IT
   │ Grade    : Excellent
   └────────────────────────────┘
   [Destructor called for Dynamic Student]

 --- Objects going out of scope (destructors) ---
   [Destructor called for Kiran M]
   [Destructor called for Priya R]
   [Destructor called for Arjun S]
   [Destructor called for Pavan Shetty H S]
   [Destructor called for Rahul Kumar]

 ================================================================
*/

