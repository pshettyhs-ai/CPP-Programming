/*
 * File    : Map.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::map and std::unordered_map
 * Date    : Week 8 - Day 3
 *
 * Notes:
 *   map: key-value pairs, sorted by key, O(log n) operations (Red-Black Tree)
 *   unordered_map: key-value, unsorted, O(1) average (Hash Table)
 *
 *   When to use which:
 *   - Need sorted keys? → map
 *   - Just need fast lookup? → unordered_map
 *   - Need to iterate in order? → map
 */

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

int main() {
    cout << "=== std::map ===" << endl;

    // ── Basic map usage ───────────────────
    cout << "\n--- map (sorted) ---" << endl;
    map<string, int> studentMarks;

    // Insert methods
    studentMarks["Pavan"]  = 92;
    studentMarks["Rahul"]  = 85;
    studentMarks["Priya"]  = 97;
    studentMarks["Arjun"]  = 78;
    studentMarks.insert({"Kiran", 88});
    studentMarks.emplace("Sneha", 91);

    // Iteration — always sorted by key (alphabetical for strings)
    cout << "Student marks (sorted by name):" << endl;
    for (auto& [name, marks] : studentMarks) {  // structured bindings (C++17)
        cout << "  " << name << ": " << marks << endl;
    }

    // Access
    cout << "\nPavan's marks: " << studentMarks["Pavan"] << endl;
    cout << "Rahul's marks: " << studentMarks.at("Rahul") << endl;

    // Check existence
    if (studentMarks.count("Priya") > 0)
        cout << "Priya is in the map." << endl;
    if (studentMarks.find("Unknown") == studentMarks.end())
        cout << "Unknown is NOT in the map." << endl;

    // Erase
    studentMarks.erase("Arjun");
    cout << "Size after erase: " << studentMarks.size() << endl;

    // ── Frequency counter (common use) ────
    cout << "\n--- Word Frequency Counter ---" << endl;
    string text = "the quick brown fox jumps over the lazy dog the fox";
    map<string, int> wordCount;
    string word;
    for (size_t i = 0, j; i <= text.size(); i = j + 1) {
        j = text.find(' ', i);
        if (j == string::npos) j = text.size();
        word = text.substr(i, j - i);
        if (!word.empty()) wordCount[word]++;
    }
    for (auto& [w, cnt] : wordCount)
        cout << "  '" << w << "': " << cnt << endl;

    // ── unordered_map (faster lookup) ─────
    cout << "\n--- unordered_map ---" << endl;
    unordered_map<string, string> capitals;
    capitals["India"]  = "New Delhi";
    capitals["Japan"]  = "Tokyo";
    capitals["France"] = "Paris";
    capitals["USA"]    = "Washington D.C.";

    cout << "Capital of India: " << capitals["India"] << endl;
    cout << "Capital of Japan: " << capitals.at("Japan") << endl;

    // unordered — no guaranteed iteration order
    cout << "All capitals (no guaranteed order):" << endl;
    for (auto& [country, capital] : capitals)
        cout << "  " << country << " → " << capital << endl;

    // ── map of vectors ────────────────────
    cout << "\n--- Map of Vectors ---" << endl;
    map<string, vector<int>> scores;
    scores["Math"]    = {95, 88, 92, 87};
    scores["Physics"] = {78, 82, 90, 85};
    scores["CS"]      = {97, 99, 94, 96};

    for (auto& [subject, marks] : scores) {
        int total = 0;
        for (int m : marks) total += m;
        cout << "  " << subject << " avg: " << (double)total/marks.size() << endl;
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Map.cpp -o prog
 ================================================================

 === std::map ===

 --- map (sorted) ---
 Student marks (sorted by name):
   Arjun: 78
   Kiran: 88
   Pavan: 92
   Priya: 97
   Rahul: 85
   Sneha: 91

 Pavan's marks: 92
 Rahul's marks: 85
 Priya is in the map.
 Unknown is NOT in the map.
 Size after erase: 5

 --- Word Frequency Counter ---
   'brown': 1
   'dog': 1
   'fox': 2
   'jumps': 1
   'lazy': 1
   'over': 1
   'quick': 1
   'the': 3

 --- unordered_map ---
 Capital of India: New Delhi
 Capital of Japan: Tokyo
 All capitals (no guaranteed order):
   USA → Washington D.C.
   France → Paris
   Japan → Tokyo
   India → New Delhi

 --- Map of Vectors ---
   CS avg: 96.5
   Math avg: 90.5
   Physics avg: 83.75

 ================================================================
*/

