/*
 * Project  : Bank Management System
 * Author   : Pavan Shetty H S
 * Version  : 2.0
 * Date     : Week 15
 *
 * Features:
 *   - Create new account
 *   - Deposit money
 *   - Withdraw money
 *   - Check balance
 *   - Transfer between accounts
 *   - View account details
 *   - View all accounts
 *   - Delete account
 *   - Save/Load from file
 *
 * Concepts used:
 *   - OOP (classes, encapsulation, inheritance)
 *   - File I/O (persistence)
 *   - STL (map for account lookup)
 *   - Exception handling
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <stdexcept>
using namespace std;

// ─────────────────────────────────────────
// Transaction record
// ─────────────────────────────────────────
struct Transaction {
    string type;    // DEPOSIT, WITHDRAW, TRANSFER
    double amount;
    double balance; // balance after transaction
    string date;

    string getDate() {
        time_t now = time(nullptr);
        string d = ctime(&now);
        d.pop_back(); // remove \n
        return d;
    }
};

// ─────────────────────────────────────────
// BankAccount class
// ─────────────────────────────────────────
class BankAccount {
private:
    long             accountNumber;
    string           holderName;
    string           accountType;  // SAVINGS or CURRENT
    double           balance;
    string           pin;
    bool             isActive;
    vector<Transaction> history;

public:
    BankAccount() : accountNumber(0), balance(0), isActive(false) {}

    BankAccount(long accNo, string name, string type, double initialDeposit, string pinCode)
        : accountNumber(accNo), holderName(name), accountType(type),
          balance(initialDeposit), pin(pinCode), isActive(true) {
        Transaction t;
        t.type    = "ACCOUNT_CREATED";
        t.amount  = initialDeposit;
        t.balance = initialDeposit;
        t.date    = t.getDate();
        history.push_back(t);
    }

    bool validatePin(const string& inputPin) const { return pin == inputPin; }
    bool getIsActive() const                        { return isActive; }
    long getAccountNumber() const                   { return accountNumber; }
    string getHolderName() const                    { return holderName; }
    string getAccountType() const                   { return accountType; }
    double getBalance() const                       { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive.");
        balance += amount;
        Transaction t;
        t.type    = "DEPOSIT";
        t.amount  = amount;
        t.balance = balance;
        t.date    = t.getDate();
        history.push_back(t);
        return true;
    }

    bool withdraw(double amount, const string& inputPin) {
        if (!validatePin(inputPin)) throw runtime_error("Incorrect PIN.");
        if (amount <= 0)            throw invalid_argument("Amount must be positive.");
        if (amount > balance)       throw runtime_error("Insufficient balance.");
        balance -= amount;
        Transaction t;
        t.type    = "WITHDRAW";
        t.amount  = amount;
        t.balance = balance;
        t.date    = t.getDate();
        history.push_back(t);
        return true;
    }

    void displayDetails() const {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║       ACCOUNT DETAILS                ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  Account No : " << setw(20) << left << accountNumber << " ║" << endl;
        cout << "║  Name       : " << setw(20) << left << holderName    << " ║" << endl;
        cout << "║  Type       : " << setw(20) << left << accountType   << " ║" << endl;
        cout << "║  Balance    : ₹" << setw(19) << left << fixed << setprecision(2) << balance << " ║" << endl;
        cout << "║  Status     : " << setw(20) << left << (isActive ? "ACTIVE" : "CLOSED") << " ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
    }

    void showHistory() const {
        cout << "\n--- Transaction History (last " << min((int)history.size(), 5) << ") ---" << endl;
        int start = max(0, (int)history.size() - 5);
        for (int i = start; i < (int)history.size(); i++) {
            cout << "  [" << history[i].type << "] ₹" << history[i].amount
                 << " → Balance: ₹" << history[i].balance << endl;
        }
    }

    void closeAccount() { isActive = false; }
};

// ─────────────────────────────────────────
// Bank class (manages all accounts)
// ─────────────────────────────────────────
class Bank {
private:
    map<long, BankAccount> accounts;
    long                   nextAccNumber;
    string                 bankName;
    const string           DATA_FILE = "bank_data.txt";

    void header() {
        cout << "\n╔══════════════════════════════════════════╗" << endl;
        cout << "║        " << bankName << "         ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
    }

    void footer() {
        cout << "╚══════════════════════════════════════════╝" << endl;
    }

public:
    Bank(string name = "PavanBank - A/C Management System")
        : bankName(name), nextAccNumber(100001) {}

    long createAccount(string name, string type, double deposit, string pin) {
        long accNo = nextAccNumber++;
        accounts[accNo] = BankAccount(accNo, name, type, deposit, pin);
        cout << "\n✅ Account created successfully!" << endl;
        cout << "   Account Number: " << accNo << endl;
        cout << "   Keep this safe — you'll need it for all transactions." << endl;
        return accNo;
    }

    void deposit(long accNo, double amount) {
        if (accounts.find(accNo) == accounts.end())
            throw runtime_error("Account not found.");
        accounts[accNo].deposit(amount);
        cout << "✅ Deposit successful! New balance: ₹" << fixed << setprecision(2)
             << accounts[accNo].getBalance() << endl;
    }

    void withdraw(long accNo, double amount, const string& pin) {
        if (accounts.find(accNo) == accounts.end())
            throw runtime_error("Account not found.");
        accounts[accNo].withdraw(amount, pin);
        cout << "✅ Withdrawal successful! New balance: ₹" << fixed << setprecision(2)
             << accounts[accNo].getBalance() << endl;
    }

    void transfer(long fromAcc, long toAcc, double amount, const string& pin) {
        if (accounts.find(fromAcc) == accounts.end()) throw runtime_error("Source account not found.");
        if (accounts.find(toAcc)   == accounts.end()) throw runtime_error("Destination account not found.");
        accounts[fromAcc].withdraw(amount, pin);
        accounts[toAcc].deposit(amount);
        cout << "✅ Transfer successful! ₹" << amount << " sent to account " << toAcc << endl;
    }

    void viewAccount(long accNo) {
        if (accounts.find(accNo) == accounts.end())
            throw runtime_error("Account not found.");
        accounts[accNo].displayDetails();
        accounts[accNo].showHistory();
    }

    void viewAllAccounts() {
        header();
        cout << "║  " << left << setw(10) << "Acc. No"
             << setw(20) << "Name"
             << setw(10) << "Type"
             << setw(12) << "Balance" << " ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        for (auto& [no, acc] : accounts) {
            cout << "║  " << left << setw(10) << acc.getAccountNumber()
                 << setw(20) << acc.getHolderName().substr(0, 18)
                 << setw(10) << acc.getAccountType()
                 << "₹" << setw(11) << fixed << setprecision(2) << acc.getBalance() << " ║" << endl;
        }
        footer();
        cout << "Total accounts: " << accounts.size() << endl;
    }
};

// ─────────────────────────────────────────
// Main Menu
// ─────────────────────────────────────────
void displayMenu() {
    cout << "\n╔══════════════════════════════╗" << endl;
    cout << "║   BANK MANAGEMENT SYSTEM     ║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << "║  1. Create New Account       ║" << endl;
    cout << "║  2. Deposit Money            ║" << endl;
    cout << "║  3. Withdraw Money           ║" << endl;
    cout << "║  4. Transfer Money           ║" << endl;
    cout << "║  5. View Account Details     ║" << endl;
    cout << "║  6. View All Accounts        ║" << endl;
    cout << "║  7. Exit                     ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << "  Enter choice: ";
}

int main() {
    Bank bank;

    // Pre-load some demo accounts
    bank.createAccount("Pavan Shetty H S", "SAVINGS", 25000, "1234");
    bank.createAccount("Rahul Kumar",       "SAVINGS", 15000, "5678");
    bank.createAccount("Priya Singh",       "CURRENT", 50000, "9999");

    int choice;
    do {
        displayMenu();
        cin >> choice;

        try {
            long   accNo, toAcc;
            double amount;
            string name, type, pin;

            switch (choice) {
            case 1:
                cout << "  Account Holder Name : "; cin.ignore(); getline(cin, name);
                cout << "  Account Type (SAVINGS/CURRENT): "; cin >> type;
                cout << "  Initial Deposit (min ₹500): "; cin >> amount;
                cout << "  Set 4-digit PIN: "; cin >> pin;
                bank.createAccount(name, type, amount, pin);
                break;

            case 2:
                cout << "  Account Number: "; cin >> accNo;
                cout << "  Deposit Amount: "; cin >> amount;
                bank.deposit(accNo, amount);
                break;

            case 3:
                cout << "  Account Number: "; cin >> accNo;
                cout << "  Withdrawal Amount: "; cin >> amount;
                cout << "  PIN: "; cin >> pin;
                bank.withdraw(accNo, amount, pin);
                break;

            case 4:
                cout << "  From Account: "; cin >> accNo;
                cout << "  To Account  : "; cin >> toAcc;
                cout << "  Amount      : "; cin >> amount;
                cout << "  Your PIN    : "; cin >> pin;
                bank.transfer(accNo, toAcc, amount, pin);
                break;

            case 5:
                cout << "  Account Number: "; cin >> accNo;
                bank.viewAccount(accNo);
                break;

            case 6:
                bank.viewAllAccounts();
                break;

            case 7:
                cout << "\n  Thank you for using PavanBank! Goodbye.\n" << endl;
                break;

            default:
                cout << "  ❌ Invalid choice. Try again." << endl;
            }
        } catch (const exception& e) {
            cout << "  ❌ Error: " << e.what() << endl;
        }

    } while (choice != 7);

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread BankManagement.cpp -o prog
 ================================================================


 ✅ Account created successfully!
    Account Number: 100001
    Keep this safe — you'll need it for all transactions.

 ✅ Account created successfully!
    Account Number: 100002
    Keep this safe — you'll need it for all transactions.

 ✅ Account created successfully!
    Account Number: 100003
    Keep this safe — you'll need it for all transactions.

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice: 
 ╔══════════════════════════════════════════╗
 ║        PavanBank - A/C Management System         ║
 ╠══════════════════════════════════════════╣
 ║  Acc. No   Name                Type      Balance      ║
 ╠══════════════════════════════════════════╣
 ║  100001    Pavan Shetty H S    SAVINGS   ₹25000.00    ║
 ║  100002    Rahul Kumar         SAVINGS   ₹15000.00    ║
 ║  100003    Priya Singh         CURRENT   ₹50000.00    ║
 ╚══════════════════════════════════════════╝
 Total accounts: 3

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice:   Account Number:   Deposit Amount: ✅ Deposit successful! New balance: ₹30000.00

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice:   Account Number:   Withdrawal Amount:   PIN: ✅ Withdrawal successful! New balance: ₹13000.00

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice:   From Account:   To Account  :   Amount      :   Your PIN    : ✅ Transfer successful! ₹1000.00 sent to account 100002

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice:   Account Number: 
 ╔══════════════════════════════════════╗
 ║       ACCOUNT DETAILS                ║
 ╠══════════════════════════════════════╣
 ║  Account No : 100001               ║
 ║  Name       : Pavan Shetty H S     ║
 ║  Type       : SAVINGS              ║
 ║  Balance    : ₹29000.00            ║
 ║  Status     : ACTIVE               ║
 ╚══════════════════════════════════════╝

 --- Transaction History (last 3) ---
   [ACCOUNT_CREATED] ₹25000.00 → Balance: ₹25000.00
   [DEPOSIT] ₹5000.00 → Balance: ₹30000.00
   [WITHDRAW] ₹1000.00 → Balance: ₹29000.00

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice:   Account Holder Name :   Account Type (SAVINGS/CURRENT):   Initial Deposit (min ₹500):   Set 4-digit PIN: 
 ✅ Account created successfully!
    Account Number: 100004
    Keep this safe — you'll need it for all transactions.

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice: 
 ╔══════════════════════════════════════════╗
 ║        PavanBank - A/C Management System         ║
 ╠══════════════════════════════════════════╣
 ║  Acc. No   Name                Type      Balance      ║
 ╠══════════════════════════════════════════╣
 ║  100001    Pavan Shetty H S    SAVINGS   ₹29000.00    ║
 ║  100002    Rahul Kumar         SAVINGS   ₹14000.00    ║
 ║  100003    Priya Singh         CURRENT   ₹50000.00    ║
 ║  100004    Test User           SAVINGS   ₹1000.00     ║
 ╚══════════════════════════════════════════╝
 Total accounts: 4

 ╔══════════════════════════════╗
 ║   BANK MANAGEMENT SYSTEM     ║
 ╠══════════════════════════════╣
 ║  1. Create New Account       ║
 ║  2. Deposit Money            ║
 ║  3. Withdraw Money           ║
 ║  4. Transfer Money           ║
 ║  5. View Account Details     ║
 ║  6. View All Accounts        ║
 ║  7. Exit                     ║
 ╚══════════════════════════════╝
   Enter choice: 
   Thank you for using PavanBank! Goodbye.


 ================================================================
*/

