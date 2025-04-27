#ifndef GRAPH_H 
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct vertex;

struct edge
{
    vertex* dest;
    edge* eNext;
    int weight;
};

struct vertex
{
    char data;
    vertex* vNext;
    edge* aHead;
    bool visited;
};

// implementing both adj list and adj matrix for an undirected weighted graph
class Graph 
{
    private:
        vertex* vertices; // list of vertices
        int** adjMatrix; 
        bool* visited;
        int maxVertices;
        int numVertices;

    public:
        Graph(int maxV);
        ~Graph();

        // core operations
        void addVertex(char data);
        void addEdge(char src, char dest, int weight);
        void removeVertex(char data);
        void removeEdge(char src, char dest);  // complete this

        // traversal/search algorithms
        void bfsL(char start);
        void bfsM(char start); // complete this
        void dfsL(char start);
        void dfsM(char start);   

        bool detectCycle();  // Detect cycle in the graph
        void dijkstra(char start);
        void kruskal();
        void prim(char start);

        // ---------------- Extra Credits - Pick one of the two ----------------------------- 
        // Detect cycle with DFS - Option 1
        // bool detectCycleDFS();

        // Print Connected Components - Option 2
        // void connectedComponents();

    private:
        // Helper function for cycle detection (used by detectCycle)
        bool detectCycleUtil(int v, std::vector<bool>& visited, std::vector<bool>& recStack);


    // Helpers
    vertex* getVertex(char data);  // (Optional, can be used internally)
    int getIndex(char data);       // Map char to index (e.g., 'A' → 0)

};

#endif
