#include "bstP.h"
#include <iostream>
#include <queue>
#include <algorithm>

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if (node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}  

// Task 1: Height function (Recursively calculate the height of a node)
int BST::height(node* root)
{
    if (root == nullptr) {
        return -1;  // height of an empty tree is -1
    }

    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);

    return 1 + std::max(leftHeight, rightHeight);
}

// Task 2: CountNodes function (Recursively count the number of nodes)
int BST::countNodes(node* root)
{
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

// Helper function to check balance and calculate height
bool BST::checkBalanceAndHeight(node* root, int& height)
{
    if (root == nullptr) {
        height = -1;  // Height of an empty subtree is -1
        return true;  // An empty subtree is balanced
    }

    int leftHeight = 0, rightHeight = 0;

    // Check balance of left subtree
    bool leftBalanced = checkBalanceAndHeight(root->leftChild, leftHeight);

    // Check balance of right subtree
    bool rightBalanced = checkBalanceAndHeight(root->rightChild, rightHeight);

    // Calculate the height of the current node
    height = std::max(leftHeight, rightHeight) + 1;

    // Check if the current node is balanced (difference in heights <= 1)
    if (std::abs(leftHeight - rightHeight) > 1) {
        return false;  // Tree is unbalanced
    }

    return leftBalanced && rightBalanced;  // Tree is balanced if both subtrees are balanced
}

// Task 3: isBalanced function (Checks if the tree is balanced)
string BST::isBalanced(node* root)
{
    int treeHeight = 0;
    if (checkBalanceAndHeight(root, treeHeight)) {
        return "Yes";  // Balanced
    }

    // If the tree is not balanced, determine whether it is left-heavy or right-heavy
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);

    if (leftHeight > rightHeight) {
        return "Left-heavy";
    } else {
        return "Right-heavy";
    }
}

// Task 4: BFS function (Breadth-first traversal)
void BST::BFS()
{
    if (root == nullptr) {
        return;
    }

    std::queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* current = q.front();
        q.pop();
        std::cout << current->data << " ";

        if (current->leftChild != nullptr) {
            q.push(current->leftChild);
        }
        if (current->rightChild != nullptr) {
            q.push(current->rightChild);
        }
    }
    std::cout << std::endl;
}

// Task 5: Insert function (Handle duplicate insertions)
void BST::insertNode(node*& root, int data)
{
    if (root == nullptr)
    {
        root = new node(data);
        return;
    }

    if (data < root->data)
        insertNode(root->leftChild, data);
    else if (data > root->data)
        insertNode(root->rightChild, data);
    else
    {
        std::cout << "Duplicate found, " << data << " not inserted!" << std::endl;
        return;  // Duplicate found, do not insert
    }
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    std::cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    std::cout << root->data << " ";
}

void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->data << std::endl;
    printTree(root->leftChild, space);
}

