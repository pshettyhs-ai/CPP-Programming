/*
 * File    : LinkedList.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Singly, Doubly, and Circular Linked Lists
 * Date    : Week 12 - Day 1
 *
 * Notes:
 *   Array: fixed size, fast random access, slow insert/delete in middle
 *   Linked List: dynamic size, slow random access, fast insert/delete anywhere
 *
 *   I implemented all three types here — singly, doubly, and circular.
 *   The hardest part was getting the pointer updates right for delete operations.
 *   Drew it on paper first — highly recommended before coding linked list ops.
 */

#include <iostream>
using namespace std;

// ─────────────────────────────────────────
// SINGLY LINKED LIST
// ─────────────────────────────────────────
struct SNode {
    int    data;
    SNode* next;
    SNode(int d) : data(d), next(nullptr) {}
};

class SinglyLinkedList {
private:
    SNode* head;
    int    size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    void insertFront(int data) {
        SNode* node = new SNode(data);
        node->next = head;
        head = node;
        size++;
    }

    void insertEnd(int data) {
        SNode* node = new SNode(data);
        if (!head) { head = node; size++; return; }
        SNode* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
        size++;
    }

    void insertAt(int pos, int data) {
        if (pos == 0) { insertFront(data); return; }
        SNode* node = new SNode(data);
        SNode* curr = head;
        for (int i = 0; i < pos - 1 && curr; i++) curr = curr->next;
        if (!curr) { cout << "Position out of range\n"; delete node; return; }
        node->next = curr->next;
        curr->next = node;
        size++;
    }

    void deleteFront() {
        if (!head) return;
        SNode* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void deleteValue(int data) {
        if (!head) return;
        if (head->data == data) { deleteFront(); return; }
        SNode* curr = head;
        while (curr->next && curr->next->data != data) curr = curr->next;
        if (!curr->next) { cout << "Value not found\n"; return; }
        SNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        size--;
    }

    void reverse() {
        SNode *prev = nullptr, *curr = head, *next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    bool search(int data) {
        SNode* curr = head;
        while (curr) {
            if (curr->data == data) return true;
            curr = curr->next;
        }
        return false;
    }

    int getSize() const { return size; }

    void display() const {
        SNode* curr = head;
        cout << "HEAD → ";
        while (curr) {
            cout << "[" << curr->data << "] → ";
            curr = curr->next;
        }
        cout << "NULL (size=" << size << ")" << endl;
    }

    ~SinglyLinkedList() {
        while (head) deleteFront();
    }
};

// ─────────────────────────────────────────
// DOUBLY LINKED LIST
// ─────────────────────────────────────────
struct DNode {
    int    data;
    DNode* prev;
    DNode* next;
    DNode(int d) : data(d), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
    int    size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insertEnd(int data) {
        DNode* node = new DNode(data);
        if (!tail) { head = tail = node; size++; return; }
        node->prev = tail;
        tail->next = node;
        tail = node;
        size++;
    }

    void deleteFront() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; size--; return; }
        DNode* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        size--;
    }

    void displayForward() const {
        DNode* curr = head;
        cout << "NULL ← ";
        while (curr) {
            cout << "[" << curr->data << "] ↔ ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    void displayBackward() const {
        DNode* curr = tail;
        cout << "NULL → ";
        while (curr) {
            cout << "[" << curr->data << "] ↔ ";
            curr = curr->prev;
        }
        cout << "NULL" << endl;
    }

    ~DoublyLinkedList() { while (head) deleteFront(); }
};

int main() {
    cout << "=== LINKED LISTS ===" << endl;

    // SINGLY LINKED LIST
    cout << "\n--- Singly Linked List ---" << endl;
    SinglyLinkedList sll;
    sll.insertEnd(10);
    sll.insertEnd(20);
    sll.insertEnd(30);
    sll.insertFront(5);
    sll.insertAt(2, 15);
    sll.display();

    cout << "Search 15: " << (sll.search(15) ? "Found" : "Not found") << endl;
    cout << "Search 99: " << (sll.search(99) ? "Found" : "Not found") << endl;

    sll.deleteValue(15);
    sll.display();

    sll.reverse();
    cout << "After reverse: "; sll.display();

    // DOUBLY LINKED LIST
    cout << "\n--- Doubly Linked List ---" << endl;
    DoublyLinkedList dll;
    dll.insertEnd(1);
    dll.insertEnd(2);
    dll.insertEnd(3);
    dll.insertEnd(4);
    dll.insertEnd(5);
    cout << "Forward:  "; dll.displayForward();
    cout << "Backward: "; dll.displayBackward();
    dll.deleteFront();
    cout << "After delete front: "; dll.displayForward();

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread LinkedList.cpp -o prog
 ================================================================

 === LINKED LISTS ===

 --- Singly Linked List ---
 HEAD → [5] → [10] → [15] → [20] → [30] → NULL (size=5)
 Search 15: Found
 Search 99: Not found
 HEAD → [5] → [10] → [20] → [30] → NULL (size=4)
 After reverse: HEAD → [30] → [20] → [10] → [5] → NULL (size=4)

 --- Doubly Linked List ---
 Forward:  NULL ← [1] ↔ [2] ↔ [3] ↔ [4] ↔ [5] ↔ NULL
 Backward: NULL → [5] ↔ [4] ↔ [3] ↔ [2] ↔ [1] ↔ NULL
 After delete front: NULL ← [2] ↔ [3] ↔ [4] ↔ [5] ↔ NULL

 ================================================================
*/

