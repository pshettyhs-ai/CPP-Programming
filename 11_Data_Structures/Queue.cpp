/*
 * File    : Queue.cpp (custom implementation)
 * Author  : Pavan Shetty H S
 * Topic   : Custom Queue using circular array
 * Date    : Week 12 - Day 3
 */

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T, int MAX = 100>
class CircularQueue {
    T   data[MAX];
    int front_, rear_, count;
public:
    CircularQueue() : front_(0), rear_(-1), count(0) {}

    void enqueue(T val) {
        if (isFull()) throw overflow_error("Queue full!");
        rear_ = (rear_ + 1) % MAX;
        data[rear_] = val;
        count++;
    }

    void dequeue() {
        if (isEmpty()) throw underflow_error("Queue empty!");
        front_ = (front_ + 1) % MAX;
        count--;
    }

    T    front()   const {
        if (isEmpty()) throw underflow_error("Queue empty!");
        return data[front_];
    }
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == MAX; }
    int  size()    const { return count; }

    void display() const {
        cout << "Queue (front→rear): ";
        int idx = front_;
        for (int i = 0; i < count; i++) {
            cout << data[idx] << " ";
            idx = (idx + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== CUSTOM QUEUE ===" << endl;

    CircularQueue<int> q;
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    q.display();
    cout << "Front: " << q.front() << " Size: " << q.size() << endl;

    q.dequeue();
    q.display();

    q.enqueue(40); q.enqueue(50);
    q.display();

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Queue.cpp -o prog
 ================================================================

 === CUSTOM QUEUE ===
 Queue (front→rear): 10 20 30 
 Front: 10 Size: 3
 Queue (front→rear): 20 30 
 Queue (front→rear): 20 30 40 50 

 ================================================================
*/

