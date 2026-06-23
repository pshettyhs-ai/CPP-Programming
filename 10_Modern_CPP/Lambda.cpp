/*
 * File    : Lambda.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Lambda Expressions (C++11)
 * Date    : Week 10 - Day 1
 *
 * Notes:
 *   Lambda = anonymous function defined inline where it's used.
 *   Syntax: [capture](params) -> return_type { body }
 *
 *   Before lambdas I had to write separate functions or function objects
 *   for things like custom sort comparators. Lambdas make this much cleaner.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int main() {
    cout << "=== LAMBDA EXPRESSIONS ===" << endl;

    // 1. Basic lambda
    auto greet = []() {
        cout << "Hello from a lambda!" << endl;
    };
    greet();  // call it

    // 2. Lambda with parameters
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "add(3, 7) = " << add(3, 7) << endl;

    // 3. Capture by value [=]
    int multiplier = 5;
    auto multiplyByVal = [multiplier](int x) { return x * multiplier; };
    multiplier = 100;  // changing multiplier AFTER capture
    cout << "multiplyByVal(4) = " << multiplyByVal(4) << " (captured 5, not 100)" << endl;

    // 4. Capture by reference [&]
    int total = 0;
    auto addToTotal = [&total](int x) { total += x; };
    addToTotal(10); addToTotal(20); addToTotal(30);
    cout << "total after additions = " << total << endl;

    // 5. Capture all by value [=] or by reference [&]
    int a = 10, b = 20;
    auto sumAll = [=]() { return a + b; };  // captures a and b by value
    cout << "sumAll() = " << sumAll() << endl;

    // 6. Lambda with STL algorithms
    cout << "\n--- Lambdas with STL ---" << endl;
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // Custom sort
    sort(nums.begin(), nums.end(), [](int a, int b){ return a > b; });
    cout << "Sorted descending: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    // Count elements matching condition
    int target = 5;
    int cnt = count_if(nums.begin(), nums.end(), [target](int x){ return x == target; });
    cout << "Count of " << target << ": " << cnt << endl;

    // Filter using remove_if
    nums.erase(remove_if(nums.begin(), nums.end(), [](int x){ return x % 2 == 0; }), nums.end());
    cout << "Odds only: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    // 7. Storing lambdas in std::function
    cout << "\n--- std::function ---" << endl;
    function<int(int, int)> operation;
    char op = '+';
    switch(op) {
        case '+': operation = [](int a, int b){ return a + b; }; break;
        case '-': operation = [](int a, int b){ return a - b; }; break;
        case '*': operation = [](int a, int b){ return a * b; }; break;
    }
    cout << "10 " << op << " 3 = " << operation(10, 3) << endl;

    // 8. Immediately Invoked Lambda
    cout << "\n--- Immediately Invoked ---" << endl;
    int result = [](int x, int y){ return x * x + y * y; }(3, 4);
    cout << "3² + 4² = " << result << endl;

    // 9. Recursive lambda (needs std::function)
    cout << "\n--- Recursive Lambda ---" << endl;
    function<int(int)> fact = [&fact](int n) -> int {
        return n <= 1 ? 1 : n * fact(n - 1);
    };
    cout << "fact(6) = " << fact(6) << endl;

    // 10. Lambda returning lambda (higher-order)
    cout << "\n--- Lambda returning Lambda ---" << endl;
    auto makeAdder = [](int offset) {
        return [offset](int x) { return x + offset; };
    };
    auto add10 = makeAdder(10);
    auto add100 = makeAdder(100);
    cout << "add10(5)  = " << add10(5)  << endl;
    cout << "add100(5) = " << add100(5) << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Lambda.cpp -o prog
 ================================================================

 === LAMBDA EXPRESSIONS ===
 Hello from a lambda!
 add(3, 7) = 10
 multiplyByVal(4) = 20 (captured 5, not 100)
 total after additions = 60
 sumAll() = 30

 --- Lambdas with STL ---
 Sorted descending: 9 6 5 5 5 4 3 3 2 1 1 
 Count of 5: 3
 Odds only: 9 5 5 5 3 3 1 1 

 --- std::function ---
 10 + 3 = 13

 --- Immediately Invoked ---
 3² + 4² = 25

 --- Recursive Lambda ---
 fact(6) = 720

 --- Lambda returning Lambda ---
 add10(5)  = 15
 add100(5) = 105

 ================================================================
*/

