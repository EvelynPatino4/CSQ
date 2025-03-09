// In bstP.h
#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};

class BST
{
public:
    node* root;

    BST();
    ~BST();
    void clearTree(node* node);

    void insertNode(node*& root, int data);
    node* searchNode(node*& root, int data);
    void deleteNode(node*& root, int data);

    void preorder(node* root);
    void inorder(node* root);
    void postorder(node* root);

    void printTree(node* root, int space);

    // Task 1: height function
    int height(node* root);

    // Task 2: countNodes function
    int countNodes(node* root);

    // Task 3: isBalanced function
    string isBalanced(node* root);

    // Task 4: BFS function
    void BFS();

    // Helper function to check balance and calculate height
    bool checkBalanceAndHeight(node* root, int& height);
};

#endif
