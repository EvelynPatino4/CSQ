#include "reserve.h"

// Constructor to initialize reservation
reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr;
    subtreeSize = 1; // initialize subtree size as 1 (itself)
}

// Constructor for BST
BST::BST() {
    root = nullptr;
}

// Destructor for BST to clear all nodes
BST::~BST() {
    clearTree(root);
}

// Helper function to recursively delete the tree
void BST::clearTree(reservation* node) {
    if (node == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Reserve new landing time
bool BST::reserve(int time) {
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }

    insert(root, time); // insert new time in the tree
    return true; // no conflict - reservation successful
}

// Check for landing time conflicts within 3 minutes
bool BST::checkConflict(reservation* node, int time) {
    if (node == nullptr)
        return false; // no conflict, reached leaf

    // If current node's time is within 3 minutes of the desired time, conflict
    if (abs(node->time - time) <= 3)
        return true;

    // If the time is less than the current node's time, check the left subtree
    if (time < node->time)
        return checkConflict(node->left, time);
    else // If the time is greater, check the right subtree
        return checkConflict(node->right, time);
}

// Insert new reservation and update subtree size
void BST::insert(reservation*& node, int time) {
    if (node == nullptr) {
        node = new reservation(time); // Insert a new node
        return;
    }

    if (time < node->time) {
        insert(node->left, time); // Insert in the left subtree
    } else if (time > node->time) {
        insert(node->right, time); // Insert in the right subtree
    }
    // Duplicates are not inserted (we assume no exact duplicate times)

    // Update the subtree size of the current node
    node->subtreeSize = 1 + (node->left ? node->left->subtreeSize : 0) + (node->right ? node->right->subtreeSize : 0);
}

// Count planes with landing times <= t
int BST::countPlanes(reservation* node, int t) {
    if (node == nullptr)
        return 0; // No nodes, so count is 0

    if (node->time > t) {
        return countPlanes(node->left, t); // We only need to look at the left subtree
    } else {
        // Count this node + all nodes in the left subtree + all nodes in the right subtree whose time <= t
        return 1 + (node->left ? node->left->subtreeSize : 0) + countPlanes(node->right, t);
    }
}

// Inorder traversal to display the tree (for debugging)
void BST::inorder(reservation* root) {
    if (root == nullptr)
        return; // Base case, if the node is null, do nothing
    
    inorder(root->left);  // Traverse left subtree
    cout << root->time << " ";  // Print the current node's time
    inorder(root->right);  // Traverse right subtree
}

