/*
 * File    : Objects.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Objects — creation, types, this pointer, static members
 * Date    : Week 5 - Day 2
 */

#include <iostream>
#include <string>
using namespace std;

class Counter {
private:
    int   value;
    string name;
    static int instanceCount;  // shared by ALL Counter objects

public:
    Counter(string n = "Counter", int start = 0) : name(n), value(start) {
        instanceCount++;
        cout << "  Created '" << name << "' (total instances: " << instanceCount << ")" << endl;
    }

    void increment(int by = 1) { value += by; }
    void decrement(int by = 1) { value -= by; }
    void reset()               { value = 0; }

    int    getValue() const { return value; }
    string getName()  const { return name; }

    // 'this' pointer — points to current object
    Counter& setName(string n) {
        this->name = n;   // this-> disambiguates from param name
        return *this;     // return reference to self (enables chaining)
    }

    Counter& setValue(int v) {
        this->value = v;
        return *this;
    }

    // Static members — belong to class, not any instance
    static int getInstanceCount() { return instanceCount; }
    static void resetAll() { instanceCount = 0; }

    void display() const {
        cout << "  Counter[" << name << "] = " << value << endl;
    }

    ~Counter() {
        instanceCount--;
        cout << "  Destroyed '" << name << "' (remaining: " << instanceCount << ")" << endl;
    }
};

// Must define static member outside class
int Counter::instanceCount = 0;

int main() {
    cout << "=== OBJECTS & STATIC MEMBERS ===" << endl;

    cout << "\n--- Creating objects ---" << endl;
    Counter c1("PageViews", 0);
    Counter c2("LoginCount");
    Counter c3("Errors", 5);

    cout << "\nTotal instances: " << Counter::getInstanceCount() << endl;

    cout << "\n--- Method chaining (using 'this') ---" << endl;
    Counter c4("Temp");
    c4.setName("Requests").setValue(100);
    c4.display();

    cout << "\n--- Operations ---" << endl;
    c1.increment(50);
    c2.increment();
    c3.decrement(2);
    c1.display();
    c2.display();
    c3.display();

    cout << "\n--- Object array ---" << endl;
    Counter sensors[3] = {
        Counter("Temp"),
        Counter("Humidity"),
        Counter("Pressure")
    };
    for (int i = 0; i < 3; i++) sensors[i].increment((i+1) * 10);
    for (int i = 0; i < 3; i++) sensors[i].display();

    cout << "\n--- Scope ends, destructors called ---" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Objects.cpp -o prog
 ================================================================

 === OBJECTS & STATIC MEMBERS ===

 --- Creating objects ---
   Created 'PageViews' (total instances: 1)
   Created 'LoginCount' (total instances: 2)
   Created 'Errors' (total instances: 3)

 Total instances: 3

 --- Method chaining (using 'this') ---
   Created 'Temp' (total instances: 4)
   Counter[Requests] = 100

 --- Operations ---
   Counter[PageViews] = 50
   Counter[LoginCount] = 1
   Counter[Errors] = 3

 --- Object array ---
   Created 'Temp' (total instances: 5)
   Created 'Humidity' (total instances: 6)
   Created 'Pressure' (total instances: 7)
   Counter[Temp] = 10
   Counter[Humidity] = 20
   Counter[Pressure] = 30

 --- Scope ends, destructors called ---
   Destroyed 'Pressure' (remaining: 6)
   Destroyed 'Humidity' (remaining: 5)
   Destroyed 'Temp' (remaining: 4)
   Destroyed 'Requests' (remaining: 3)
   Destroyed 'Errors' (remaining: 2)
   Destroyed 'LoginCount' (remaining: 1)
   Destroyed 'PageViews' (remaining: 0)

 ================================================================
*/

