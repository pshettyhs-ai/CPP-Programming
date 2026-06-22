/*
 * File    : Inheritance.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Inheritance — all 5 types in C++
 * Date    : Week 6 - Day 1
 *
 * Notes:
 *   Inheritance = creating a new class from an existing class.
 *   The new class (derived/child) gets all the features of the
 *   existing class (base/parent) and can add its own.
 *
 *   5 types in C++:
 *   1. Single       — one base, one derived
 *   2. Multi-level  — A → B → C chain
 *   3. Multiple     — one derived from multiple bases
 *   4. Hierarchical — one base, multiple derived
 *   5. Hybrid       — combination (has diamond problem)
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ─────────────────────────────────────────
// TYPE 1: SINGLE INHERITANCE
// ─────────────────────────────────────────
class Animal {
protected:
    string name;
    int    age;
public:
    Animal(string n, int a) : name(n), age(a) {}
    void breathe()  { cout << name << " breathes oxygen." << endl; }
    void eat()      { cout << name << " eats food." << endl; }
    virtual void sound() { cout << name << " makes a sound." << endl; }
};

class Dog : public Animal {
private:
    string breed;
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}  // calling base constructor
    void fetch()  { cout << name << " fetches the ball!" << endl; }
    void sound() override { cout << name << " says: Woof! Woof!" << endl; }
    void display() {
        cout << "Dog: " << name << " | Age: " << age << " | Breed: " << breed << endl;
    }
};

// ─────────────────────────────────────────
// TYPE 2: MULTILEVEL INHERITANCE
// ─────────────────────────────────────────
class Person {
protected:
    string personName;
    int    personAge;
public:
    Person(string n, int a) : personName(n), personAge(a) {}
    void introduce() {
        cout << "I am " << personName << ", aged " << personAge << endl;
    }
};

class Employee : public Person {
protected:
    string company;
    double salary;
public:
    Employee(string n, int a, string c, double s)
        : Person(n, a), company(c), salary(s) {}
    void work() {
        cout << personName << " works at " << company << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize;
public:
    Manager(string n, int a, string c, double s, int ts)
        : Employee(n, a, c, s), teamSize(ts) {}
    void manage() {
        cout << personName << " manages a team of " << teamSize << " people." << endl;
    }
    void display() {
        cout << "Manager: " << personName << " | Company: " << company
             << " | Salary: " << salary << " | Team: " << teamSize << endl;
    }
};

// ─────────────────────────────────────────
// TYPE 3: MULTIPLE INHERITANCE
// ─────────────────────────────────────────
class Flyable {
public:
    void fly() { cout << "Flying in the sky!" << endl; }
};

class Swimmable {
public:
    void swim() { cout << "Swimming in water!" << endl; }
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(string n) : Animal(n, 2) {}
    void sound() override { cout << name << " says: Quack! Quack!" << endl; }
    void showTalents() {
        cout << name << " can: ";
        fly(); swim(); sound();
    }
};

// ─────────────────────────────────────────
// TYPE 4: HIERARCHICAL INHERITANCE
// ─────────────────────────────────────────
class Shape {
protected:
    string color;
public:
    Shape(string c) : color(c) {}
    virtual double area()      = 0;  // pure virtual
    virtual double perimeter() = 0;  // pure virtual
    virtual void display() {
        cout << "Shape | Color: " << color << endl;
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(string c, double r) : Shape(c), radius(r) {}
    double area()      override { return 3.14159 * radius * radius; }
    double perimeter() override { return 2 * 3.14159 * radius; }
    void display() override {
        cout << "Circle | Color: " << color << " | Radius: " << radius
             << " | Area: " << area() << endl;
    }
};

class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {}
    double area()      override { return length * width; }
    double perimeter() override { return 2 * (length + width); }
    void display() override {
        cout << "Rectangle | Color: " << color << " | " << length << "x" << width
             << " | Area: " << area() << endl;
    }
};

class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(string col, double x, double y, double z) : Shape(col), a(x), b(y), c(z) {}
    double area() override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s-a) * (s-b) * (s-c));  // Heron's formula
    }
    double perimeter() override { return a + b + c; }
    void display() override {
        cout << "Triangle | Color: " << color << " | Sides: " << a
             << "," << b << "," << c << " | Area: " << area() << endl;
    }
};

int main() {
    cout << "=== INHERITANCE ===" << endl;

    // Type 1: Single
    cout << "\n--- Single Inheritance ---" << endl;
    Dog d("Bruno", 3, "German Shepherd");
    d.display();
    d.breathe();   // inherited from Animal
    d.eat();       // inherited from Animal
    d.sound();     // overridden in Dog
    d.fetch();     // Dog's own method

    // Type 2: Multilevel
    cout << "\n--- Multilevel Inheritance ---" << endl;
    Manager mgr("Pavan Shetty", 28, "TechCorp", 150000, 8);
    mgr.introduce();  // from Person
    mgr.work();       // from Employee
    mgr.manage();     // Manager's own
    mgr.display();

    // Type 3: Multiple
    cout << "\n--- Multiple Inheritance ---" << endl;
    Duck duck("Donald");
    duck.showTalents();

    // Type 4: Hierarchical
    cout << "\n--- Hierarchical Inheritance (Polymorphism) ---" << endl;
    Shape* shapes[] = {
        new Circle("Red", 5),
        new Rectangle("Blue", 4, 6),
        new Triangle("Green", 3, 4, 5)
    };

    for (Shape* s : shapes) {
        s->display();
    }

    // Cleanup
    for (Shape* s : shapes) delete s;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Inheritance.cpp -o prog
 ================================================================

 === INHERITANCE ===

 --- Single Inheritance ---
 Dog: Bruno | Age: 3 | Breed: German Shepherd
 Bruno breathes oxygen.
 Bruno eats food.
 Bruno says: Woof! Woof!
 Bruno fetches the ball!

 --- Multilevel Inheritance ---
 I am Pavan Shetty, aged 28
 Pavan Shetty works at TechCorp
 Pavan Shetty manages a team of 8 people.
 Manager: Pavan Shetty | Company: TechCorp | Salary: 150000 | Team: 8

 --- Multiple Inheritance ---
 Donald can: Flying in the sky!
 Swimming in water!
 Donald says: Quack! Quack!

 --- Hierarchical Inheritance (Polymorphism) ---
 Circle | Color: Red | Radius: 5 | Area: 78.5397
 Rectangle | Color: Blue | 4x6 | Area: 24
 Triangle | Color: Green | Sides: 3,4,5 | Area: 6

 ================================================================
*/

