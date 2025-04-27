#include "graph.h"
#include <iostream>

int main()
{
    Graph graph(10); 
    
    // Adding vertices
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');
    graph.addVertex('E');
    graph.addVertex('F');  
    graph.addVertex('G');
    graph.addVertex('H');
    graph.addVertex('I');
    graph.addVertex('J');

    // Adding edges
    graph.addEdge('A', 'B', 1);
    graph.addEdge('A', 'C', 2);
    graph.addEdge('B', 'D', 3);
    graph.addEdge('C', 'E', 4);
    graph.addEdge('C', 'D', 5);
    graph.addEdge('E', 'D', 6);
    graph.addEdge('A', 'H', 7);
    graph.addEdge('B', 'G', 8);
    graph.addEdge('F', 'I', 9);
    graph.addEdge('F', 'J', 10);
    graph.addEdge('I', 'J', 11);
    graph.addEdge('C', 'F', 12); 
    graph.addEdge('D', 'F', 13);
    graph.addEdge('C', 'H', 14);

    // Perform BFS (Matrix version)
    cout << "BFS (Matrix version) starting from vertex A: ";
    graph.bfsM('A');
    
    // Perform DFS (List version)
    cout << "DFS (List version) starting from vertex A: ";
    graph.dfsL('A');

    // Perform DFS (Matrix version)
    cout << "DFS (Matrix version) starting from vertex A: ";
    graph.dfsM('A');

    // Detect cycle
    if (graph.detectCycle())
        cout << "Detect Cycle: Yes" << endl;
    else
        cout << "Detect Cycle: No" << endl;

    // Task 1: Run Dijkstra from vertex 'A'
    cout << "\nTask 1: Dijkstra's Algorithm (starting from A):" << endl;
    graph.dijkstra('A');

    // Task 2: Run Kruskal's Algorithm to find the Minimum Spanning Tree
    cout << "\nTask 2: Kruskal's Algorithm (MST):" << endl;
    graph.kruskal();

    // Task 3: Run Prim's Algorithm to find the Minimum Spanning Tree
    cout << "\nTask 3: Prim's Algorithm (MST, starting from A):" << endl;
    graph.prim('A');

    return 0;
}

