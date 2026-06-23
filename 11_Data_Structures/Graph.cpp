/*
 * File    : Graph.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Graph — adjacency list, BFS, DFS
 * Date    : Week 12 - Day 5
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;  // adjacency list
    bool directed;

public:
    Graph(int vertices, bool isDirected = false)
        : V(vertices), adj(vertices), directed(isDirected) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // BFS — Level-order traversal, shortest path in unweighted graph
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << "BFS from " << start << ": ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // DFS — Depth-first traversal (recursive)
    void dfsHelper(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) dfsHelper(neighbor, visited);
        }
    }

    void dfs(int start) {
        vector<bool> visited(V, false);
        cout << "DFS from " << start << ": ";
        dfsHelper(start, visited);
        cout << endl;
    }

    // DFS iterative (using stack)
    void dfsIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);
        cout << "DFS (iter) from " << start << ": ";
        while (!st.empty()) {
            int node = st.top(); st.pop();
            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";
                for (int i = adj[node].size()-1; i >= 0; i--)
                    if (!visited[adj[node][i]]) st.push(adj[node][i]);
            }
        }
        cout << endl;
    }

    // Check if path exists (BFS)
    bool hasPath(int src, int dest) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(src);
        visited[src] = true;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            if (node == dest) return true;
            for (int nb : adj[node])
                if (!visited[nb]) { visited[nb] = true; q.push(nb); }
        }
        return false;
    }

    // Shortest path (BFS on unweighted graph)
    int shortestPath(int src, int dest) {
        vector<int> dist(V, -1);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nb : adj[node]) {
                if (dist[nb] == -1) {
                    dist[nb] = dist[node] + 1;
                    if (nb == dest) return dist[nb];
                    q.push(nb);
                }
            }
        }
        return -1;
    }

    // Count connected components
    int connectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsHelper(i, visited);
                count++;
            }
        }
        return count;
    }

    void display() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < V; i++) {
            cout << "  " << i << " → ";
            for (int nb : adj[i]) cout << nb << " ";
            cout << endl;
        }
    }
};

int main() {
    cout << "=== GRAPH ===" << endl;

    // Undirected graph
    cout << "\n--- Undirected Graph ---" << endl;
    Graph g(7);
    g.addEdge(0, 1); g.addEdge(0, 2);
    g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6);
    g.display();

    g.bfs(0);
    g.dfs(0);
    g.dfsIterative(0);

    cout << "Path 0→6: " << (g.hasPath(0, 6) ? "Yes" : "No") << endl;
    cout << "Shortest path 0→5: " << g.shortestPath(0, 5) << " edges" << endl;

    // Disconnected graph
    cout << "\n--- Connected Components ---" << endl;
    Graph g2(6);
    g2.addEdge(0, 1); g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    // 5 is isolated
    cout << "Connected components: " << g2.connectedComponents() << " (expected 3)" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Graph.cpp -o prog
 ================================================================

 === GRAPH ===

 --- Undirected Graph ---
 Adjacency List:
   0 → 1 2 
   1 → 0 3 4 
   2 → 0 5 6 
   3 → 1 
   4 → 1 
   5 → 2 
   6 → 2 
 BFS from 0: 0 1 2 3 4 5 6 
 DFS from 0: 0 1 3 4 2 5 6 
 DFS (iter) from 0: 0 1 3 4 2 5 6 
 Path 0→6: Yes
 Shortest path 0→5: 2 edges

 --- Connected Components ---
 Connected components: 0 1 2 3 4 5 3 (expected 3)

 ================================================================
*/

