/*
 * File    : Queue.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::queue and std::priority_queue
 * Date    : Week 8 - Day 4
 */

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// BFS example using queue
void bfs(vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << "BFS from " << start << ": ";
    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << node << " ";
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "=== QUEUE AND PRIORITY QUEUE ===" << endl;

    // priority_queue — max heap by default
    cout << "\n--- priority_queue (max-heap) ---" << endl;
    priority_queue<int> maxPQ;
    for (int x : {5, 2, 8, 1, 9, 3}) maxPQ.push(x);
    cout << "Extracting in descending order: ";
    while (!maxPQ.empty()) { cout << maxPQ.top() << " "; maxPQ.pop(); }
    cout << endl;

    // min-heap
    cout << "\n--- priority_queue (min-heap) ---" << endl;
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : {5, 2, 8, 1, 9, 3}) minPQ.push(x);
    cout << "Extracting in ascending order: ";
    while (!minPQ.empty()) { cout << minPQ.top() << " "; minPQ.pop(); }
    cout << endl;

    // BFS using queue
    cout << "\n--- BFS using queue ---" << endl;
    vector<vector<int>> graph = {{1,2},{0,3,4},{0,5},{1},{1},{2}};
    bfs(graph, 0);

    // Task priority queue (custom comparator)
    cout << "\n--- Task Scheduler ---" << endl;
    using Task = pair<int, string>;  // priority, name
    priority_queue<Task> taskQ;
    taskQ.push({3, "Send email"});
    taskQ.push({9, "Fix critical bug"});
    taskQ.push({5, "Write tests"});
    taskQ.push({7, "Code review"});

    cout << "Tasks in priority order:" << endl;
    while (!taskQ.empty()) {
        auto [pri, name] = taskQ.top(); taskQ.pop();
        cout << "  [P" << pri << "] " << name << endl;
    }

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Queue.cpp -o prog
 ================================================================

 === QUEUE AND PRIORITY QUEUE ===

 --- priority_queue (max-heap) ---
 Extracting in descending order: 9 8 5 3 2 1 

 --- priority_queue (min-heap) ---
 Extracting in ascending order: 1 2 3 5 8 9 

 --- BFS using queue ---
 BFS from 0: 0 1 2 3 4 5 

 --- Task Scheduler ---
 Tasks in priority order:
   [P9] Fix critical bug
   [P7] Code review
   [P5] Write tests
   [P3] Send email

 ================================================================
*/

