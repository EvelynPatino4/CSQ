#include "bstA.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cerr <<"Usage: ./a <filename>" << endl;
        return 1;
    }

    int size = 50;
    string filename = argv[1];

    BST bst(size);

    ifstream infile(filename);

    if(!infile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while(getline(infile, line))
    {
        istringstream iss(line);
        int command, data;
        iss >> command;
        
        switch(command) {
            case 0:
                cout << "Exiting ..." << endl;
                return 0;
            case 1:
                iss >> data;
                bst.insertI(data);
                cout << "Insert I: " << data << endl;
                break;
            case 2:
                iss >> data;
                bst.insertR(data);
                cout << "Insert R: " << data << endl;
                break;
            case 3:
                iss >> data;
                if(bst.searchI(data))
                    cout << data << " found I" << endl;
                else
                    cout << data << " not found I" << endl;
                break;
            case 4:
                iss >> data;
                if(bst.searchR(data))
                    cout << data << " found R" << endl;
                else
                    cout << data << " not found R" << endl;
                break;
            case 5:
                cout << "Preoder traversal: ";
                bst.preorder();
                cout << endl;
                break;
            case 6:
                cout << "Inorder traversal: ";
                bst.inorder();
                cout << endl;
                break;
            case 7:
                cout << "Postorder traversal: ";
                bst.postorder();
                cout << endl;
                break;
            case 8:
                cout << "Binary Search Tree" << endl;
                bst.printTree(0, 0);
                cout << endl;
                break;
            default:
                cout << "Invalid command" << endl;
        }
    }

    return 0;
}