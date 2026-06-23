/*
 * File    : SmartPointers.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Smart Pointers — unique_ptr, shared_ptr, weak_ptr
 * Date    : Week 4 - Day 3
 *
 * Notes:
 *   Smart pointers are RAII wrappers around raw pointers.
 *   They automatically delete the memory when they go out of scope.
 *   This eliminates most memory leaks and double-delete bugs.
 *
 *   Rule of thumb (as I learnt it):
 *   - unique_ptr: one owner, not shared. Default choice.
 *   - shared_ptr: multiple owners. Use only when needed.
 *   - weak_ptr: non-owning observer. Break circular references.
 */

#include <iostream>
#include <memory>   // for smart pointers
#include <string>
using namespace std;

class Resource {
public:
    string name;
    Resource(string n) : name(n) {
        cout << "  [Resource '" << name << "' created]" << endl;
    }
    ~Resource() {
        cout << "  [Resource '" << name << "' destroyed automatically!]" << endl;
    }
    void use() { cout << "  Using resource: " << name << endl; }
};

int main() {
    cout << "=== SMART POINTERS ===" << endl;

    // ─────────────────────────────────────────
    // unique_ptr — sole owner
    // ─────────────────────────────────────────
    cout << "\n--- unique_ptr ---" << endl;
    {
        unique_ptr<Resource> uptr = make_unique<Resource>("FileHandler");
        uptr->use();
        cout << "  unique_ptr in scope..." << endl;
    }   // uptr goes out of scope → Resource auto-destroyed here!
    cout << "After scope — resource already freed." << endl;

    // Cannot copy unique_ptr, only move
    unique_ptr<int> up1 = make_unique<int>(42);
    cout << "up1 = " << *up1 << endl;
    unique_ptr<int> up2 = move(up1);  // transfer ownership
    cout << "After move: up2 = " << *up2 << endl;
    cout << "up1 is now " << (up1 ? "valid" : "null") << endl;

    // ─────────────────────────────────────────
    // shared_ptr — shared ownership
    // ─────────────────────────────────────────
    cout << "\n--- shared_ptr ---" << endl;
    {
        shared_ptr<Resource> sp1 = make_shared<Resource>("SharedConfig");
        cout << "  sp1 ref count: " << sp1.use_count() << endl;
        {
            shared_ptr<Resource> sp2 = sp1;   // copy — both own the resource
            cout << "  sp2 created, ref count: " << sp1.use_count() << endl;
            sp2->use();
        }
        cout << "  sp2 gone, ref count: " << sp1.use_count() << endl;
    }
    // Resource destroyed when last shared_ptr (sp1) goes out of scope

    // ─────────────────────────────────────────
    // weak_ptr — non-owning observer
    // ─────────────────────────────────────────
    cout << "\n--- weak_ptr ---" << endl;
    shared_ptr<Resource> sp = make_shared<Resource>("ObservedResource");
    weak_ptr<Resource>   wp = sp;  // weak reference — doesn't affect ref count

    cout << "  sp ref count: " << sp.use_count() << " (weak_ptr doesn't count)" << endl;

    // Must lock() weak_ptr before using it
    if (auto locked = wp.lock()) {
        locked->use();
        cout << "  Locked and used via weak_ptr" << endl;
    }

    sp.reset();  // release the shared_ptr
    cout << "  sp released. Is weak_ptr expired? " << (wp.expired() ? "yes" : "no") << endl;

    cout << "\n=== Smart pointer demo complete ===" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread SmartPointers.cpp -o prog
 ================================================================

 === SMART POINTERS ===

 --- unique_ptr ---
   [Resource 'FileHandler' created]
   Using resource: FileHandler
   unique_ptr in scope...
   [Resource 'FileHandler' destroyed automatically!]
 After scope — resource already freed.
 up1 = 42
 After move: up2 = 42
 up1 is now null

 --- shared_ptr ---
   [Resource 'SharedConfig' created]
   sp1 ref count: 1
   sp2 created, ref count: 2
   Using resource: SharedConfig
   sp2 gone, ref count: 1
   [Resource 'SharedConfig' destroyed automatically!]

 --- weak_ptr ---
   [Resource 'ObservedResource' created]
   sp ref count: 1 (weak_ptr doesn't count)
   Using resource: ObservedResource
   Locked and used via weak_ptr
   [Resource 'ObservedResource' destroyed automatically!]
   sp released. Is weak_ptr expired? yes

 === Smart pointer demo complete ===

 ================================================================
*/

