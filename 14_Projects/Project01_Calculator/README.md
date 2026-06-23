# 🧮 Project 01 — Scientific Calculator

**Author:** Pavan Shetty H S  
**Concepts Used:** OOP, Exception Handling, `<cmath>`, File I/O for history

---

## ✨ Features

- Basic: Add, Subtract, Multiply, Divide, Modulo, Power
- Scientific: Square root, Log, Ln, Sin, Cos, Tan, Factorial, Absolute
- Memory: Store, Recall, Clear, Add-to-memory
- History: Last 10 calculations

## 🖥️ Sample Output

```
┌─────────────────────────────────┐
│      SCIENTIFIC CALCULATOR      │
├─────────────────────────────────┤
│ BASIC:    1.Add  2.Sub  3.Mul   │
│           4.Div  5.Mod  6.Pow   │
├─────────────────────────────────┤
│ SCIENCE:  7.Sqrt 8.Log  9.Ln    │
│          10.Sin 11.Cos 12.Tan   │
│          13.Abs 14.Fact          │
├─────────────────────────────────┤
│ MEMORY: 15.MS  16.MR  17.MC     │
├─────────────────────────────────┤
│ 18. History    0. Exit           │
└─────────────────────────────────┘
  Choice: 7
  x = 144
  √144 = 12.0000

  Choice: 14
  n = 6
  6! = 720

  Choice: 4
  a = 10
  b = 0
  ❌ Error: Division by zero!
```

## ▶️ Run

```bash
g++ -std=c++17 Calculator.cpp -o calc -lm
./calc
```
