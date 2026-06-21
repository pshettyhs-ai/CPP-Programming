/*
 * File    : Strings.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::string — operations, methods, algorithms
 * Date    : Week 4 - Day 1
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int main() {
    cout << "=== STRINGS IN C++ ===" << endl;

    string s1 = "Hello";
    string s2 = " World";
    string s3 = s1 + s2;   // concatenation
    cout << s3 << endl;

    // Length, access
    cout << "Length: " << s3.length() << endl;
    cout << "First char: " << s3[0] << endl;
    cout << "Last char:  " << s3.back() << endl;

    // Substrings
    cout << "Substr(0,5): " << s3.substr(0, 5) << endl;

    // Find
    size_t pos = s3.find("World");
    if (pos != string::npos)
        cout << "'World' found at index: " << pos << endl;

    // Replace
    string s4 = s3;
    s4.replace(6, 5, "C++");
    cout << "After replace: " << s4 << endl;

    // Case conversion
    string upper = s3;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << "Uppercase: " << upper << endl;

    // Split string (using stringstream)
    string csv = "Pavan,Rahul,Priya,Arjun";
    stringstream ss(csv);
    string token;
    cout << "CSV split: ";
    while (getline(ss, token, ',')) cout << "[" << token << "] ";
    cout << endl;

    // Check palindrome
    auto isPalindrome = [](string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        return s == rev;
    };
    cout << "racecar palindrome? " << (isPalindrome("racecar") ? "yes" : "no") << endl;
    cout << "hello palindrome?   " << (isPalindrome("hello")   ? "yes" : "no") << endl;

    // String to number and back
    int    num = stoi("42");
    double dbl = stod("3.14");
    string str = to_string(12345);
    cout << "stoi: " << num << " stod: " << dbl << " to_string: " << str << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Strings.cpp -o prog
 ================================================================

 === STRINGS IN C++ ===
 Hello World
 Length: 11
 First char: H
 Last char:  d
 Substr(0,5): Hello
 'World' found at index: 6
 After replace: Hello C++
 Uppercase: HELLO WORLD
 CSV split: [Pavan] [Rahul] [Priya] [Arjun] 
 racecar palindrome? yes
 hello palindrome?   no
 stoi: 42 stod: 3.14 to_string: 12345

 ================================================================
*/

