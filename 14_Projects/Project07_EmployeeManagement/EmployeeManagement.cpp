/*
 * Project  : Employee Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 16
 *
 * Concepts: Inheritance, Polymorphism, Templates, STL, File I/O
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
using namespace std;

// ── Base Employee
class Employee {
protected:
    int    empId;
    string name;
    string department;
    string designation;
    double basicSalary;
    string joiningDate;
    int    yearsOfService;
    double performanceRating;  // 1.0 - 5.0

public:
    Employee(int id, string n, string dept, string desig,
             double salary, string date, int yos, double rating = 3.0)
        : empId(id), name(n), department(dept), designation(desig),
          basicSalary(salary), joiningDate(date), yearsOfService(yos),
          performanceRating(rating) {}

    virtual ~Employee() {}

    virtual double calculateSalary() const = 0;
    virtual string getType()         const = 0;

    virtual void displayPayslip() const {
        cout << "\n  ╔═══════════════════════════════════════╗" << endl;
        cout << "  ║            SALARY SLIP                ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ Emp ID     : " << left << setw(25) << empId       << " ║" << endl;
        cout << "  ║ Name       : " << left << setw(25) << name        << " ║" << endl;
        cout << "  ║ Department : " << left << setw(25) << department  << " ║" << endl;
        cout << "  ║ Designation: " << left << setw(25) << designation << " ║" << endl;
        cout << "  ║ Type       : " << left << setw(25) << getType()   << " ║" << endl;
        cout << "  ║ Joined     : " << left << setw(25) << joiningDate << " ║" << endl;
        cout << "  ║ Rating     : " << left << setw(25) << performanceRating << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ Basic Sal  : ₹" << left << setw(24) << fixed << setprecision(2) << basicSalary << " ║" << endl;
    }

    int    getId()         const { return empId; }
    string getName()       const { return name; }
    string getDepartment() const { return department; }
    double getBasic()      const { return basicSalary; }
    double getRating()     const { return performanceRating; }
    void setRating(double r)     { performanceRating = r; }

    void displaySummary() const {
        cout << "  " << left << setw(7) << empId
             << setw(22) << name
             << setw(16) << department
             << setw(14) << designation
             << "₹" << right << setw(10) << fixed << setprecision(0) << calculateSalary() << endl;
    }
};

// ── Permanent Employee
class PermanentEmployee : public Employee {
    double hra;   // House Rent Allowance
    double da;    // Dearness Allowance
    double ta;    // Travel Allowance
    double pf;    // Provident Fund deduction
    double tax;   // Income tax deduction

public:
    PermanentEmployee(int id, string n, string dept, string desig,
                      double salary, string date, int yos, double rating = 3.0)
        : Employee(id, n, dept, desig, salary, date, yos, rating) {
        hra  = basicSalary * 0.40;
        da   = basicSalary * 0.20;
        ta   = 2000;
        pf   = basicSalary * 0.12;
        tax  = basicSalary * 0.10;
    }

    double calculateSalary() const override {
        double gross = basicSalary + hra + da + ta;
        double deductions = pf + tax;
        return gross - deductions;
    }

    string getType() const override { return "Permanent"; }

    void displayPayslip() const override {
        Employee::displayPayslip();
        double gross = basicSalary + hra + da + ta;
        cout << "  ║ HRA (40%)  : ₹" << left << setw(24) << hra  << " ║" << endl;
        cout << "  ║ DA  (20%)  : ₹" << left << setw(24) << da   << " ║" << endl;
        cout << "  ║ TA         : ₹" << left << setw(24) << ta   << " ║" << endl;
        cout << "  ║ GROSS      : ₹" << left << setw(24) << gross << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ PF (12%)   : ₹" << left << setw(24) << pf  << " ║" << endl;
        cout << "  ║ Tax(10%)   : ₹" << left << setw(24) << tax << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ NET SALARY : ₹" << left << setw(24) << fixed << setprecision(2) << calculateSalary() << " ║" << endl;
        cout << "  ╚═══════════════════════════════════════╝" << endl;
    }
};

// ── Contract Employee
class ContractEmployee : public Employee {
    double hourlyRate;
    int    hoursWorked;

public:
    ContractEmployee(int id, string n, string dept, string desig,
                     double salary, string date, int yos,
                     double hRate, int hours, double rating = 3.0)
        : Employee(id, n, dept, desig, salary, date, yos, rating),
          hourlyRate(hRate), hoursWorked(hours) {}

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    string getType() const override { return "Contract"; }

    void displayPayslip() const override {
        Employee::displayPayslip();
        cout << "  ║ Hourly Rate: ₹" << left << setw(24) << hourlyRate   << " ║" << endl;
        cout << "  ║ Hrs Worked : "  << left << setw(25) << hoursWorked  << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ NET SALARY : ₹" << left << setw(24) << fixed << setprecision(2) << calculateSalary() << " ║" << endl;
        cout << "  ╚═══════════════════════════════════════╝" << endl;
    }
};

// ── Intern
class Intern : public Employee {
    int    durationMonths;
    string mentor;

public:
    Intern(int id, string n, string dept, double stipend,
           string date, int months, string mentorName)
        : Employee(id, n, dept, "Intern", stipend, date, 0),
          durationMonths(months), mentor(mentorName) {}

    double calculateSalary() const override { return basicSalary; }
    string getType() const override { return "Intern"; }

    void displayPayslip() const override {
        Employee::displayPayslip();
        cout << "  ║ Duration   : " << left << setw(25) << (to_string(durationMonths) + " months") << " ║" << endl;
        cout << "  ║ Mentor     : " << left << setw(25) << mentor << " ║" << endl;
        cout << "  ╠═══════════════════════════════════════╣" << endl;
        cout << "  ║ STIPEND    : ₹" << left << setw(24) << fixed << setprecision(2) << basicSalary << " ║" << endl;
        cout << "  ╚═══════════════════════════════════════╝" << endl;
    }
};

// ── EMS
class EmployeeManagementSystem {
    vector<Employee*> employees;
    int nextId = 10001;

    Employee* findEmployee(int id) {
        for (auto e : employees) if (e->getId() == id) return e;
        return nullptr;
    }

public:
    EmployeeManagementSystem() {
        employees.push_back(new PermanentEmployee(nextId++, "Pavan Shetty H S",  "Engineering", "Software Engineer",  75000, "01/01/2024", 1, 4.5));
        employees.push_back(new PermanentEmployee(nextId++, "Rahul Kumar",        "Engineering", "Senior Engineer",   120000, "15/03/2021", 4, 4.2));
        employees.push_back(new PermanentEmployee(nextId++, "Priya Singh",        "HR",          "HR Manager",         90000, "10/07/2020", 5, 4.7));
        employees.push_back(new ContractEmployee( nextId++, "Arjun Dev",          "Design",      "UI Designer",            0, "01/04/2025", 0, 800, 160, 3.8));
        employees.push_back(new Intern(           nextId++, "Sneha Rao",          "Engineering", 15000,                    "01/06/2025", 6, "Rahul Kumar"));
    }

    ~EmployeeManagementSystem() { for (auto e : employees) delete e; }

    void addEmployee() {
        cout << "  Type: 1.Permanent  2.Contract  3.Intern\n  Choice: ";
        int type; cin >> type;
        string name, dept, desig, date, mentor;
        double sal;
        int yos;

        cout << "  Name       : "; cin.ignore(); getline(cin, name);
        cout << "  Department : "; getline(cin, dept);
        cout << "  Join Date  : "; cin >> date;
        cout << "  Years Svc  : "; cin >> yos;

        if (type == 1) {
            cout << "  Designation: "; cin.ignore(); getline(cin, desig);
            cout << "  Basic Sal ₹: "; cin >> sal;
            employees.push_back(new PermanentEmployee(nextId++, name, dept, desig, sal, date, yos));
        } else if (type == 2) {
            double hRate; int hrs;
            cout << "  Hourly Rate: "; cin >> hRate;
            cout << "  Hrs/Month  : "; cin >> hrs;
            employees.push_back(new ContractEmployee(nextId++, name, dept, "Contractor", 0, date, yos, hRate, hrs));
        } else {
            double stipend; int months;
            cout << "  Stipend  ₹ : "; cin >> stipend;
            cout << "  Duration   : "; cin >> months;
            cout << "  Mentor     : "; cin.ignore(); getline(cin, mentor);
            employees.push_back(new Intern(nextId++, name, dept, stipend, date, months, mentor));
        }
        cout << "  ✅ Employee added. ID: " << (nextId - 1) << endl;
    }

    void viewPayslip() {
        int id; cout << "  Employee ID: "; cin >> id;
        Employee* e = findEmployee(id);
        if (e) e->displayPayslip();
        else   cout << "  ❌ Not found.\n";
    }

    void viewAllEmployees() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              EMPLOYEE DIRECTORY                              ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "  " << left << setw(7)  << "ID"
             << setw(22) << "Name"
             << setw(16) << "Department"
             << setw(14) << "Designation"
             << right << setw(12) << "Net Salary" << endl;
        cout << "  " << string(68, '-') << endl;
        for (auto e : employees) e->displaySummary();
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    }

    void departmentReport() {
        map<string, vector<Employee*>> byDept;
        for (auto e : employees) byDept[e->getDepartment()].push_back(e);

        cout << "\n--- Department-wise Report ---" << endl;
        for (auto& [dept, emps] : byDept) {
            double total = 0;
            for (auto e : emps) total += e->calculateSalary();
            cout << "  " << left << setw(20) << dept
                 << "Employees: " << setw(4) << emps.size()
                 << "Total Salary: ₹" << fixed << setprecision(0) << total << endl;
        }
    }

    void updateRating() {
        int id; double rating;
        cout << "  Employee ID    : "; cin >> id;
        cout << "  New Rating(1-5): "; cin >> rating;
        Employee* e = findEmployee(id);
        if (!e) { cout << "  ❌ Not found.\n"; return; }
        e->setRating(rating);
        cout << "  ✅ Rating updated.\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗" << endl;
            cout << "║  EMPLOYEE MANAGEMENT SYSTEM      ║" << endl;
            cout << "╠══════════════════════════════════╣" << endl;
            cout << "║  1. Add Employee                 ║" << endl;
            cout << "║  2. View Payslip                 ║" << endl;
            cout << "║  3. View All Employees           ║" << endl;
            cout << "║  4. Department Report            ║" << endl;
            cout << "║  5. Update Performance Rating    ║" << endl;
            cout << "║  6. Exit                         ║" << endl;
            cout << "╚══════════════════════════════════╝" << endl;
            cout << "  Choice: "; cin >> choice;
            switch(choice) {
                case 1: addEmployee();       break;
                case 2: viewPayslip();       break;
                case 3: viewAllEmployees();  break;
                case 4: departmentReport();  break;
                case 5: updateRating();      break;
                case 6: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    EmployeeManagementSystem ems;
    ems.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread EmployeeManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════════════════════════╗
 ║              EMPLOYEE DIRECTORY                              ║
 ╠══════════════════════════════════════════════════════════════╣
   ID     Name                  Department      Designation     Net Salary
   --------------------------------------------------------------------
   10001  Pavan Shetty H S      Engineering     Software Engineer₹    105500
   10002  Rahul Kumar           Engineering     Senior Engineer₹    167600
   10003  Priya Singh           HR              HR Manager    ₹    126200
   10004  Arjun Dev             Design          UI Designer   ₹    128000
   10005  Sneha Rao             Engineering     Intern        ₹     15000
 ╚══════════════════════════════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Employee ID: 
   ╔═══════════════════════════════════════╗
   ║            SALARY SLIP                ║
   ╠═══════════════════════════════════════╣
   ║ Emp ID     : 10001                     ║
   ║ Name       : Pavan Shetty H S          ║
   ║ Department : Engineering               ║
   ║ Designation: Software Engineer         ║
   ║ Type       : Permanent                 ║
   ║ Joined     : 01/01/2024                ║
   ║ Rating     : 4                         ║
   ╠═══════════════════════════════════════╣
   ║ Basic Sal  : ₹75000.00                 ║
   ║ HRA (40%)  : ₹30000.00                 ║
   ║ DA  (20%)  : ₹15000.00                 ║
   ║ TA         : ₹2000.00                  ║
   ║ GROSS      : ₹122000.00                ║
   ╠═══════════════════════════════════════╣
   ║ PF (12%)   : ₹9000.00                  ║
   ║ Tax(10%)   : ₹7500.00                  ║
   ╠═══════════════════════════════════════╣
   ║ NET SALARY : ₹105500.00                ║
   ╚═══════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 --- Department-wise Report ---
   Design              Employees: 1   Total Salary: ₹128000
   Engineering         Employees: 3   Total Salary: ₹288100
   HR                  Employees: 1   Total Salary: ₹126200

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Employee ID    :   New Rating(1-5):   ✅ Rating updated.

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Type: 1.Permanent  2.Contract  3.Intern
   Choice:   Name       :   Department :   Join Date  :   Years Svc  :   Designation:   Basic Sal ₹:   ✅ Employee added. ID: 10006

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════════════════════════╗
 ║              EMPLOYEE DIRECTORY                              ║
 ╠══════════════════════════════════════════════════════════════╣
   ID     Name                  Department      Designation     Net Salary
   --------------------------------------------------------------------
   10001  Pavan Shetty H S      Engineering     Software Engineer₹    105500
   10002  Rahul Kumar           Engineering     Senior Engineer₹    167600
   10003  Priya Singh           HR              HR Manager    ₹    126200
   10004  Arjun Dev             Design          UI Designer   ₹    128000
   10005  Sneha Rao             Engineering     Intern        ₹     15000
   10006  Demo Employee         Finance         Analyst       ₹     71000
 ╚══════════════════════════════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║  EMPLOYEE MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add Employee                 ║
 ║  2. View Payslip                 ║
 ║  3. View All Employees           ║
 ║  4. Department Report            ║
 ║  5. Update Performance Rating    ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

