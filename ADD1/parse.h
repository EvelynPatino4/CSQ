#ifndef PARSE_H
#define PARSE_H

#include <iostream>
// #include <stack> - Don't use this library
#include <cctype>
#include <cmath>
#include <string>
#include <sstream>


using namespace std;

class Node {
    public:
        string value;
        Node* left;
        Node* right;

        Node(string val);
};


class Parser {
    private:
        Node* root;

        bool isNumber(const string& s);
        Node* simplifyTree(Node* node);
        double evaluateTree(Node* node);
        void preOrderTraversal(Node* node);
        void inOrderTraversal(Node* node);
        void postOrderTraversal(Node* node);
        void deleteTree(Node* node);

    public:
        Parser();
        ~Parser();

        Node* buildExpressionTree(const string& postfix);
        void preOrder();
        void inOrder();
        void postOrder();
        double evaluate();
        Node* simplify();
};

#endif 



