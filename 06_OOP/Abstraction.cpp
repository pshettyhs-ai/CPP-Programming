/*
 * File    : Abstraction.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Abstraction — hiding complexity, showing essentials
 * Date    : Week 6 - Day 3
 *
 * Notes:
 *   Abstraction = showing WHAT something does, hiding HOW.
 *   Implemented in C++ via:
 *   1. Abstract classes (pure virtual functions)
 *   2. Interfaces (all pure virtual)
 *
 *   An abstract class CANNOT be instantiated directly.
 *   Any derived class MUST implement all pure virtual functions.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Abstract class (interface-like)
class DatabaseConnection {
public:
    virtual bool   connect(string host, int port) = 0;  // pure virtual
    virtual bool   disconnect()                   = 0;
    virtual bool   executeQuery(string query)     = 0;
    virtual string fetchResult()                  = 0;
    virtual string getConnectionType()            = 0;

    // Non-virtual method — concrete behaviour
    void showStatus() {
        cout << "  [" << getConnectionType() << "] Connection active." << endl;
    }

    virtual ~DatabaseConnection() {}
};

class MySQLConnection : public DatabaseConnection {
    bool connected = false;
public:
    bool connect(string host, int port) override {
        cout << "  MySQL: Connecting to " << host << ":" << port << endl;
        connected = true;
        return true;
    }
    bool disconnect() override {
        cout << "  MySQL: Disconnected." << endl;
        connected = false;
        return true;
    }
    bool executeQuery(string query) override {
        cout << "  MySQL: Running → " << query << endl;
        return connected;
    }
    string fetchResult() override { return "MySQL: {rows: 5, status: OK}"; }
    string getConnectionType() override { return "MySQL"; }
};

class SQLiteConnection : public DatabaseConnection {
    string dbFile;
    bool   open = false;
public:
    SQLiteConnection(string file) : dbFile(file) {}
    bool connect(string host, int port) override {
        cout << "  SQLite: Opening file " << dbFile << endl;
        open = true;
        return true;
    }
    bool disconnect() override {
        cout << "  SQLite: Closed " << dbFile << endl;
        open = false;
        return true;
    }
    bool executeQuery(string query) override {
        cout << "  SQLite: Executing → " << query << endl;
        return open;
    }
    string fetchResult() override { return "SQLite: {rows: 2, status: OK}"; }
    string getConnectionType() override { return "SQLite"; }
};

int main() {
    cout << "=== ABSTRACTION ===" << endl;

    // Cannot do: DatabaseConnection db;  → compile error! (abstract class)

    cout << "\n--- Polymorphic usage through abstraction ---" << endl;

    vector<DatabaseConnection*> connections;
    connections.push_back(new MySQLConnection());
    connections.push_back(new SQLiteConnection("local.db"));

    for (auto* conn : connections) {
        conn->connect("server", 5432);
        conn->showStatus();
        conn->executeQuery("SELECT * FROM users");
        cout << "  Result: " << conn->fetchResult() << endl;
        conn->disconnect();
        cout << endl;
    }

    for (auto* conn : connections) delete conn;

    cout << "Key point: we used the same interface (DatabaseConnection*)" << endl;
    cout << "for both MySQL and SQLite — that's abstraction in action." << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Abstraction.cpp -o prog
 ================================================================

 === ABSTRACTION ===

 --- Polymorphic usage through abstraction ---
   MySQL: Connecting to server:5432
   [MySQL] Connection active.
   MySQL: Running → SELECT * FROM users
   Result: MySQL: {rows: 5, status: OK}
   MySQL: Disconnected.

   SQLite: Opening file local.db
   [SQLite] Connection active.
   SQLite: Executing → SELECT * FROM users
   Result: SQLite: {rows: 2, status: OK}
   SQLite: Closed local.db

 Key point: we used the same interface (DatabaseConnection*)
 for both MySQL and SQLite — that's abstraction in action.

 ================================================================
*/

