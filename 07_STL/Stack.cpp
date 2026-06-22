/*
 * File    : Stack.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::stack and std::queue
 * Date    : Week 8 - Day 4
 */

#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// Using stack to check balanced brackets
bool isBalanced(string expr) {
    stack<char> st;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            char top = st.top(); st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return st.empty();
}

// Reverse a string using stack
string reverseStr(string s) {
    stack<char> st;
    for (char c : s) st.push(c);
    string result;
    while (!st.empty()) { result += st.top(); st.pop(); }
    return result;
}

int main() {
    cout << "=== STACK AND QUEUE ===" << endl;

    // Stack — LIFO
    cout << "\n--- std::stack ---" << endl;
    stack<int> st;
    st.push(10); st.push(20); st.push(30);
    cout << "Top: " << st.top() << endl;
    cout << "Size: " << st.size() << endl;
    while (!st.empty()) {
        cout << st.top() << " "; st.pop();
    }
    cout << endl;

    // Balanced brackets
    cout << "\n--- Balanced Brackets ---" << endl;
    vector<string> exprs = {"(())", "([{}])", "([)]", "((("};
    for (auto& e : exprs)
        cout << "'" << e << "' → " << (isBalanced(e) ? "Balanced" : "Not balanced") << endl;

    // Reverse string
    cout << "\n--- Reverse String ---" << endl;
    cout << "reverse('hello') = " << reverseStr("hello") << endl;

    // Queue — FIFO
    cout << "\n--- std::queue ---" << endl;
    queue<string> q;
    q.push("First"); q.push("Second"); q.push("Third");
    cout << "Front: " << q.front() << " Back: " << q.back() << endl;
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Stack.cpp -o prog
 ================================================================

 === STACK AND QUEUE ===

 --- std::stack ---
 Top: 30
 Size: 3
 30 20 10 

 --- Balanced Brackets ---
 '(())' → Balanced
 '([{}])' → Balanced
 '([)]' → Not balanced
 '(((' → Not balanced

 --- Reverse String ---
 reverse('hello') = olleh

 --- std::queue ---
 Front: First Back: Third
 First Second Third 

 ================================================================
*/

