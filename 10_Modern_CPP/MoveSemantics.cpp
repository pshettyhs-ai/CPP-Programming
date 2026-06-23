/*
 * File    : MoveSemantics.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Move Semantics and Rvalue References (C++11)
 * Date    : Week 10 - Day 3
 *
 * Notes:
 *   This was one of the harder C++11 concepts to grasp.
 *   The key insight: copy = duplicate the data, move = STEAL the data.
 *   
 *   lvalue: has a name, has a persistent address (int x = 5; → x is lvalue)
 *   rvalue: temporary, no persistent address (int x = 5 + 3; → 5+3 is rvalue)
 *   
 *   Move semantics avoids expensive copies when working with temporaries.
 *   Crucial for performance with large containers.
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>   // std::move
using namespace std;

class Buffer {
public:
    int*   data;
    size_t size;
    string name;

    Buffer(size_t sz, string n) : size(sz), name(n) {
        data = new int[sz];
        for (size_t i = 0; i < sz; i++) data[i] = i;
        cout << "  [Constructed: " << name << " size=" << sz << "]" << endl;
    }

    // Copy constructor — expensive (copies all data)
    Buffer(const Buffer& other) : size(other.size), name(other.name + "_copy") {
        data = new int[size];
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        cout << "  [COPY: " << other.name << " → " << name << " (copying " << size << " ints)]" << endl;
    }

    // Move constructor — cheap (just steals the pointer)
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size), name(other.name + "_moved") {
        other.data = nullptr;
        other.size = 0;
        cout << "  [MOVE: stole data from " << other.name << "]" << endl;
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            name = other.name + "_assigned";
            data = new int[size];
            for (size_t i = 0; i < size; i++) data[i] = other.data[i];
            cout << "  [COPY ASSIGN from " << other.name << "]" << endl;
        }
        return *this;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            name = other.name + "_move_assigned";
            other.data = nullptr;
            other.size = 0;
            cout << "  [MOVE ASSIGN from " << other.name << "]" << endl;
        }
        return *this;
    }

    ~Buffer() {
        if (data) {
            delete[] data;
            cout << "  [Destroyed: " << name << "]" << endl;
        } else {
            cout << "  [Destroyed empty shell: " << name << "]" << endl;
        }
    }

    void show() const {
        cout << "  Buffer[" << name << "] data=" << (data ? "valid" : "null")
             << " size=" << size << endl;
    }
};

Buffer createBuffer(size_t sz) {
    Buffer local(sz, "local");
    return local;  // compiler uses move (or RVO — Return Value Optimisation)
}

int main() {
    cout << "=== MOVE SEMANTICS ===" << endl;

    // Copy vs Move
    cout << "\n--- Copy Construction ---" << endl;
    Buffer b1(100, "B1");
    Buffer b2 = b1;  // copy — expensive
    b1.show(); b2.show();

    cout << "\n--- Move Construction ---" << endl;
    Buffer b3(100, "B3");
    Buffer b4 = move(b3);  // move — cheap, b3 becomes empty shell
    b3.show();  // b3 now empty
    b4.show();

    cout << "\n--- Return Value (Move/RVO) ---" << endl;
    Buffer b5 = createBuffer(50);  // compiler optimizes — no copy!
    b5.show();

    // std::move in practice — moving into vector
    cout << "\n--- Moving into vector ---" << endl;
    vector<Buffer> buffers;
    buffers.reserve(3);
    Buffer temp1(10, "T1");
    Buffer temp2(20, "T2");
    buffers.push_back(move(temp1));  // move temp1 into vector
    buffers.push_back(move(temp2));  // move temp2 into vector
    cout << "temp1 after move: "; temp1.show();  // temp1 is empty now
    cout << "temp2 after move: "; temp2.show();

    cout << "\n--- Cleanup ---" << endl;
    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread MoveSemantics.cpp -o prog
 ================================================================

 === MOVE SEMANTICS ===

 --- Copy Construction ---
   [Constructed: B1 size=100]
   [COPY: B1 → B1_copy (copying 100 ints)]
   Buffer[B1] data=valid size=100
   Buffer[B1_copy] data=valid size=100

 --- Move Construction ---
   [Constructed: B3 size=100]
   [MOVE: stole data from B3]
   Buffer[B3] data=null size=0
   Buffer[B3_moved] data=valid size=100

 --- Return Value (Move/RVO) ---
   [Constructed: local size=50]
   Buffer[local] data=valid size=50

 --- Moving into vector ---
   [Constructed: T1 size=10]
   [Constructed: T2 size=20]
   [MOVE: stole data from T1]
   [MOVE: stole data from T2]
 temp1 after move:   Buffer[T1] data=null size=0
 temp2 after move:   Buffer[T2] data=null size=0

 --- Cleanup ---
   [Destroyed empty shell: T2]
   [Destroyed empty shell: T1]
   [Destroyed: T1_moved]
   [Destroyed: T2_moved]
   [Destroyed: local]
   [Destroyed: B3_moved]
   [Destroyed empty shell: B3]
   [Destroyed: B1_copy]
   [Destroyed: B1]

 ================================================================
*/

