/*
 * File    : Destructor.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Destructors — RAII, resource cleanup, virtual destructors
 * Date    : Week 5 - Day 3
 *
 * Notes:
 *   Destructor = cleanup function called automatically when object dies.
 *   Key rule: if you manually manage resources (heap, file, socket),
 *   write a destructor to release them.
 *
 *   RAII (Resource Acquisition Is Initialisation):
 *   - Acquire resource in constructor
 *   - Release resource in destructor
 *   - Guaranteed cleanup even if exception thrown
 *
 *   This is the pattern behind smart pointers, lock_guard, fstream, etc.
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ─────────────────────────────────────────
// Basic destructor demo
// ─────────────────────────────────────────
class DatabaseConnection {
    string host;
    bool   connected;
public:
    DatabaseConnection(string h) : host(h), connected(false) {
        cout << "  [CTOR] Opening connection to " << host << endl;
        connected = true;
    }

    void query(string sql) {
        if (!connected) { cout << "  Not connected!\n"; return; }
        cout << "  Running: " << sql << endl;
    }

    ~DatabaseConnection() {
        if (connected) {
            cout << "  [DTOR] Closing connection to " << host << endl;
            connected = false;
        }
    }
};

// ─────────────────────────────────────────
// RAII file wrapper
// ─────────────────────────────────────────
class FileGuard {
    fstream file;
    string  filename;
public:
    FileGuard(string fn, ios::openmode mode) : filename(fn) {
        file.open(fn, mode);
        cout << "  [FileGuard] Opened: " << filename << endl;
        if (!file.is_open()) throw runtime_error("Cannot open " + filename);
    }

    fstream& get() { return file; }
    bool isOpen()  { return file.is_open(); }

    ~FileGuard() {
        if (file.is_open()) {
            file.close();
            cout << "  [FileGuard] Auto-closed: " << filename << endl;
        }
    }
};

// ─────────────────────────────────────────
// Why virtual destructor matters
// ─────────────────────────────────────────
class Base {
public:
    Base()                    { cout << "  [Base CTOR]" << endl; }
    virtual ~Base()           { cout << "  [Base DTOR]" << endl; }  // VIRTUAL!
};

class Derived : public Base {
    int* resource;
public:
    Derived() : Base() {
        resource = new int[100];
        cout << "  [Derived CTOR] allocated 100 ints" << endl;
    }
    ~Derived() {
        delete[] resource;
        cout << "  [Derived DTOR] freed resource" << endl;
    }
};

// ─────────────────────────────────────────
// Order of construction/destruction
// ─────────────────────────────────────────
class A {
public:
    A() { cout << "  A constructed" << endl; }
   ~A() { cout << "  A destroyed"   << endl; }
};

class B {
public:
    B() { cout << "  B constructed" << endl; }
   ~B() { cout << "  B destroyed"   << endl; }
};

class C {
    A a;   // member — constructed before body
    B b;   // member — constructed before body
public:
    C() { cout << "  C body" << endl; }
   ~C() { cout << "  C destroyed (members destroyed in reverse)" << endl; }
};

int main() {
    cout << "=== DESTRUCTORS ===" << endl;

    // Basic destructor
    cout << "\n--- Basic Destructor (RAII) ---" << endl;
    {
        DatabaseConnection db("mysql://localhost:3306");
        db.query("SELECT * FROM users");
        db.query("UPDATE users SET active=1");
        // db's destructor auto-called here when scope ends
    }
    cout << "After scope — connection already closed" << endl;

    // RAII file guard
    cout << "\n--- RAII File Guard ---" << endl;
    try {
        FileGuard fg("test_raii.txt", ios::out | ios::trunc);
        fg.get() << "RAII is great!\n";
        // fg auto-closes file here even if exception thrown
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "File closed by RAII — no manual close needed" << endl;

    // Virtual destructor
    cout << "\n--- Virtual Destructor ---" << endl;
    Base* ptr = new Derived();
    delete ptr;   // WITHOUT virtual: only Base DTOR called → memory leak!
                  // WITH    virtual: Derived DTOR called first → correct

    // Constructor/Destructor order
    cout << "\n--- Construction/Destruction Order ---" << endl;
    {
        C obj;
        cout << "  (C obj in use)" << endl;
        // Members destroyed in REVERSE order: B, then A
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Destructor.cpp -o prog
 ================================================================

 === DESTRUCTORS ===

 --- Basic Destructor (RAII) ---
   [CTOR] Opening connection to mysql://localhost:3306
   Running: SELECT * FROM users
   Running: UPDATE users SET active=1
   [DTOR] Closing connection to mysql://localhost:3306
 After scope — connection already closed

 --- RAII File Guard ---
   [FileGuard] Opened: test_raii.txt
   [FileGuard] Auto-closed: test_raii.txt
 File closed by RAII — no manual close needed

 --- Virtual Destructor ---
   [Base CTOR]
   [Derived CTOR] allocated 100 ints
   [Derived DTOR] freed resource
   [Base DTOR]

 --- Construction/Destruction Order ---
   A constructed
   B constructed
   C body
   (C obj in use)
   C destroyed (members destroyed in reverse)
   B destroyed
   A destroyed

 ================================================================
*/

