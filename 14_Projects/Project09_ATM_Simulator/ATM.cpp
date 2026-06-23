/*
 * Project  : ATM Simulator
 * Author   : Pavan Shetty H S
 * Date     : Week 16
 *
 * Simulates a complete ATM workflow including:
 * - Card insertion (account number)
 * - PIN verification with lockout
 * - Balance inquiry
 * - Cash withdrawal
 * - Mini statement
 * - PIN change
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
using namespace std;

class ATMAccount {
private:
    long   cardNumber;
    string pin;
    double balance;
    string holderName;
    int    failedAttempts;
    bool   isBlocked;
    vector<string> miniStatement;

public:
    ATMAccount(long card, string p, double bal, string name)
        : cardNumber(card), pin(p), balance(bal), holderName(name),
          failedAttempts(0), isBlocked(false) {}

    bool verifyPin(const string& inputPin) {
        if (isBlocked) throw runtime_error("Card blocked! Visit branch.");
        if (inputPin == pin) {
            failedAttempts = 0;
            return true;
        }
        failedAttempts++;
        if (failedAttempts >= 3) {
            isBlocked = true;
            throw runtime_error("3 wrong PINs. Card BLOCKED!");
        }
        throw runtime_error("Wrong PIN! " + to_string(3 - failedAttempts) + " attempt(s) remaining.");
    }

    double getBalance() const { return balance; }
    string getName() const    { return holderName; }
    long   getCard()  const   { return cardNumber; }

    void withdraw(double amount) {
        if (amount <= 0)       throw invalid_argument("Invalid amount.");
        if (amount > 20000)    throw runtime_error("Limit: ₹20,000 per transaction.");
        if (int(amount) % 100 != 0) throw runtime_error("Enter amount in multiples of ₹100.");
        if (amount > balance)  throw runtime_error("Insufficient balance.");
        balance -= amount;
        miniStatement.push_back("WDL ₹" + to_string((int)amount) + " Bal:₹" + to_string((int)balance));
    }

    void deposit(double amount) {
        balance += amount;
        miniStatement.push_back("DEP ₹" + to_string((int)amount) + " Bal:₹" + to_string((int)balance));
    }

    void changePin(const string& oldPin, const string& newPin) {
        verifyPin(oldPin);
        if (newPin.length() != 4) throw runtime_error("PIN must be exactly 4 digits.");
        pin = newPin;
    }

    void showMiniStatement() {
        cout << "\n  ---- MINI STATEMENT ----" << endl;
        if (miniStatement.empty()) { cout << "  No transactions." << endl; return; }
        int start = max(0, (int)miniStatement.size() - 5);
        for (int i = start; i < (int)miniStatement.size(); i++) {
            cout << "  " << miniStatement[i] << endl;
        }
        cout << "  Current Balance: ₹" << fixed << setprecision(2) << balance << endl;
    }
};

class ATM {
private:
    vector<ATMAccount> accounts;
    double cashAvailable;

    ATMAccount* findAccount(long cardNo) {
        for (auto& acc : accounts) {
            if (acc.getCard() == cardNo) return &acc;
        }
        return nullptr;
    }

    void printReceipt(string operation, double amount, double balance) {
        cout << "\n  ================================" << endl;
        cout << "       TRANSACTION RECEIPT" << endl;
        cout << "  ================================" << endl;
        cout << "  Operation : " << operation << endl;
        cout << "  Amount    : ₹" << fixed << setprecision(2) << amount << endl;
        cout << "  Balance   : ₹" << balance << endl;
        cout << "  ================================" << endl;
    }

public:
    ATM(double cash = 500000) : cashAvailable(cash) {
        // Pre-loaded accounts
        accounts.emplace_back(4111111111111111LL, "1234", 45000, "Pavan Shetty H S");
        accounts.emplace_back(4222222222222222LL, "5678", 12000, "Rahul Kumar");
        accounts.emplace_back(4333333333333333LL, "9999", 75000, "Priya Singh");
    }

    void run() {
        cout << "\n  ╔══════════════════════════╗" << endl;
        cout << "  ║     WELCOME TO ATM       ║" << endl;
        cout << "  ║    PavanBank Ltd.        ║" << endl;
        cout << "  ╚══════════════════════════╝" << endl;

        cout << "\n  Please insert your card (enter 16-digit card number): ";
        long cardNo;
        cin >> cardNo;

        ATMAccount* acc = findAccount(cardNo);
        if (!acc) {
            cout << "  ❌ Card not recognised. Returning card..." << endl;
            return;
        }

        cout << "  Card accepted. Welcome, " << acc->getName() << "!" << endl;

        // PIN verification
        int attempts = 3;
        bool authenticated = false;
        while (attempts > 0) {
            cout << "\n  Enter PIN: ";
            string pin;
            cin >> pin;
            try {
                acc->verifyPin(pin);
                authenticated = true;
                cout << "  ✅ PIN verified." << endl;
                break;
            } catch (const exception& e) {
                cout << "  ❌ " << e.what() << endl;
                attempts--;
            }
        }

        if (!authenticated) {
            cout << "  Card blocked and returned." << endl;
            return;
        }

        // Main ATM menu
        int choice;
        do {
            cout << "\n  ┌──────────────────────────┐" << endl;
            cout << "  │       ATM MENU           │" << endl;
            cout << "  ├──────────────────────────┤" << endl;
            cout << "  │  1. Balance Inquiry      │" << endl;
            cout << "  │  2. Cash Withdrawal      │" << endl;
            cout << "  │  3. Cash Deposit         │" << endl;
            cout << "  │  4. Mini Statement       │" << endl;
            cout << "  │  5. Change PIN           │" << endl;
            cout << "  │  6. Exit                 │" << endl;
            cout << "  └──────────────────────────┘" << endl;
            cout << "  Choice: ";
            cin >> choice;

            double amount;
            string oldPin, newPin;

            try {
                switch(choice) {
                case 1:
                    cout << "\n  Your current balance: ₹"
                         << fixed << setprecision(2) << acc->getBalance() << endl;
                    break;

                case 2:
                    cout << "  Enter amount (multiples of ₹100): ₹";
                    cin >> amount;
                    if (amount > cashAvailable)
                        throw runtime_error("ATM has insufficient cash. Try lower amount.");
                    acc->withdraw(amount);
                    cashAvailable -= amount;
                    printReceipt("WITHDRAWAL", amount, acc->getBalance());
                    cout << "  Please collect your cash: ₹" << (int)amount << endl;
                    break;

                case 3:
                    cout << "  Enter deposit amount: ₹";
                    cin >> amount;
                    acc->deposit(amount);
                    cashAvailable += amount;
                    printReceipt("DEPOSIT", amount, acc->getBalance());
                    break;

                case 4:
                    acc->showMiniStatement();
                    break;

                case 5:
                    cout << "  Old PIN: "; cin >> oldPin;
                    cout << "  New PIN: "; cin >> newPin;
                    acc->changePin(oldPin, newPin);
                    cout << "  ✅ PIN changed successfully!" << endl;
                    break;

                case 6:
                    cout << "\n  Thank you for using PavanBank ATM." << endl;
                    cout << "  Please take your card. Have a great day!" << endl;
                    break;

                default:
                    cout << "  Invalid choice." << endl;
                }
            } catch (const exception& e) {
                cout << "  ❌ " << e.what() << endl;
            }
        } while (choice != 6);
    }
};

int main() {
    ATM atm(500000);
    atm.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread ATM.cpp -o prog
 ================================================================


   ╔══════════════════════════╗
   ║     WELCOME TO ATM       ║
   ║    PavanBank Ltd.        ║
   ╚══════════════════════════╝

   Please insert your card (enter 16-digit card number):   Card accepted. Welcome, Pavan Shetty H S!

   Enter PIN:   ✅ PIN verified.

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice: 
   Your current balance: ₹45000.00

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice:   Enter amount (multiples of ₹100): ₹
   ================================
        TRANSACTION RECEIPT
   ================================
   Operation : WITHDRAWAL
   Amount    : ₹5000.00
   Balance   : ₹40000.00
   ================================
   Please collect your cash: ₹5000

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice:   Enter deposit amount: ₹
   ================================
        TRANSACTION RECEIPT
   ================================
   Operation : DEPOSIT
   Amount    : ₹2000.00
   Balance   : ₹42000.00
   ================================

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice: 
   ---- MINI STATEMENT ----
   WDL ₹5000 Bal:₹40000
   DEP ₹2000 Bal:₹42000
   Current Balance: ₹42000.00

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice:   Old PIN:   New PIN:   ✅ PIN changed successfully!

   ┌──────────────────────────┐
   │       ATM MENU           │
   ├──────────────────────────┤
   │  1. Balance Inquiry      │
   │  2. Cash Withdrawal      │
   │  3. Cash Deposit         │
   │  4. Mini Statement       │
   │  5. Change PIN           │
   │  6. Exit                 │
   └──────────────────────────┘
   Choice: 
   Thank you for using PavanBank ATM.
   Please take your card. Have a great day!

 ================================================================
*/

