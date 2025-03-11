#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class reservation {
public:
    int time;  // assume time in minutes
    reservation* left;
    reservation* right;
    int subtreeSize;  // size of the subtree rooted at this node

    reservation(int t);  // Constructor for initialization
};

class BST {
public:
    reservation* root;

    BST();  // Constructor to initialize the root to nullptr
    ~BST();  // Destructor to clear the tree

    // Complete these three function definitions
    bool checkConflict(reservation* node, int time);  // Task 1: Check conflict
    void insert(reservation*& root, int time);  // Task 2: Insert reservation
    int countPlanes(reservation* node, int time);  // Task 3: Count planes

    void clearTree(reservation* node);  // Helper to clear the tree
    bool reserve(int time);  // Reserve a time slot if no conflict
    void inorder(reservation* root);  // In-order traversal to check reservations

    // Task 1: Implement height function
    int height(reservation* node);

    // Task 2: Implement isBalanced function
    string isBalanced(reservation* node);

    // Task 3: Implement BFS function
    void BFS(reservation* node);
};

#endif

