#include "parse.h"

int main() {
    string postfix;

    cout << "Enter postfix expression (space-separated): ";
    getline(cin, postfix);

    Parser parser;

    // Build the expression tree
    Node* root = parser.buildExpressionTree(postfix);

    if (!root) {
        cerr << "Invalid expression!" << endl;
        return 1;
    }

    // Display tree traversals
    cout << "\nIn-order Traversal (Infix): ";
    parser.inOrder();

    cout << "Pre-order Traversal (Prefix): ";
    parser.preOrder();

    cout << "Post-order Traversal (Postfix): ";
    parser.postOrder();

    // Evaluate the expression
    cout << "\nExpression Result: " << parser.evaluate() << endl;

    // Optimize the tree
    cout << "\nOptimizing the expression tree..." << endl;
    parser.simplify();

    cout << "Optimized Expression: ";
    parser.inOrder();
    cout << endl;

    return 0;
}

