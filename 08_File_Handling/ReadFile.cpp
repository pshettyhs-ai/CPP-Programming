/*
 * File    : ReadFile.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Reading files — ifstream, getline, line by line
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    cout << "=== FILE READING ===" << endl;

    // Write a test file first
    {
        ofstream out("test_input.txt");
        out << "Line 1: Hello from file\n";
        out << "Line 2: C++ File I/O\n";
        out << "Line 3: Pavan Shetty H S\n";
        out << "42 3.14 hello\n";
    }

    // 1. Read line by line
    cout << "\n--- Read Line by Line ---" << endl;
    ifstream fin("test_input.txt");
    if (!fin.is_open()) {
        cerr << "Error: Cannot open file!" << endl;
        return 1;
    }
    string line;
    int lineNo = 1;
    while (getline(fin, line)) {
        cout << "[" << lineNo++ << "] " << line << endl;
    }
    fin.close();

    // 2. Read word by word
    cout << "\n--- Read Word by Word ---" << endl;
    ifstream fin2("test_input.txt");
    string word;
    while (fin2 >> word) {
        cout << word << " | ";
    }
    cout << endl;
    fin2.close();

    // 3. Read specific data types
    cout << "\n--- Parse Mixed Data ---" << endl;
    ifstream fin3("test_input.txt");
    // Skip first 3 lines
    for (int i = 0; i < 3; i++) getline(fin3, line);
    int num; double dbl; string str;
    fin3 >> num >> dbl >> str;
    cout << "int=" << num << " double=" << dbl << " string=" << str << endl;
    fin3.close();

    // 4. File existence check
    ifstream check("nonexistent.txt");
    cout << "\nFile exists: " << (check.good() ? "yes" : "no") << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread ReadFile.cpp -o prog
 ================================================================

 === FILE READING ===

 --- Read Line by Line ---
 [1] Line 1: Hello from file
 [2] Line 2: C++ File I/O
 [3] Line 3: Pavan Shetty H S
 [4] 42 3.14 hello

 --- Read Word by Word ---
 Line | 1: | Hello | from | file | Line | 2: | C++ | File | I/O | Line | 3: | Pavan | Shetty | H | S | 42 | 3.14 | hello | 

 --- Parse Mixed Data ---
 int=42 double=3.14 string=hello

 File exists: no

 ================================================================
*/

