/*
 * File    : AppendFile.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Appending to files, file positions, binary files
 * Date    : Week 9 - Day 3
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

string getTimestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void log(const string& msg, const string& level = "INFO") {
    ofstream logFile("app.log", ios::app);  // ios::app = append mode
    logFile << "[" << getTimestamp() << "] [" << level << "] " << msg << "\n";
    logFile.close();
}

int main() {
    cout << "=== APPEND AND FILE POSITIONS ===" << endl;

    // 1. Append mode
    cout << "\n--- Append Mode (ios::app) ---" << endl;

    // Write initial content
    {
        ofstream f("notes.txt");
        f << "=== My Notes ===\n";
        f << "First entry.\n";
    }

    // Append multiple times
    {
        ofstream f("notes.txt", ios::app);
        f << "Second entry.\n";
    }
    {
        ofstream f("notes.txt", ios::app);
        f << "Third entry.\n";
    }

    // Read it back
    ifstream in("notes.txt");
    string line;
    cout << "notes.txt contents:" << endl;
    while (getline(in, line)) cout << "  " << line << endl;

    // 2. Logging demo
    cout << "\n--- Append Logging ---" << endl;
    log("Application started");
    log("User logged in: pavan@email.com");
    log("Failed to connect to DB", "ERROR");
    log("Retry successful");
    log("Session ended");

    ifstream logIn("app.log");
    cout << "app.log contents:" << endl;
    while (getline(logIn, line)) cout << "  " << line << endl;

    // 3. File seek positions
    cout << "\n--- File Seek (tellg, seekg) ---" << endl;
    {
        ofstream out("seek_test.txt");
        out << "Hello World! C++ is great.";
    }

    fstream fs("seek_test.txt");
    cout << "Initial position: " << fs.tellg() << endl;

    fs.seekg(6);  // go to position 6
    cout << "After seekg(6): read = '";
    char ch;
    while (fs.get(ch) && ch != '!') cout << ch;
    cout << "'" << endl;

    fs.seekg(0, ios::end);
    cout << "File size: " << fs.tellg() << " bytes" << endl;

    fs.seekg(0, ios::beg);
    cout << "Back to start: ";
    getline(fs, line);
    cout << line << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread AppendFile.cpp -o prog
 ================================================================

 === APPEND AND FILE POSITIONS ===

 --- Append Mode (ios::app) ---
 notes.txt contents:
   === My Notes ===
   First entry.
   Second entry.
   Third entry.

 --- Append Logging ---
 app.log contents:
   [2026-06-21 07:01:23] [INFO] Application started
   [2026-06-21 07:01:23] [INFO] User logged in: pavan@email.com
   [2026-06-21 07:01:23] [ERROR] Failed to connect to DB
   [2026-06-21 07:01:23] [INFO] Retry successful
   [2026-06-21 07:01:23] [INFO] Session ended

 --- File Seek (tellg, seekg) ---
 Initial position: 0
 After seekg(6): read = 'World'
 File size: 26 bytes
 Back to start: Hello World! C++ is great.

 ================================================================
*/

