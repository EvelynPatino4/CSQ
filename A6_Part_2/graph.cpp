#include "graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Graph Constructor
Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;
    visited = new bool[maxV]();
    adjMatrix = new int*[maxV];
    for (int i = 0; i < maxV; i++)
    {
        adjMatrix[i] = new int[maxV]();
        fill(adjMatrix[i], adjMatrix[i] + maxV, 0);  // Initialize the adjacency matrix with 0s
    }
}

// Graph Destructor
Graph::~Graph()
{
    delete[] visited;
    for (int i = 0; i < maxVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

// Add a new vertex to the graph
void Graph::addVertex(char data) {
    if (numVertices < maxVertices) {
        vertex* newVertex = new vertex;
        newVertex->data = data;
        newVertex->visited = false;
        newVertex->vNext = vertices;
        newVertex->aHead = nullptr;
        vertices = newVertex;
        numVertices++;
    } else {
        cout << "Maximum vertices reached!" << endl;
    }
}

// Add an edge between two vertices
void Graph::addEdge(char src, char dest, int weight) {
    int srcIndex = getIndex(src);
    int destIndex = getIndex(dest);
    
    // Add to adjacency matrix
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;  // Since it's an undirected graph
    
    // Add to adjacency list
    vertex* srcVertex = getVertex(src);
    vertex* destVertex = getVertex(dest);
    
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;
    
    // Repeat for the reverse edge for undirected graph
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;
}

// Perform BFS using adjacency list
void Graph::bfsL(char start) {
    vertex* startVertex = getVertex(start);
    if (!startVertex) {
        cout << "Vertex not found!" << endl;
        return;
    }

    queue<vertex*> q;
    startVertex->visited = true;
    q.push(startVertex);
    
    while (!q.empty()) {
        vertex* v = q.front();
        q.pop();
        cout << v->data << " ";

        edge* adj = v->aHead;
        while (adj) {
            if (!adj->dest->visited) {
                adj->dest->visited = true;
                q.push(adj->dest);
            }
            adj = adj->eNext;
        }
    }
    cout << endl;
}

// Perform BFS using adjacency matrix
void Graph::bfsM(char start) {
    int startIndex = getIndex(start);
    vector<bool> visited(maxVertices, false);
    queue<int> q;
    
    visited[startIndex] = true;
    q.push(startIndex);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << char('A' + u) << " ";
        
        for (int v = 0; v < maxVertices; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

// Perform DFS using adjacency list
void Graph::dfsL(char start) {
    vertex* startVertex = getVertex(start);
    if (!startVertex) {
        cout << "Vertex not found!" << endl;
        return;
    }

    stack<vertex*> s;
    startVertex->visited = true;
    s.push(startVertex);

    while (!s.empty()) {
        vertex* v = s.top();
        s.pop();
        cout << v->data << " ";

        edge* adj = v->aHead;
        while (adj) {
            if (!adj->dest->visited) {
                adj->dest->visited = true;
                s.push(adj->dest);
            }
            adj = adj->eNext;
        }
    }
    cout << endl;
}

// Perform DFS using adjacency matrix
void Graph::dfsM(char start) {
    int startIndex = getIndex(start);
    vector<bool> visited(maxVertices, false);
    stack<int> s;
    
    visited[startIndex] = true;
    s.push(startIndex);

    while (!s.empty()) {
        int u = s.top();
        s.pop();
        cout << char('A' + u) << " ";

        for (int v = 0; v < maxVertices; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }
    cout << endl;
}

// Dijkstra's Algorithm (Task 1)
void Graph::dijkstra(char start)
{
    int startIndex = start - 'A';  // Indexing for adjacency matrix

    vector<int> distance(maxVertices, INT_MAX);
    vector<bool> visited(maxVertices, false);
    distance[startIndex] = 0;

    using Pair = pair<int, int>;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, startIndex});

    while (!pq.empty())
    {
        int u = pq.top().second;  
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < maxVertices; v++)
        {
            if (adjMatrix[u][v] != 0 && !visited[v])
            {
                int newDist = distance[u] + adjMatrix[u][v];
                if (newDist < distance[v])
                {
                    distance[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
    }

    cout << "Dijkstra from " << start << ":\n";
    for (int i = 0; i < maxVertices; i++)
    {
        if (distance[i] == INT_MAX)
            cout << start << " -> " << char('A' + i) << " = INF\n";
        else
            cout << start << " -> " << char('A' + i) << " = " << distance[i] << endl;
    }
}

// Kruskal's Algorithm (Task 2)
int find(vector<int>& parent, int i)
{
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSet(vector<int>& parent, vector<int>& rank, int x, int y)
{
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else
    {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void Graph::kruskal()
{
    vector<tuple<int, char, char>> edges;
    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = i + 1; j < maxVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                edges.push_back({adjMatrix[i][j], char('A' + i), char('A' + j)});
            }
        }
    }

    sort(edges.begin(), edges.end());
    vector<int> parent(maxVertices), rank(maxVertices, 0);
    for (int i = 0; i < maxVertices; i++)
        parent[i] = i;

    int totalCost = 0;
    cout << "Kruskal MST:\n";
    for (auto& [weight, uChar, vChar] : edges)
    {
        int u = uChar - 'A';
        int v = vChar - 'A';
        if (find(parent, u) != find(parent, v))
        {
            cout << uChar << " - " << vChar << " : " << weight << endl;
            totalCost += weight;
            unionSet(parent, rank, u, v);
        }
    }
    cout << "Total cost: " << totalCost << endl;
}

// Prim's Algorithm (Task 3)
void Graph::prim(char start)
{
    int startIndex = start - 'A';
    vector<int> key(maxVertices, INT_MAX);
    vector<bool> inMST(maxVertices, false);
    vector<char> parent(maxVertices, -1);

    key[startIndex] = 0;
    using Pair = pair<int, int>;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, startIndex});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (int v = 0; v < maxVertices; v++)
        {
            if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < key[v])
            {
                key[v] = adjMatrix[u][v];
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    int totalCost = 0;
    cout << "Prim MST:\n";
    for (int i = 1; i < maxVertices; i++)
    {
        if (parent[i] != -1)
        {
            cout << char('A' + parent[i]) << " - " << char('A' + i) << " : " << adjMatrix[parent[i]][i] << endl;
            totalCost += adjMatrix[parent[i]][i];
        }
    }
    cout << "Total cost: " << totalCost << endl;
}

// Helper function to get the vertex by data (char)
vertex* Graph::getVertex(char data) {
    vertex* temp = vertices;
    while (temp) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->vNext;
    }
    return nullptr;  // Not found
}

// Helper function to get the index of a vertex
int Graph::getIndex(char data) {
    return data - 'A';  // Assuming vertices are labeled as 'A', 'B', 'C', etc.
}

// Detect cycle in the graph (DFS based)
bool Graph::detectCycle() {
    vector<bool> visited(maxVertices, false);
    vector<bool> recStack(maxVertices, false);

    for (int i = 0; i < maxVertices; i++) {
        if (!visited[i]) {
            if (detectCycleUtil(i, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

// Helper function for cycle detection (DFS)
bool Graph::detectCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
    if (recStack[v]) {
        return true;
    }

    if (visited[v]) {
        return false;
    }

    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < maxVertices; i++) {
        if (adjMatrix[v][i] != 0 && detectCycleUtil(i, visited, recStack)) {
            return true;
        }
    }

    recStack[v] = false;
    return false;
}
