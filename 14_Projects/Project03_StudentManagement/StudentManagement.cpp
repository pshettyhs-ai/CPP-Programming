/*
 * Project  : Student Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 15
 *
 * Manages student records: add, update, delete, search, grade reports.
 * Concepts: OOP, STL (vector, map), File I/O, sorting, templates
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;

struct Subject {
    string name;
    int    marks;
    int    maxMarks;
    Subject(string n, int m, int mx = 100) : name(n), marks(m), maxMarks(mx) {}
};

class Student {
private:
    int             rollNumber;
    string          name;
    string          branch;
    int             semester;
    vector<Subject> subjects;

public:
    Student() : rollNumber(0), semester(0) {}
    Student(int roll, string n, string br, int sem)
        : rollNumber(roll), name(n), branch(br), semester(sem) {}

    void addSubject(string subName, int marks, int maxMarks = 100) {
        subjects.emplace_back(subName, marks, maxMarks);
    }

    double calculatePercentage() const {
        if (subjects.empty()) return 0.0;
        int total    = 0;
        int maxTotal = 0;
        for (auto& s : subjects) {
            total    += s.marks;
            maxTotal += s.maxMarks;
        }
        return (maxTotal > 0) ? (double)total / maxTotal * 100.0 : 0.0;
    }

    double calculateCGPA() const {
        double pct = calculatePercentage();
        if      (pct >= 90) return 10.0;
        else if (pct >= 80) return 9.0;
        else if (pct >= 70) return 8.0;
        else if (pct >= 60) return 7.0;
        else if (pct >= 50) return 6.0;
        else if (pct >= 40) return 5.0;
        else                return 0.0;
    }

    string getGrade() const {
        double pct = calculatePercentage();
        if      (pct >= 90) return "O (Outstanding)";
        else if (pct >= 80) return "A+ (Excellent)";
        else if (pct >= 70) return "A  (Very Good)";
        else if (pct >= 60) return "B+ (Good)";
        else if (pct >= 50) return "B  (Average)";
        else if (pct >= 40) return "C  (Pass)";
        else                return "F  (Fail)";
    }

    bool hasPassed() const {
        for (auto& s : subjects)
            if (s.marks < s.maxMarks * 0.35) return false;  // 35% passing
        return true;
    }

    // Getters
    int    getRoll()     const { return rollNumber; }
    string getName()     const { return name; }
    string getBranch()   const { return branch; }
    int    getSemester() const { return semester; }
    double getPercent()  const { return calculatePercentage(); }

    void displayReport() const {
        cout << "\n╔════════════════════════════════════════════╗" << endl;
        cout << "║           STUDENT MARK SHEET               ║" << endl;
        cout << "╠════════════════════════════════════════════╣" << endl;
        cout << "║  Roll No : " << left << setw(31) << rollNumber       << " ║" << endl;
        cout << "║  Name    : " << left << setw(31) << name             << " ║" << endl;
        cout << "║  Branch  : " << left << setw(31) << branch           << " ║" << endl;
        cout << "║  Semester: " << left << setw(31) << semester         << " ║" << endl;
        cout << "╠════════════════════════════════════════════╣" << endl;
        cout << "║  Subject              Marks    Max    %    ║" << endl;
        cout << "╠════════════════════════════════════════════╣" << endl;
        for (auto& s : subjects) {
            double pct = (s.maxMarks > 0) ? (double)s.marks / s.maxMarks * 100.0 : 0;
            cout << "║  " << left << setw(21) << s.name
                 << right << setw(5) << s.marks
                 << setw(7) << s.maxMarks
                 << fixed << setprecision(1) << setw(7) << pct << "%  ║" << endl;
        }
        cout << "╠════════════════════════════════════════════╣" << endl;
        cout << "║  Total Percentage : " << left << setw(23)
             << (to_string((int)calculatePercentage()) + "%")  << " ║" << endl;
        cout << "║  CGPA             : " << left << setw(23)
             << to_string(calculateCGPA()).substr(0,3)          << " ║" << endl;
        cout << "║  Grade            : " << left << setw(23) << getGrade()  << " ║" << endl;
        cout << "║  Result           : " << left << setw(23)
             << (hasPassed() ? "PASS ✅" : "FAIL ❌")          << " ║" << endl;
        cout << "╚════════════════════════════════════════════╝" << endl;
    }

    void displaySummary() const {
        cout << "  " << left  << setw(8)  << rollNumber
             << setw(22) << name
             << setw(10) << branch
             << setw(5)  << semester
             << right << fixed << setprecision(2) << setw(8) << calculatePercentage() << "%"
             << setw(6) << (hasPassed() ? "PASS" : "FAIL") << endl;
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    int             nextRoll;

public:
    StudentManagementSystem() : nextRoll(22001) {
        // Pre-load some students
        Student s1(nextRoll++, "Pavan Shetty H S", "CSE", 5);
        s1.addSubject("Data Structures",      88, 100);
        s1.addSubject("Operating Systems",    79, 100);
        s1.addSubject("DBMS",                 91, 100);
        s1.addSubject("Computer Networks",    85, 100);
        s1.addSubject("Embedded Systems",     94, 100);
        students.push_back(s1);

        Student s2(nextRoll++, "Rahul Kumar", "ECE", 5);
        s2.addSubject("Signals & Systems",    72, 100);
        s2.addSubject("VLSI Design",          68, 100);
        s2.addSubject("Microprocessors",      81, 100);
        s2.addSubject("Control Systems",      75, 100);
        s2.addSubject("Embedded C",           83, 100);
        students.push_back(s2);

        Student s3(nextRoll++, "Priya Singh", "CSE", 5);
        s3.addSubject("Data Structures",      95, 100);
        s3.addSubject("Operating Systems",    88, 100);
        s3.addSubject("DBMS",                 92, 100);
        s3.addSubject("Computer Networks",    90, 100);
        s3.addSubject("Embedded Systems",     87, 100);
        students.push_back(s3);
    }

    void addStudent() {
        string name, branch;
        int sem;
        cout << "\n  Enter Name   : "; cin.ignore(); getline(cin, name);
        cout << "  Enter Branch : "; cin >> branch;
        cout << "  Semester     : "; cin >> sem;

        Student s(nextRoll++, name, branch, sem);

        int numSubjects;
        cout << "  How many subjects? "; cin >> numSubjects;
        cin.ignore();
        for (int i = 0; i < numSubjects; i++) {
            string subName;
            int marks;
            cout << "  Subject " << (i+1) << " name : "; getline(cin, subName);
            cout << "  Marks (out of 100): "; cin >> marks; cin.ignore();
            s.addSubject(subName, marks);
        }
        students.push_back(s);
        cout << "  ✅ Student added. Roll Number: " << (nextRoll - 1) << endl;
    }

    void searchStudent() {
        cout << "  Search by: 1.Roll No  2.Name\n  Choice: ";
        int ch; cin >> ch;
        if (ch == 1) {
            int roll; cout << "  Roll No: "; cin >> roll;
            for (auto& s : students)
                if (s.getRoll() == roll) { s.displayReport(); return; }
            cout << "  ❌ Student not found." << endl;
        } else {
            string nm; cout << "  Name: "; cin.ignore(); getline(cin, nm);
            for (auto& s : students)
                if (s.getName() == nm) { s.displayReport(); return; }
            cout << "  ❌ Student not found." << endl;
        }
    }

    void viewAllStudents() {
        cout << "\n╔════════════════════════════════════════════════════╗" << endl;
        cout << "║              ALL STUDENTS SUMMARY                  ║" << endl;
        cout << "╠════════════════════════════════════════════════════╣" << endl;
        cout << "  " << left << setw(8) << "Roll" << setw(22) << "Name"
             << setw(10) << "Branch" << setw(5) << "Sem"
             << setw(10) << "%" << "Result" << endl;
        cout << "  " << string(55, '-') << endl;
        for (auto& s : students) s.displaySummary();
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        cout << "  Total students: " << students.size() << endl;
    }

    void classReport() {
        if (students.empty()) { cout << "  No students." << endl; return; }

        double sumPct = 0;
        int passed = 0, failed = 0;
        Student* topper = &students[0];

        for (auto& s : students) {
            sumPct += s.getPercent();
            if (s.hasPassed()) passed++; else failed++;
            if (s.getPercent() > topper->getPercent()) topper = &s;
        }

        cout << "\n--- Class Report ---" << endl;
        cout << "  Total Students  : " << students.size()     << endl;
        cout << "  Passed          : " << passed              << endl;
        cout << "  Failed          : " << failed              << endl;
        cout << "  Class Average   : " << fixed << setprecision(2)
             << sumPct / students.size() << "%" << endl;
        cout << "  Class Topper    : " << topper->getName()
             << " (" << topper->getPercent() << "%)" << endl;
    }

    void sortByPercentage() {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getPercent() > b.getPercent();
        });
        cout << "  ✅ Students sorted by percentage (descending)." << endl;
        viewAllStudents();
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗" << endl;
            cout << "║   STUDENT MANAGEMENT SYSTEM      ║" << endl;
            cout << "╠══════════════════════════════════╣" << endl;
            cout << "║  1. Add New Student              ║" << endl;
            cout << "║  2. Search Student               ║" << endl;
            cout << "║  3. View All Students            ║" << endl;
            cout << "║  4. Class Report                 ║" << endl;
            cout << "║  5. Sort by Percentage           ║" << endl;
            cout << "║  6. Exit                         ║" << endl;
            cout << "╚══════════════════════════════════╝" << endl;
            cout << "  Choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addStudent();      break;
                case 2: searchStudent();   break;
                case 3: viewAllStudents(); break;
                case 4: classReport();     break;
                case 5: sortByPercentage(); break;
                case 6: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid choice.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    StudentManagementSystem sms;
    sms.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread StudentManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔════════════════════════════════════════════════════╗
 ║              ALL STUDENTS SUMMARY                  ║
 ╠════════════════════════════════════════════════════╣
   Roll    Name                  Branch    Sem  %         Result
   -------------------------------------------------------
   22001   Pavan Shetty H S      CSE       5       87.40%  PASS
   22002   Rahul Kumar           ECE       5       75.80%  PASS
   22003   Priya Singh           CSE       5       90.40%  PASS
 ╚════════════════════════════════════════════════════╝
   Total students: 3

 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 --- Class Report ---
   Total Students  : 3
   Passed          : 3
   Failed          : 0
   Class Average   : 84.53%
   Class Topper    : Priya Singh (90.40%)

 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Search by: 1.Roll No  2.Name
   Choice:   Roll No: 
 ╔════════════════════════════════════════════╗
 ║           STUDENT MARK SHEET               ║
 ╠════════════════════════════════════════════╣
 ║  Roll No : 22001                           ║
 ║  Name    : Pavan Shetty H S                ║
 ║  Branch  : CSE                             ║
 ║  Semester: 5                               ║
 ╠════════════════════════════════════════════╣
 ║  Subject              Marks    Max    %    ║
 ╠════════════════════════════════════════════╣
 ║  Data Structures         88    100   88.0%  ║
 ║  Operating Systems       79    100   79.0%  ║
 ║  DBMS                    91    100   91.0%  ║
 ║  Computer Networks       85    100   85.0%  ║
 ║  Embedded Systems        94    100   94.0%  ║
 ╠════════════════════════════════════════════╣
 ║  Total Percentage : 87%                     ║
 ║  CGPA             : 9.0                     ║
 ║  Grade            : A+ (Excellent)          ║
 ║  Result           : PASS ✅                ║
 ╚════════════════════════════════════════════╝

 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
   Enter Name   :   Enter Branch :   Semester     :   How many subjects?   Subject 1 name :   Marks (out of 100):   Subject 2 name :   Marks (out of 100):   ✅ Student added. Roll Number: 22004

 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   ✅ Students sorted by percentage (descending).

 ╔════════════════════════════════════════════════════╗
 ║              ALL STUDENTS SUMMARY                  ║
 ╠════════════════════════════════════════════════════╣
   Roll    Name                  Branch    Sem  %         Result
   -------------------------------------------------------
   22003   Priya Singh           CSE       5       90.40%  PASS
   22001   Pavan Shetty H S      CSE       5       87.40%  PASS
   22004   Demo Student          CSE       3       77.50%  PASS
   22002   Rahul Kumar           ECE       5       75.80%  PASS
 ╚════════════════════════════════════════════════════╝
   Total students: 4

 ╔══════════════════════════════════╗
 ║   STUDENT MANAGEMENT SYSTEM      ║
 ╠══════════════════════════════════╣
 ║  1. Add New Student              ║
 ║  2. Search Student               ║
 ║  3. View All Students            ║
 ║  4. Class Report                 ║
 ║  5. Sort by Percentage           ║
 ║  6. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

