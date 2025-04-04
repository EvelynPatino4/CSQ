#include "parse.h"
#include <sstream>
#include <iostream>

using namespace std;

// ======================= PUBLIC FUNCTIONS ================================================

// Node constructor
Node::Node(string val)
{
    value = val;
    left = nullptr;
    right = nullptr; 
}

// Constructor - initializing root
Parser::Parser()
{
    root = nullptr; 
}

// Destructor - free tree memory
Parser::~Parser() 
{
    if (root) {
        deleteTree(root);  // Safely delete the tree
    }
}

void Parser::preOrder() 
{
    preOrderTraversal(root);
    cout << endl;
}

void Parser::inOrder() 
{
    inOrderTraversal(root);
    cout << endl;
}

void Parser::postOrder() 
{
    postOrderTraversal(root);
    cout << endl;
}

double Parser::evaluate() 
{
    return evaluateTree(root);
}

Node* Parser::simplify() 
{
    root = simplifyTree(root);
    return root;
}

// Build the expression tree from a postfix expression
Node* Parser::buildExpressionTree(const string& postfix) 
{
    struct StackNode {
        Node* treeNode;
        StackNode* next;
    };
    
    StackNode* top = nullptr;

    auto push = [&](Node* treeNode) {
        StackNode* newNode = new StackNode{treeNode, top};
        top = newNode;
        cout << "Pushed node: " << treeNode->value << endl;  // Debugging
    };

    auto pop = [&]() -> Node* {
        if (!top) {
            cout << "Error: Stack is empty on pop!" << endl;  // Debugging
            return nullptr;
        }
        Node* treeNode = top->treeNode;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        cout << "Popped node: " << treeNode->value << endl;  // Debugging
        return treeNode;
    };

    stringstream ss(postfix);
    string token;
    
    while (ss >> token) {
        cout << "Processing token: " << token << endl;  // Debugging
        Node* newNode = new Node(token);

        if (isNumber(token)) {
            push(newNode); // Operand to stack
        } else {
            // Operator: Pop two nodes and set them as children
            Node* rightNode = pop();
            Node* leftNode = pop();
            if (leftNode == nullptr || rightNode == nullptr) {
                cout << "Error: Pop operation failed, invalid expression!" << endl;  // Debugging
                return nullptr;
            }
            newNode->right = rightNode;
            newNode->left = leftNode;
            push(newNode);
        }
    }

    root = pop();
    if (!root) {
        cout << "Error: Root node is null after pop!" << endl;  // Debugging
    }
    return root;
}

// ======================= PRIVATE FUNCTIONS ================================================

bool Parser::isNumber(const string& s) {
    for (size_t i = 0; i < s.size(); ++i) {  // Use index-based loop
        if (!isdigit(s[i]) && s[i] != '.') {
            return false;
        }
    }
    return true;
}

// Safely delete the tree nodes
void Parser::deleteTree(Node* node) {
    if (!node) return;

    cout << "Deleting node with value: " << node->value << endl;  // Debugging
    deleteTree(node->left);   // Recursively delete left subtree
    deleteTree(node->right);  // Recursively delete right subtree
    delete node;  // Delete the current node
}

// Recursive Pre-order traversal (C-L-R)
void Parser::preOrderTraversal(Node* node) {
    if (!node) return;
    cout << node->value << " ";  // Print the current node's value
    preOrderTraversal(node->left);  // Traverse left subtree
    preOrderTraversal(node->right); // Traverse right subtree
}

// Recursive In-order traversal (L-C-R)
void Parser::inOrderTraversal(Node* node) {
    if (!node) return;
    if (node->left) {
        cout << "( ";
        inOrderTraversal(node->left);
    }
    cout << node->value << " ";
    if (node->right) {
        inOrderTraversal(node->right);
        cout << ") ";
    }
}

// Recursive Post-order traversal (L-R-C)
void Parser::postOrderTraversal(Node* node) {
    if (!node) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->value << " ";
}

// Evaluate the expression tree
double Parser::evaluateTree(Node* node) {
    if (!node) {
        cout << "Error: Encountered null node during evaluation!" << endl;  // Debugging
        return 0.0;
    }

    // If the node is a number, return its value
    if (isNumber(node->value)) {
        cout << "Evaluating number: " << node->value << endl;  // Debugging
        return stod(node->value);  // Convert string to double
    }

    // Recursively calculate left and right subtrees
    double leftValue = evaluateTree(node->left);
    double rightValue = evaluateTree(node->right);

    // Handle the operators (+, -, *, /)
    if (node->value == "+") {
        cout << "Evaluating addition: " << leftValue << " + " << rightValue << endl;  // Debugging
        return leftValue + rightValue;
    }
    if (node->value == "-") {
        cout << "Evaluating subtraction: " << leftValue << " - " << rightValue << endl;  // Debugging
        return leftValue - rightValue;
    }
    if (node->value == "*") {
        cout << "Evaluating multiplication: " << leftValue << " * " << rightValue << endl;  // Debugging
        return leftValue * rightValue;
    }
    if (node->value == "/") {
        // Check for division by zero
        if (rightValue != 0) {
            cout << "Evaluating division: " << leftValue << " / " << rightValue << endl;  // Debugging
            return leftValue / rightValue;
        } else {
            cout << "Error: Division by zero!" << endl;  // Debugging
            return 0.0;
        }
    }

    // Default return value if no known operator is found
    cerr << "Error: Unknown operator " << node->value << endl;  // Debugging
    return 0.0;
}

// Simplify the tree by applying constant folding and algebraic rules
Node* Parser::simplifyTree(Node* node) {
    if (!node) return nullptr;

    cout << "Simplifying node: " << node->value << endl;  // Debugging

    // Simplify left and right subtrees recursively
    node->left = simplifyTree(node->left);
    node->right = simplifyTree(node->right);

    // If both children are numbers, evaluate and replace with a constant node
    if (node->left && node->right && isNumber(node->left->value) && isNumber(node->right->value)) {
        double result = evaluateTree(node);  // Evaluate the current operation
        cout << "Simplified to: " << result << endl;  // Debugging
        return new Node(to_string(result)); // Replace the node with the computed value
    }

    return node;  // Return the node if simplification wasn't possible
}