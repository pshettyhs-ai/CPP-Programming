/*
 * File    : CustomException.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Custom Exception Classes
 * Date    : Week 9 - Day 2
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

// Custom exception hierarchy
class AppException : public runtime_error {
    int errorCode;
public:
    AppException(string msg, int code) : runtime_error(msg), errorCode(code) {}
    int getCode() const { return errorCode; }
};

class DatabaseException : public AppException {
    string query;
public:
    DatabaseException(string msg, string q)
        : AppException(msg, 500), query(q) {}
    string getQuery() const { return query; }
};

class AuthException : public AppException {
public:
    AuthException(string msg) : AppException(msg, 401) {}
};

class ValidationException : public AppException {
    string field;
public:
    ValidationException(string field_, string msg)
        : AppException(msg, 400), field(field_) {}
    string getField() const { return field; }
};

// Demo functions
void validateAge(int age) {
    if (age < 0 || age > 150)
        throw ValidationException("age", "Age must be between 0 and 150. Got: " + to_string(age));
}

void authenticateUser(string username, string password) {
    if (username != "admin" || password != "secret")
        throw AuthException("Invalid username or password.");
}

void queryDB(string sql) {
    if (sql.empty())
        throw DatabaseException("Empty query not allowed.", sql);
    if (sql.find("DROP TABLE") != string::npos)
        throw DatabaseException("Dangerous query blocked!", sql);
    cout << "DB query OK: " << sql << endl;
}

int main() {
    cout << "=== CUSTOM EXCEPTIONS ===" << endl;

    // Validation
    cout << "\n--- Validation Exceptions ---" << endl;
    for (int age : {25, -5, 200}) {
        try {
            validateAge(age);
            cout << "Age " << age << " is valid." << endl;
        } catch (const ValidationException& e) {
            cout << "Validation error [field=" << e.getField()
                 << ", code=" << e.getCode() << "]: " << e.what() << endl;
        }
    }

    // Auth
    cout << "\n--- Auth Exceptions ---" << endl;
    for (auto& [u, p] : vector<pair<string,string>>{{"admin","secret"},{"hacker","pass"}}) {
        try {
            authenticateUser(u, p);
            cout << "Login OK: " << u << endl;
        } catch (const AuthException& e) {
            cout << "Auth failed [" << e.getCode() << "]: " << e.what() << endl;
        }
    }

    // DB
    cout << "\n--- Database Exceptions ---" << endl;
    for (auto& q : {"SELECT * FROM users", "", "DROP TABLE users"}) {
        try {
            queryDB(q);
        } catch (const DatabaseException& e) {
            cout << "DB error: " << e.what() << " (query: '" << e.getQuery() << "')" << endl;
        }
    }

    // Catch by base class
    cout << "\n--- Polymorphic Catch ---" << endl;
    try {
        throw AuthException("Session expired.");
    } catch (const AppException& e) {
        cout << "AppException [" << e.getCode() << "]: " << e.what() << endl;
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread CustomException.cpp -o prog
 ================================================================

 === CUSTOM EXCEPTIONS ===

 --- Validation Exceptions ---
 Age 25 is valid.
 Validation error [field=age, code=400]: Age must be between 0 and 150. Got: -5
 Validation error [field=age, code=400]: Age must be between 0 and 150. Got: 200

 --- Auth Exceptions ---
 Login OK: admin
 Auth failed [401]: Invalid username or password.

 --- Database Exceptions ---
 DB query OK: SELECT * FROM users
 DB error: Empty query not allowed. (query: '')
 DB error: Dangerous query blocked! (query: 'DROP TABLE users')

 --- Polymorphic Catch ---
 AppException [401]: Session expired.

 ================================================================
*/

