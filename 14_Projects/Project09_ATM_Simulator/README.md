# 🏧 Project 09 — ATM Simulator

**Author:** Pavan Shetty H S  
**Concepts Used:** OOP, Encapsulation, Exception Handling, Input Validation

---

## ✨ Features

- Card number verification
- PIN validation with 3-attempt lockout
- Balance inquiry
- Cash withdrawal (multiples of ₹100, max ₹20,000)
- Cash deposit
- Mini statement (last 5 transactions)
- PIN change

## 🖥️ Sample Output

```
  ╔══════════════════════════╗
  ║     WELCOME TO ATM       ║
  ║    PavanBank Ltd.        ║
  ╚══════════════════════════╝

  Please insert your card (enter 16-digit card number): 4111111111111111
  Card accepted. Welcome, Pavan Shetty H S!

  Enter PIN: 1234
  ✅ PIN verified.

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
  Choice: 2
  Enter amount (multiples of ₹100): ₹5000

  ================================
       TRANSACTION RECEIPT
  ================================
  Operation : WITHDRAWAL
  Amount    : ₹5000.00
  Balance   : ₹40000.00
  ================================
  Please collect your cash: ₹5000
```

## ▶️ Run

```bash
g++ -std=c++17 ATM.cpp -o atm
./atm
```

## 📚 Learning Outcomes

- Encapsulation: PIN, balance hidden; accessed only through methods
- Exception hierarchy for different error types
- RAII-like PIN lockout mechanism
- Input validation patterns
