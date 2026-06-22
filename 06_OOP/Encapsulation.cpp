/*
 * File    : Encapsulation.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Encapsulation — bundling data and restricting access
 * Date    : Week 5 - Day 3
 *
 * Notes:
 *   Encapsulation means hiding implementation details and exposing
 *   only what's necessary through a clean interface (getters/setters).
 *   
 *   Real-world analogy: ATM machine
 *   - You see: card slot, keypad, screen, cash dispenser
 *   - You don't see: internal bank servers, security logic, cash counting
 *   The internal details are ENCAPSULATED.
 */

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    string accountNumber;
    double balance;
    string pin;          // sensitive — never expose directly
    int    failedAttempts;
    bool   isLocked;

    bool validatePin(const string& inputPin) {
        if (isLocked) {
            throw runtime_error("Account is locked. Visit branch.");
        }
        if (inputPin == pin) {
            failedAttempts = 0;
            return true;
        }
        failedAttempts++;
        if (failedAttempts >= 3) {
            isLocked = true;
            throw runtime_error("Too many wrong PINs. Account locked.");
        }
        return false;
    }

public:
    BankAccount(string name, string accNo, double initial, string pinCode)
        : accountHolder(name), accountNumber(accNo),
          balance(initial), pin(pinCode),
          failedAttempts(0), isLocked(false) {}

    // Only expose necessary info, not sensitive data
    string getAccountHolder() const { return accountHolder; }
    string getAccountNumber() const {
        // Mask account number for security
        return "XXXX-XXXX-" + accountNumber.substr(accountNumber.length() - 4);
    }
    double getBalance(const string& inputPin) {
        if (validatePin(inputPin)) return balance;
        return -1;
    }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "  Invalid deposit amount." << endl;
            return false;
        }
        balance += amount;
        cout << "  Deposited: ₹" << amount << " | Balance: ₹" << balance << endl;
        return true;
    }

    bool withdraw(double amount, const string& inputPin) {
        if (!validatePin(inputPin)) {
            cout << "  Wrong PIN! Attempts left: " << (3 - failedAttempts) << endl;
            return false;
        }
        if (amount > balance) {
            cout << "  Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        cout << "  Withdrawn: ₹" << amount << " | Balance: ₹" << balance << endl;
        return true;
    }
};

int main() {
    cout << "=== ENCAPSULATION ===" << endl;

    BankAccount acc("Pavan Shetty H S", "9988776655", 25000.0, "1234");

    cout << "\nAccount Holder : " << acc.getAccountHolder() << endl;
    cout << "Account Number : " << acc.getAccountNumber() << " (masked)" << endl;

    // Cannot access: acc.balance, acc.pin, acc.failedAttempts — private!

    cout << "\n--- Transactions ---" << endl;
    acc.deposit(5000);
    acc.withdraw(3000, "1234");  // correct PIN
    acc.withdraw(1000, "9999");  // wrong PIN

    try {
        acc.withdraw(1000, "9999");  // wrong PIN again
        acc.withdraw(1000, "9999");  // locks account
    } catch (const runtime_error& e) {
        cout << "  Error: " << e.what() << endl;
    }

    cout << "\nBalance (with PIN): ₹" << acc.getBalance("1234") << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Encapsulation.cpp -o prog
 ================================================================

 NOTE: This program terminates abnormally (uncaught std::runtime_error
 leading to std::terminate / SIGABRT, exit code 134). The final call
 acc.getBalance("1234") on a now-locked account throws from inside
 validatePin(), and that throw is NOT wrapped in a try/catch (only the
 two withdraw() calls above it are). This is the program's actual,
 reproducible behavior as written above -- not a build problem.

 === ENCAPSULATION ===

 Account Holder : Pavan Shetty H S
 Account Number : XXXX-XXXX-6655 (masked)

 --- Transactions ---
   Deposited: ₹5000 | Balance: ₹30000
   Withdrawn: ₹3000 | Balance: ₹27000
   Wrong PIN! Attempts left: 2
   Wrong PIN! Attempts left: 1
   Error: Too many wrong PINs. Account locked.
 terminate called after throwing an instance of 'std::runtime_error'
   what():  Account is locked. Visit branch.

 [Process exited with status 134]

 ================================================================
*/

