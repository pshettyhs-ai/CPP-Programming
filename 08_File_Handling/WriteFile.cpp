/*
 * File    : WriteFile.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Writing files — ofstream, formatting, binary
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct StudentRecord {
    int    id;
    string name;
    double gpa;
};

int main() {
    cout << "=== FILE WRITING ===" << endl;

    // 1. Basic text write
    cout << "\n--- Basic Write ---" << endl;
    ofstream fout("output.txt");
    if (!fout) { cerr << "Cannot open file!\n"; return 1; }
    fout << "Name: Pavan Shetty H S\n";
    fout << "Role: Software Engineer\n";
    fout << "Year: 2025\n";
    fout.close();
    cout << "Written to output.txt" << endl;

    // 2. Formatted table
    cout << "\n--- Formatted Table Write ---" << endl;
    ofstream report("report.txt");
    report << string(40, '=') << "\n";
    report << "STUDENT REPORT\n";
    report << string(40, '=') << "\n";
    report << left << setw(8) << "ID" << setw(20) << "Name" << setw(8) << "GPA\n";
    report << string(40, '-') << "\n";

    StudentRecord students[] = {
        {1001, "Pavan Shetty", 8.9},
        {1002, "Rahul Kumar",  7.5},
        {1003, "Priya Singh",  9.2}
    };
    for (auto& s : students) {
        report << left << setw(8) << s.id
               << setw(20) << s.name
               << fixed << setprecision(1) << s.gpa << "\n";
    }
    report << string(40, '=') << "\n";
    report.close();
    cout << "Formatted report written to report.txt" << endl;

    // 3. Binary write
    cout << "\n--- Binary Write ---" << endl;
    ofstream binOut("data.bin", ios::binary);
    int values[] = {10, 20, 30, 40, 50};
    binOut.write(reinterpret_cast<char*>(values), sizeof(values));
    binOut.close();

    // Read back binary
    ifstream binIn("data.bin", ios::binary);
    int readVals[5];
    binIn.read(reinterpret_cast<char*>(readVals), sizeof(readVals));
    cout << "Binary read back: ";
    for (int v : readVals) cout << v << " ";
    cout << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread WriteFile.cpp -o prog
 ================================================================

 === FILE WRITING ===

 --- Basic Write ---
 Written to output.txt

 --- Formatted Table Write ---
 Formatted report written to report.txt

 --- Binary Write ---
 Binary read back: 10 20 30 40 50 

 ================================================================
*/

