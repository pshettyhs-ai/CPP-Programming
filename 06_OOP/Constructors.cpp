/*
 * File    : Constructors.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Constructors — all types + initializer list
 * Date    : Week 5 - Day 2
 */

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    double price;
    int    quantity;
    int    id;
    static int nextId;  // shared across all instances

public:
    // 1. Default Constructor
    Product() : name("Unknown"), price(0.0), quantity(0), id(++nextId) {
        cout << "  Default constructor → id=" << id << endl;
    }

    // 2. Parameterized Constructor (with member initializer list)
    Product(string n, double p, int q)
        : name(n), price(p), quantity(q), id(++nextId) {
        cout << "  Param constructor → " << name << " id=" << id << endl;
    }

    // 3. Copy Constructor
    Product(const Product& other)
        : name(other.name), price(other.price),
          quantity(other.quantity), id(++nextId) {
        cout << "  Copy constructor → copying " << other.name << " as new id=" << id << endl;
    }

    // 4. Move Constructor (C++11)
    Product(Product&& other) noexcept
        : name(move(other.name)), price(other.price),
          quantity(other.quantity), id(other.id) {
        other.id = -1;
        cout << "  Move constructor → moved resource" << endl;
    }

    void display() const {
        cout << "  [" << id << "] " << name << " | ₹" << price
             << " | Qty: " << quantity << endl;
    }

    ~Product() {
        if (id != -1)
            cout << "  Destructor → [" << id << "] " << name << endl;
    }
};

int Product::nextId = 0;  // static member initialization

// Delegating constructors (C++11)
class Config {
    string host;
    int    port;
    bool   ssl;
public:
    Config() : Config("localhost", 8080, false) {}  // delegates to main constructor
    Config(string h, int p) : Config(h, p, false) {}
    Config(string h, int p, bool s) : host(h), port(p), ssl(s) {}

    void show() {
        cout << "  Config: " << host << ":" << port << (ssl ? " [SSL]" : "") << endl;
    }
};

int main() {
    cout << "=== CONSTRUCTORS ===" << endl;

    cout << "\n--- Constructor Types ---" << endl;
    Product p1;                              // default
    Product p2("Laptop", 65000, 5);         // parameterized
    Product p3(p2);                          // copy
    Product p4(move(Product("Mouse", 500, 20))); // move (from temporary)

    cout << "\n--- Products ---" << endl;
    p1.display();
    p2.display();
    p3.display();
    p4.display();

    cout << "\n--- Delegating Constructors ---" << endl;
    Config c1;
    Config c2("api.example.com", 443);
    Config c3("db.server.com", 5432, true);
    c1.show(); c2.show(); c3.show();

    cout << "\n--- Destructors (auto-called) ---" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Constructors.cpp -o prog
 ================================================================

 === CONSTRUCTORS ===

 --- Constructor Types ---
   Default constructor → id=1
   Param constructor → Laptop id=2
   Copy constructor → copying Laptop as new id=3
   Param constructor → Mouse id=4
   Move constructor → moved resource

 --- Products ---
   [1] Unknown | ₹0 | Qty: 0
   [2] Laptop | ₹65000 | Qty: 5
   [3] Laptop | ₹65000 | Qty: 5
   [4] Mouse | ₹500 | Qty: 20

 --- Delegating Constructors ---
   Config: localhost:8080
   Config: api.example.com:443
   Config: db.server.com:5432 [SSL]

 --- Destructors (auto-called) ---
   Destructor → [4] Mouse
   Destructor → [3] Laptop
   Destructor → [2] Laptop
   Destructor → [1] Unknown

 ================================================================
*/

