/*
 * File    : BFS.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Breadth-First Search — shortest path, level-order traversal
 * Date    : Week 13 - Day 5
 *
 * Notes:
 *   BFS explores level by level using a queue.
 *   Guarantees shortest path in UNWEIGHTED graphs.
 *   For weighted graphs, use Dijkstra's algorithm.
 *
 *   Time:  O(V + E) — visits each vertex and edge once
 *   Space: O(V)     — queue can hold all vertices in worst case
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // undirected
    }

    // Standard BFS traversal
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS traversal from " << start << ": ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";
            for (int nb : adj[node]) {
                if (!visited[nb]) {
                    visited[nb] = true;
                    q.push(nb);
                }
            }
        }
        cout << endl;
    }

    // Shortest path using BFS
    vector<int> shortestPath(int src, int dest) {
        vector<int>  dist(V, -1);
        vector<int>  parent(V, -1);
        queue<int>   q;

        dist[src] = 0;
        q.push(src);

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nb : adj[node]) {
                if (dist[nb] == -1) {
                    dist[nb]   = dist[node] + 1;
                    parent[nb] = node;
                    q.push(nb);
                    if (nb == dest) goto found;
                }
            }
        }
        return {};  // no path

        found:
        // Reconstruct path
        vector<int> path;
        for (int cur = dest; cur != -1; cur = parent[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        return path;
    }

    // BFS level by level
    void levelOrder(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            cout << "Level " << level << ": ";
            for (int i = 0; i < size; i++) {
                int node = q.front(); q.pop();
                cout << node << " ";
                for (int nb : adj[node]) {
                    if (!visited[nb]) {
                        visited[nb] = true;
                        q.push(nb);
                    }
                }
            }
            cout << endl;
            level++;
        }
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int count = 1;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nb : adj[node]) {
                if (!visited[nb]) {
                    visited[nb] = true;
                    q.push(nb);
                    count++;
                }
            }
        }
        return count == V;
    }
};

int main() {
    cout << "=== BFS (Breadth-First Search) ===" << endl;

    Graph g(8);
    g.addEdge(0, 1); g.addEdge(0, 2);
    g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6);
    g.addEdge(3, 7);

    cout << "\nGraph:" << endl;
    cout << "        0" << endl;
    cout << "       / \\" << endl;
    cout << "      1   2" << endl;
    cout << "     / \\ / \\" << endl;
    cout << "    3  4 5  6" << endl;
    cout << "    |" << endl;
    cout << "    7" << endl;

    cout << "\n--- BFS Traversal ---" << endl;
    g.bfs(0);

    cout << "\n--- Level-Order ---" << endl;
    g.levelOrder(0);

    cout << "\n--- Shortest Paths ---" << endl;
    auto path = g.shortestPath(0, 7);
    cout << "Path 0→7: ";
    for (int n : path) cout << n << " ";
    cout << "(length: " << path.size()-1 << " edges)" << endl;

    path = g.shortestPath(3, 6);
    cout << "Path 3→6: ";
    for (int n : path) cout << n << " ";
    cout << "(length: " << path.size()-1 << " edges)" << endl;

    cout << "\nGraph connected: " << (g.isConnected() ? "Yes" : "No") << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread BFS.cpp -o prog
 ================================================================

 === BFS (Breadth-First Search) ===

 Graph:
         0
        / \
       1   2
      / \ / \
     3  4 5  6
     |
     7

 --- BFS Traversal ---
 BFS traversal from 0: 0 1 2 3 4 5 6 7 

 --- Level-Order ---
 Level 0: 0 
 Level 1: 1 2 
 Level 2: 3 4 5 6 
 Level 3: 7 

 --- Shortest Paths ---
 Path 0→7: 0 1 3 7 (length: 3 edges)
 Path 3→6: 3 1 0 2 6 (length: 4 edges)

 Graph connected: Yes

 ================================================================
*/

