/*
 * File    : Stack.cpp (custom implementation)
 * Author  : Pavan Shetty H S
 * Topic   : Custom Stack implementation using array and linked list
 * Date    : Week 12 - Day 2
 */

#include <iostream>
#include <stdexcept>
using namespace std;

// Stack using array
template<typename T, int MAX = 100>
class ArrayStack {
    T   data[MAX];
    int top_;
public:
    ArrayStack() : top_(-1) {}

    void push(T val) {
        if (top_ >= MAX - 1) throw overflow_error("Stack overflow!");
        data[++top_] = val;
    }
    void pop() {
        if (isEmpty()) throw underflow_error("Stack underflow!");
        top_--;
    }
    T    peek()    const {
        if (isEmpty()) throw underflow_error("Stack empty!");
        return data[top_];
    }
    bool isEmpty() const { return top_ == -1; }
    int  size()    const { return top_ + 1; }

    void display() const {
        cout << "Stack (top→bottom): ";
        for (int i = top_; i >= 0; i--) cout << data[i] << " ";
        cout << endl;
    }
};

// Applications
void reverseArray(int arr[], int n) {
    ArrayStack<int> st;
    for (int i = 0; i < n; i++) st.push(arr[i]);
    for (int i = 0; i < n; i++) { arr[i] = st.peek(); st.pop(); }
}

int main() {
    cout << "=== CUSTOM STACK ===" << endl;

    ArrayStack<int> st;
    st.push(10); st.push(20); st.push(30); st.push(40);
    st.display();
    cout << "Top: " << st.peek() << " Size: " << st.size() << endl;
    st.pop();
    st.display();

    // Reverse array using stack
    int arr[] = {1, 2, 3, 4, 5};
    reverseArray(arr, 5);
    cout << "Reversed array: ";
    for (int x : arr) cout << x << " "; cout << endl;

    // Exception handling
    try {
        ArrayStack<int> empty;
        empty.pop();
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Stack.cpp -o prog
 ================================================================

 === CUSTOM STACK ===
 Stack (top→bottom): 40 30 20 10 
 Top: 40 Size: 4
 Stack (top→bottom): 30 20 10 
 Reversed array: 5 4 3 2 1 
 Exception: Stack underflow!

 ================================================================
*/

