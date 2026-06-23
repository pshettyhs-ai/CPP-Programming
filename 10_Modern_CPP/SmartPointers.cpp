/*
 * File    : SmartPointers.cpp (Modern C++)
 * Author  : Pavan Shetty H S
 * Topic   : Smart Pointers — deep dive with real patterns
 * Date    : Week 10 - Day 4
 *
 * Notes:
 *   Covered basics in 05_Pointers/SmartPointers.cpp.
 *   Here: focusing on real-world usage patterns and pitfalls.
 *
 *   Golden rules:
 *   1. Prefer unique_ptr — zero overhead, explicit ownership
 *   2. Use shared_ptr only when truly multiple owners
 *   3. Watch out for circular references → use weak_ptr
 *   4. Never mix smart and raw pointer ownership
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    int    value;
    string name;
    shared_ptr<Node> next;    // forward link
    weak_ptr<Node>   parent;  // back-link — weak to avoid circular reference!

    Node(int v, string n) : value(v), name(n) {
        cout << "  [Node '" << name << "' created]" << endl;
    }
    ~Node() {
        cout << "  [Node '" << name << "' destroyed]" << endl;
    }
};

// Factory pattern with unique_ptr
class Connection {
    string host;
    int    port;
    bool   open_;
public:
    Connection(string h, int p) : host(h), port(p), open_(true) {
        cout << "  [Connecting to " << host << ":" << port << "]" << endl;
    }
    ~Connection() {
        if (open_) {
            cout << "  [Disconnecting from " << host << "]" << endl;
        }
    }
    void query(string sql) const { cout << "  Query: " << sql << endl; }
    bool isOpen() const { return open_; }
};

// Factory function — returns unique_ptr
unique_ptr<Connection> createConnection(string host, int port) {
    return make_unique<Connection>(host, port);
}

// Function that borrows without taking ownership
void performQuery(const Connection& conn, string sql) {
    conn.query(sql);
}

int main() {
    cout << "=== SMART POINTERS (ADVANCED) ===" << endl;

    // 1. unique_ptr as factory return
    cout << "\n--- unique_ptr Factory Pattern ---" << endl;
    {
        auto conn = createConnection("db.server.com", 5432);
        performQuery(*conn, "SELECT * FROM users LIMIT 10");
        performQuery(*conn, "SELECT count(*) FROM orders");
    }  // connection auto-closed here
    cout << "Scope exited — connection properly closed." << endl;

    // 2. unique_ptr in containers
    cout << "\n--- unique_ptr in vector ---" << endl;
    vector<unique_ptr<Connection>> pool;
    pool.push_back(make_unique<Connection>("primary.db", 5432));
    pool.push_back(make_unique<Connection>("replica.db", 5432));
    pool.push_back(make_unique<Connection>("cache.db",   6379));

    for (auto& conn : pool) {
        conn->query("PING");
    }
    pool.clear();  // all connections closed
    cout << "Pool cleared — all connections closed." << endl;

    // 3. shared_ptr — multiple owners
    cout << "\n--- shared_ptr Multiple Owners ---" << endl;
    {
        auto node1 = make_shared<Node>(1, "Root");
        {
            auto node2 = make_shared<Node>(2, "Child");
            node1->next = node2;  // node1 holds a reference to node2
            cout << "  node2 ref count: " << node2.use_count() << " (node1 + local)" << endl;
        }
        // node2 local is gone, but node1->next still holds it
        cout << "  After inner scope: node1->next still valid: "
             << (node1->next ? "yes" : "no") << endl;
        cout << "  node1->next ref count: " << node1->next.use_count() << endl;
    }
    cout << "Outer scope done — nodes destroyed." << endl;

    // 4. Circular reference problem (and weak_ptr fix)
    cout << "\n--- weak_ptr breaks Circular Reference ---" << endl;
    {
        auto parent = make_shared<Node>(10, "Parent");
        auto child  = make_shared<Node>(20, "Child");

        parent->next = child;    // parent → child (shared_ptr)
        child->parent = parent;  // child → parent (WEAK — no ownership)

        cout << "  parent ref count: " << parent.use_count() << endl;
        cout << "  child  ref count: " << child.use_count()  << endl;

        // Access parent through weak_ptr
        if (auto p = child->parent.lock()) {
            cout << "  Child's parent: " << p->name << " (value=" << p->value << ")" << endl;
        }
    }
    // Both destroyed correctly — no memory leak!
    cout << "No memory leak — weak_ptr broke the cycle." << endl;

    // 5. custom deleter
    cout << "\n--- Custom Deleter ---" << endl;
    auto customDeleter = [](int* p) {
        cout << "  [Custom deleter called for int*]" << endl;
        delete p;
    };
    {
        unique_ptr<int, decltype(customDeleter)> managed(new int(99), customDeleter);
        cout << "  Value: " << *managed << endl;
    }  // custom deleter called here

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread SmartPointers.cpp -o prog
 ================================================================

 === SMART POINTERS (ADVANCED) ===

 --- unique_ptr Factory Pattern ---
   [Connecting to db.server.com:5432]
   Query: SELECT * FROM users LIMIT 10
   Query: SELECT count(*) FROM orders
   [Disconnecting from db.server.com]
 Scope exited — connection properly closed.

 --- unique_ptr in vector ---
   [Connecting to primary.db:5432]
   [Connecting to replica.db:5432]
   [Connecting to cache.db:6379]
   Query: PING
   Query: PING
   Query: PING
   [Disconnecting from primary.db]
   [Disconnecting from replica.db]
   [Disconnecting from cache.db]
 Pool cleared — all connections closed.

 --- shared_ptr Multiple Owners ---
   [Node 'Root' created]
   [Node 'Child' created]
   node2 ref count: 2 (node1 + local)
   After inner scope: node1->next still valid: yes
   node1->next ref count: 1
   [Node 'Root' destroyed]
   [Node 'Child' destroyed]
 Outer scope done — nodes destroyed.

 --- weak_ptr breaks Circular Reference ---
   [Node 'Parent' created]
   [Node 'Child' created]
   parent ref count: 1
   child  ref count: 2
   Child's parent: Parent (value=10)
   [Node 'Parent' destroyed]
   [Node 'Child' destroyed]
 No memory leak — weak_ptr broke the cycle.

 --- Custom Deleter ---
   Value: 99
   [Custom deleter called for int*]

 ================================================================
*/

