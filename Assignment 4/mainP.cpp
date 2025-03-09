#include "bstP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./bstProgram <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    BST tree;  // Create a BST object

    // Open the input file
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data;

        if (!(iss >> command)) {
            cerr << "Invalid command format." << endl;
            continue;
        }

        switch (command) {
            case 0:
                cout << "Exiting...!" << endl;
                return 0;
            case 1:
                if (iss >> data) {
                    // Insert node into the BST
                    tree.insertNode(tree.root, data);
                    cout << "Insert: " << data << endl;
                } else {
                    cerr << "Invalid insert command." << endl;
                }
                break;
            case 2:
                if (iss >> data) {
                    // Search for the node in the BST
                    node* result = tree.searchNode(tree.root, data);
                    cout << (result ? "Found: " + to_string(data) : "Not found") << endl;
                } else {
                    cerr << "Invalid search command." << endl;
                }
                break;
            case 3:
                if (iss >> data) {
                    // Delete node from the BST
                    tree.deleteNode(tree.root, data);
                    cout << "Deleted: " << data << endl;
                } else {
                    cerr << "Invalid delete command." << endl;
                }
                break;
            case 4:
                // Perform Inorder traversal
                cout << "Inorder traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 5:
                // Perform Preorder traversal
                cout << "Preorder traversal: ";
                tree.preorder(tree.root);
                cout << endl;
                break;
            case 6:
                // Perform Postorder traversal
                cout << "Postorder traversal: ";
                tree.postorder(tree.root);
                cout << endl;
                break;
            case 7:
                // Perform BFS traversal
                cout << "BFS traversal: ";
                tree.BFS();
                break;
            case 8:
                // Print tree height
                cout << "Height of the tree: " << tree.height(tree.root) << endl;
                break;
            case 9:
                // Print number of nodes in the tree
                cout << "Number of nodes: " << tree.countNodes(tree.root) << endl;
                break;
            case 10:
                // Check if the tree is balanced
                cout << "Is the tree balanced? " << tree.isBalanced(tree.root) << endl;
                break;
            default:
                cerr << "Invalid command." << endl;
        }
    }

    return 0;
}
