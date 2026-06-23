/*
 * Project  : Inventory Management System
 * Author   : Pavan Shetty H S
 * Date     : Week 16
 *
 * Concepts: STL (map, vector), Templates, File I/O, OOP
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

struct Product {
    int    id;
    string name;
    string category;
    double costPrice;
    double sellingPrice;
    int    quantity;
    int    reorderLevel;

    Product() : id(0), costPrice(0), sellingPrice(0), quantity(0), reorderLevel(5) {}
    Product(int i, string n, string c, double cp, double sp, int qty, int rl = 5)
        : id(i), name(n), category(c), costPrice(cp), sellingPrice(sp),
          quantity(qty), reorderLevel(rl) {}

    bool needsReorder() const { return quantity <= reorderLevel; }
    double profit()     const { return (sellingPrice - costPrice) * quantity; }

    void display() const {
        cout << "  " << left << setw(6) << id
             << setw(24) << name.substr(0, 22)
             << setw(14) << category
             << right << setw(8) << "₹" + to_string((int)sellingPrice)
             << setw(7) << quantity
             << (needsReorder() ? "  ⚠ LOW" : "") << endl;
    }
};

struct SaleRecord {
    int    productId;
    string productName;
    int    quantity;
    double totalAmount;
    string date;
};

class Inventory {
    map<int, Product> products;
    vector<SaleRecord> sales;
    int nextId = 3001;
    double totalRevenue = 0;

    string today() { return "19/06/2025"; }

public:
    Inventory() {
        products[nextId] = Product(nextId++, "Arduino Uno R3",        "Microcontroller", 380,  650,  25, 5);
        products[nextId] = Product(nextId++, "STM32 F103C8T6",        "Microcontroller", 320,  550,  15, 3);
        products[nextId] = Product(nextId++, "ESP32 Dev Board",       "WiFi Module",     450,  750,  20, 5);
        products[nextId] = Product(nextId++, "16x2 LCD Display",      "Display",         85,   150,  40, 10);
        products[nextId] = Product(nextId++, "DHT22 Sensor",          "Sensor",          120,  200,  30, 8);
        products[nextId] = Product(nextId++, "HC-SR04 Ultrasonic",    "Sensor",          55,   110,  50, 10);
        products[nextId] = Product(nextId++, "L298N Motor Driver",    "Motor Driver",    95,   180,  3,  5);
        products[nextId] = Product(nextId++, "Jumper Wires (40pcs)",  "Accessories",     45,   100,  60, 15);
        products[nextId] = Product(nextId++, "Breadboard 830pts",     "Accessories",     75,   150,  35, 10);
        products[nextId] = Product(nextId++, "7805 Voltage Reg",      "Power",           8,    25,   100,20);
    }

    void addProduct() {
        string name, cat;
        double cp, sp;
        int qty, rl;
        cout << "  Name       : "; cin.ignore(); getline(cin, name);
        cout << "  Category   : "; getline(cin, cat);
        cout << "  Cost Price : ₹"; cin >> cp;
        cout << "  Sell Price : ₹"; cin >> sp;
        cout << "  Quantity   : "; cin >> qty;
        cout << "  Reorder Lvl: "; cin >> rl;
        products[nextId] = Product(nextId++, name, cat, cp, sp, qty, rl);
        cout << "  ✅ Product added. ID: " << (nextId - 1) << endl;
    }

    void restockProduct() {
        int id, qty;
        cout << "  Product ID : "; cin >> id;
        cout << "  Add Qty    : "; cin >> qty;
        if (products.count(id) == 0) { cout << "  ❌ Not found.\n"; return; }
        products[id].quantity += qty;
        cout << "  ✅ Restocked. New qty: " << products[id].quantity << endl;
    }

    void sellProduct() {
        int id, qty;
        cout << "  Product ID : "; cin >> id;
        cout << "  Quantity   : "; cin >> qty;
        if (products.count(id) == 0) { cout << "  ❌ Not found.\n"; return; }
        Product& p = products[id];
        if (qty > p.quantity) { cout << "  ❌ Insufficient stock. Available: " << p.quantity << endl; return; }
        p.quantity -= qty;
        double amount = qty * p.sellingPrice;
        totalRevenue += amount;
        sales.push_back({id, p.name, qty, amount, today()});
        cout << "  ✅ Sold " << qty << " x " << p.name << " = ₹" << fixed << setprecision(2) << amount << endl;
        if (p.needsReorder()) cout << "  ⚠ Stock low! Reorder soon." << endl;
    }

    void viewAllProducts() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    INVENTORY                                 ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "  " << left << setw(6) << "ID" << setw(24) << "Name"
             << setw(14) << "Category" << right << setw(8) << "Price" << setw(7) << "Qty" << endl;
        cout << "  " << string(60, '-') << endl;
        for (auto& [id, p] : products) p.display();
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << "  Total products: " << products.size() << endl;
    }

    void lowStockAlert() {
        cout << "\n⚠ LOW STOCK ALERT ⚠" << endl;
        bool any = false;
        for (auto& [id, p] : products) {
            if (p.needsReorder()) {
                cout << "  [" << id << "] " << p.name << " — Qty: " << p.quantity
                     << " (Reorder at: " << p.reorderLevel << ")" << endl;
                any = true;
            }
        }
        if (!any) cout << "  All products well-stocked." << endl;
    }

    void salesReport() {
        cout << "\n--- SALES REPORT ---" << endl;
        if (sales.empty()) { cout << "  No sales.\n"; return; }
        for (auto& s : sales) {
            cout << "  " << s.productName << " | Qty:" << s.quantity
                 << " | ₹" << fixed << setprecision(2) << s.totalAmount << endl;
        }
        cout << "  ─────────────────────\n";
        cout << "  Total Revenue: ₹" << totalRevenue << endl;
    }

    void searchProduct() {
        cout << "  Search by: 1.ID  2.Name  3.Category\n  Choice: ";
        int ch; cin >> ch;
        if (ch == 1) {
            int id; cout << "  ID: "; cin >> id;
            if (products.count(id)) products[id].display();
            else cout << "  ❌ Not found.\n";
        } else {
            string q; cout << "  Query: "; cin.ignore(); getline(cin, q);
            transform(q.begin(), q.end(), q.begin(), ::tolower);
            for (auto& [id, p] : products) {
                string field = (ch == 2) ? p.name : p.category;
                string fl = field;
                transform(fl.begin(), fl.end(), fl.begin(), ::tolower);
                if (fl.find(q) != string::npos) p.display();
            }
        }
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗" << endl;
            cout << "║   INVENTORY MANAGEMENT SYSTEM    ║" << endl;
            cout << "╠══════════════════════════════════╣" << endl;
            cout << "║  1. Add Product                  ║" << endl;
            cout << "║  2. Restock Product              ║" << endl;
            cout << "║  3. Sell Product                 ║" << endl;
            cout << "║  4. View All Products            ║" << endl;
            cout << "║  5. Low Stock Alert              ║" << endl;
            cout << "║  6. Sales Report                 ║" << endl;
            cout << "║  7. Search Product               ║" << endl;
            cout << "║  8. Exit                         ║" << endl;
            cout << "╚══════════════════════════════════╝" << endl;
            cout << "  Choice: "; cin >> choice;
            switch(choice) {
                case 1: addProduct();     break;
                case 2: restockProduct(); break;
                case 3: sellProduct();    break;
                case 4: viewAllProducts(); break;
                case 5: lowStockAlert();  break;
                case 6: salesReport();    break;
                case 7: searchProduct();  break;
                case 8: cout << "  Goodbye!\n"; break;
                default: cout << "  Invalid.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    Inventory inv;
    inv.run();
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread InventoryManagement.cpp -o prog
 ================================================================


 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ╔══════════════════════════════════════════════════════════════╗
 ║                    INVENTORY                                 ║
 ╠══════════════════════════════════════════════════════════════╣
   ID    Name                    Category         Price    Qty
   ------------------------------------------------------------
   3001  Arduino Uno R3          Microcontroller  ₹650     25
   3002  STM32 F103C8T6          Microcontroller  ₹550     15
   3003  ESP32 Dev Board         WiFi Module     ₹750     20
   3004  16x2 LCD Display        Display         ₹150     40
   3005  DHT22 Sensor            Sensor          ₹200     30
   3006  HC-SR04 Ultrasonic      Sensor          ₹110     50
   3007  L298N Motor Driver      Motor Driver    ₹180      3  ⚠ LOW
   3008  Jumper Wires (40pcs)    Accessories     ₹100     60
   3009  Breadboard 830pts       Accessories     ₹150     35
   3010  7805 Voltage Reg        Power            ₹25    100
 ╚══════════════════════════════════════════════════════════════╝
   Total products: 10

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 ⚠ LOW STOCK ALERT ⚠
   [3008] L298N Motor Driver — Qty: 3 (Reorder at: 5)

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Product ID :   Quantity   :   ✅ Sold 2 x HC-SR04 Ultrasonic = ₹220.00

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Product ID :   Add Qty    :   ✅ Restocked. New qty: 68

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Search by: 1.ID  2.Name  3.Category
   Choice:   Query:   3005  DHT22 Sensor            Sensor          ₹200     30

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice: 
 --- SALES REPORT ---
   HC-SR04 Ultrasonic | Qty:2 | ₹220.00
   ─────────────────────
   Total Revenue: ₹220.00

 ╔══════════════════════════════════╗
 ║   INVENTORY MANAGEMENT SYSTEM    ║
 ╠══════════════════════════════════╣
 ║  1. Add Product                  ║
 ║  2. Restock Product              ║
 ║  3. Sell Product                 ║
 ║  4. View All Products            ║
 ║  5. Low Stock Alert              ║
 ║  6. Sales Report                 ║
 ║  7. Search Product               ║
 ║  8. Exit                         ║
 ╚══════════════════════════════════╝
   Choice:   Goodbye!

 ================================================================
*/

