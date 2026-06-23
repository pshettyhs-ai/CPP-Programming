# 🏦 Project 02 — Bank Management System

**Author:** Pavan Shetty H S  
**Concepts Used:** OOP, Encapsulation, STL Map, File I/O, Exception Handling

---

## 📋 Project Overview

A complete console-based Bank Management System that simulates core banking operations. Built as a learning project to apply OOP concepts and exception handling in a real-world scenario.

## ✨ Features

- ✅ Create new account (Savings / Current)
- ✅ Deposit money
- ✅ Withdraw money (with PIN validation)
- ✅ Transfer money between accounts
- ✅ View account details
- ✅ View all accounts
- ✅ Transaction history (last 5)
- ✅ Exception handling for invalid operations

## 🏗️ Class Design

```
┌─────────────────┐     ┌───────────────────────┐
│    Transaction  │     │     BankAccount       │
│─────────────────│     │───────────────────────│
│ + type: string  │◄────│ - accountNumber: long │
│ + amount: double│     │ - holderName: string  │
│ + balance: dbl  │     │ - balance: double     │
│ + date: string  │     │ - pin: string         │
└─────────────────┘     │ - history: vector<T>  │
                        │───────────────────────│
                        │ + deposit()           │
                        │ + withdraw()          │
                        │ + displayDetails()    │
                        └───────────────────────┘
                                   ▲
                        ┌──────────┴────────────┐
                        │        Bank           │
                        │───────────────────────│
                        │ - accounts: map<>     │
                        │ - nextAccNumber: long │
                        │───────────────────────│
                        │ + createAccount()     │
                        │ + deposit()           │
                        │ + withdraw()          │
                        │ + transfer()          │
                        │ + viewAllAccounts()   │
                        └───────────────────────┘
```

## 🖥️ Sample Output

```
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
  Enter choice: 2

  Account Number: 100001
  Deposit Amount: 5000

✅ Deposit successful! New balance: ₹30000.00

╔══════════════════════════════════════╗
║       ACCOUNT DETAILS                ║
╠══════════════════════════════════════╣
║  Account No : 100001                 ║
║  Name       : Pavan Shetty H S       ║
║  Type       : SAVINGS                ║
║  Balance    : ₹30000.00              ║
║  Status     : ACTIVE                 ║
╚══════════════════════════════════════╝
```

## ▶️ Compilation & Run

```bash
g++ -std=c++17 -Wall BankManagement.cpp -o bank
./bank
```

## 📚 Learning Outcomes

- Applied encapsulation: sensitive data (PIN, balance) is private
- Used `std::map` for O(log n) account lookup by account number
- Exception handling makes the system robust
- Structured bindings (`auto& [key, val]`) from C++17

## 🚀 Future Improvements

- [ ] File persistence (save/load accounts)
- [ ] Interest calculation based on account type
- [ ] Multi-user login with admin panel
- [ ] GUI using Qt
