/*
 * File    : Tree.cpp
 * Author  : Pavan Shetty H S
 * Topic   : Binary Tree and Binary Search Tree
 * Date    : Week 12 - Day 3
 *
 * Notes:
 *   Tree = hierarchical data structure with nodes and edges.
 *   BST property: left < root < right at every node.
 *   
 *   Traversals:
 *   - Inorder (LNR)   → gives sorted output for BST
 *   - Preorder (NLR)  → useful for copying a tree
 *   - Postorder (LRN) → useful for deleting a tree
 */

#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int       data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int data) {
        if (!node) return new TreeNode(data);
        if (data < node->data) node->left  = insert(node->left,  data);
        else if (data > node->data) node->right = insert(node->right, data);
        return node;  // if data == node->data, no duplicate
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(TreeNode* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(TreeNode* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int height(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    bool search(TreeNode* node, int data) {
        if (!node) return false;
        if (data == node->data) return true;
        if (data < node->data) return search(node->left, data);
        return search(node->right, data);
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int data) {
        if (!node) return nullptr;
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            // Node found — 3 cases
            if (!node->left)  { TreeNode* r = node->right; delete node; return r; }
            if (!node->right) { TreeNode* l = node->left;  delete node; return l; }
            // Node has 2 children: replace with inorder successor
            TreeNode* successor = findMin(node->right);
            node->data  = successor->data;
            node->right = deleteNode(node->right, successor->data);
        }
        return node;
    }

    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int data)    { root = insert(root, data); }
    void remove(int data)    { root = deleteNode(root, data); }
    bool search(int data)    { return search(root, data); }
    int  height()            { return height(root); }
    void inorder()           { inorder(root); cout << endl; }
    void preorder()          { preorder(root); cout << endl; }
    void postorder()         { postorder(root); cout << endl; }

    void levelOrder() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = q.front(); q.pop();
                cout << curr->data << " ";
                if (curr->left)  q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== BINARY SEARCH TREE ===" << endl;

    BST tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int v : values) tree.insert(v);

    cout << "\nInorder   (sorted): "; tree.inorder();
    cout << "Preorder           : "; tree.preorder();
    cout << "Postorder          : "; tree.postorder();
    cout << "Tree height        : " << tree.height() << endl;

    cout << "\nLevel-order (BFS):" << endl;
    tree.levelOrder();

    cout << "\nSearch 40 : " << (tree.search(40)  ? "Found" : "Not found") << endl;
    cout << "Search 99  : " << (tree.search(99)  ? "Found" : "Not found") << endl;

    tree.remove(30);
    cout << "\nAfter removing 30 — Inorder: "; tree.inorder();

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Tree.cpp -o prog
 ================================================================

 === BINARY SEARCH TREE ===

 Inorder   (sorted): 10 20 25 30 35 40 45 50 60 70 80 
 Preorder           : 50 30 20 10 25 40 35 45 70 60 80 
 Postorder          : 10 25 20 35 45 40 30 60 80 70 50 
 Tree height        : 4

 Level-order (BFS):
 50 
 30 70 
 20 40 60 80 
 10 25 35 45 

 Search 40 : Found
 Search 99  : Not found

 After removing 30 — Inorder: 10 20 25 35 40 45 50 60 70 80 

 ================================================================
*/

