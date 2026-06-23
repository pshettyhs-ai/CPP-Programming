/*
 * File    : DFS.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Depth-First Search — cycle detection, topological sort
 * Date    : Week 13 - Day 6
 *
 * Notes:
 *   DFS goes as deep as possible before backtracking.
 *   Uses a stack (either explicit or the call stack via recursion).
 *
 *   Applications:
 *   - Cycle detection
 *   - Topological sorting
 *   - Finding all paths
 *   - Maze solving
 *
 *   Time:  O(V + E)
 *   Space: O(V) recursion stack
 */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

class DFSGraph {
    int V;
    vector<vector<int>> adj;
    bool directed;

public:
    DFSGraph(int v, bool dir = false) : V(v), adj(v), directed(dir) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // Recursive DFS
    void dfsRec(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (int nb : adj[node])
            if (!visited[nb]) dfsRec(nb, visited);
    }

    void dfs(int start) {
        vector<bool> visited(V, false);
        cout << "DFS from " << start << ": ";
        dfsRec(start, visited);
        cout << endl;
    }

    // Cycle detection in undirected graph
    bool hasCycleUndirected(int node, vector<bool>& visited, int parent) {
        visited[node] = true;
        for (int nb : adj[node]) {
            if (!visited[nb]) {
                if (hasCycleUndirected(nb, visited, node)) return true;
            } else if (nb != parent) {
                return true;   // back edge — cycle!
            }
        }
        return false;
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
            if (!visited[i] && hasCycleUndirected(i, visited, -1))
                return true;
        return false;
    }

    // Topological sort (for directed acyclic graphs — DAG)
    void topoHelper(int node, vector<bool>& visited, stack<int>& st) {
        visited[node] = true;
        for (int nb : adj[node])
            if (!visited[nb]) topoHelper(nb, visited, st);
        st.push(node);   // push after all descendants processed
    }

    void topologicalSort() {
        vector<bool> visited(V, false);
        stack<int>   st;
        for (int i = 0; i < V; i++)
            if (!visited[i]) topoHelper(i, visited, st);

        cout << "Topological order: ";
        while (!st.empty()) { cout << st.top() << " "; st.pop(); }
        cout << endl;
    }

    // Find all paths from src to dest
    void findAllPaths(int src, int dest, vector<int>& path, vector<bool>& visited,
                      vector<vector<int>>& allPaths) {
        visited[src] = true;
        path.push_back(src);
        if (src == dest) {
            allPaths.push_back(path);
        } else {
            for (int nb : adj[src])
                if (!visited[nb])
                    findAllPaths(nb, dest, path, visited, allPaths);
        }
        path.pop_back();
        visited[src] = false;   // backtrack
    }

    void printAllPaths(int src, int dest) {
        vector<int>          path;
        vector<bool>         visited(V, false);
        vector<vector<int>>  allPaths;
        findAllPaths(src, dest, path, visited, allPaths);

        cout << "All paths " << src << "→" << dest << ":" << endl;
        for (auto& p : allPaths) {
            cout << "  ";
            for (int node : p) cout << node << " ";
            cout << endl;
        }
    }
};

int main() {
    cout << "=== DFS (Depth-First Search) ===" << endl;

    // Undirected graph
    cout << "\n--- Undirected Graph ---" << endl;
    DFSGraph ug(6);
    ug.addEdge(0, 1); ug.addEdge(0, 2);
    ug.addEdge(1, 3); ug.addEdge(1, 4);
    ug.addEdge(2, 5);
    ug.dfs(0);
    cout << "Has cycle: " << (ug.hasCycle() ? "Yes" : "No") << endl;

    // Graph with cycle
    DFSGraph cyc(4);
    cyc.addEdge(0, 1); cyc.addEdge(1, 2);
    cyc.addEdge(2, 3); cyc.addEdge(3, 1);  // cycle!
    cout << "Cycle graph has cycle: " << (cyc.hasCycle() ? "Yes" : "No") << endl;

    // Directed graph — topological sort
    cout << "\n--- Topological Sort (Build order) ---" << endl;
    DFSGraph dag(6, true);  // directed
    // Dependencies: 5→2, 5→0, 4→0, 4→1, 2→3, 3→1
    dag.addEdge(5, 2); dag.addEdge(5, 0);
    dag.addEdge(4, 0); dag.addEdge(4, 1);
    dag.addEdge(2, 3); dag.addEdge(3, 1);
    dag.topologicalSort();

    // All paths
    cout << "\n--- All Paths ---" << endl;
    DFSGraph pg(5);
    pg.addEdge(0, 1); pg.addEdge(0, 2);
    pg.addEdge(1, 3); pg.addEdge(2, 3);
    pg.addEdge(3, 4); pg.addEdge(1, 4);
    pg.printAllPaths(0, 4);

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread DFS.cpp -o prog
 ================================================================

 === DFS (Depth-First Search) ===

 --- Undirected Graph ---
 DFS from 0: 0 1 3 4 2 5 
 Has cycle: No
 Cycle graph has cycle: Yes

 --- Topological Sort (Build order) ---
 Topological order: 5 4 2 3 1 0 

 --- All Paths ---
 All paths 0→4:
   0 1 3 4 
   0 1 4 
   0 2 3 1 4 
   0 2 3 4 

 ================================================================
*/

