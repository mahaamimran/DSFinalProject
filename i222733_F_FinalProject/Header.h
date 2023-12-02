#ifndef Header_h
#define Header_h
#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
class Graph {
    int V;
    list<pair<int, int> >*adjList;
public:
    Graph():V(0),adjList(nullptr){}
    Graph(int v):V(v){
        adjList = new list<pair<int, int> >[V];
    }
    int getV(){return V;}
    void setV(int v){V = v;}
    list<pair<int, int> >* getAdjList(){return adjList;}
    void setAdjList(list<pair<int, int> >* adjlist){adjList = adjlist;}
    void addEdge(int u, int v, int weight=0,bool bidir=true){
        adjList[u].push_back(make_pair(v, weight));
        if(bidir)adjList[v].push_back(make_pair(u, weight));
    }
    bool doesEdgeExist(int u,int v) {
        for(auto i:adjList[u]) {
            if(i.first == v) {
                return true;
            }
        }
        return false;
    }
    int getWeight(int u, int v) {
        for(auto i:adjList[u]) {
            if(i.first == v) {
                return i.second;
            }
        }
        return 0;
    }
    void display(int rows, int columns,int carPlace=0) {
    // Each node is represented by a 'x'
    // Each edge is represented by a '-' or '|'
    // Check if edge exists between two nodes
    // If yes, print '-' or '|'
    // Else print ' '
    // Print edge based on weight, e.g., weight 1 = '-', weight 2 = '--', weight 3 = '---'
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                int u=i*columns+j;
                int v=i*columns+j+1;
                if(i*columns+j==carPlace)cout<<"C";
                else cout << "x";
                if (j != columns - 1) {
                    if (doesEdgeExist(u, v)) {
                        //for (int k = 0; k < getWeight(i * columns + j, v); k++) {
                            cout << "--";
                        //}
                    } else {
                        //for (int k = 0; k < getWeight(i * columns + j, v); k++) {
                            cout << "  ";
                        //}
                    }
                }
            }
            cout << endl;
            if (i != rows - 1) {
                for (int j = 0; j < columns; j++) {
                    int u=i*columns+j;
                    int v=(i+1)*columns+j;
                    if (doesEdgeExist(u, v)) {
                        //for (int k = 0; k < getWeight(u, v); k++) {
                            cout << "|";
                    // }
                    } else {
                        // for (int k = 0; k < getWeight(u, v); k++) {
                            cout << " ";
                    // }
                    }
                    if (j != columns - 1) {
                        //for (int k = 0; k < getWeight(u, i * columns + j + 1); k++) {
                            cout << "  ";
                        //}
                    }
                }
            }
            cout << endl;
        }
    }
    void clear() {
        for (int i = 0; i < V; i++) {
            adjList[i].clear();
        }
    }
    std::vector<int> findPath(int source, int destination) {
        std::vector<int> path;

        // Create a queue for BFS
        std::queue<int> queue;

        // Create a vector to store the parent of each vertex
        std::vector<int> parent(V, -1);

        // Create a vector to store whether a vertex has been visited or not
        std::vector<bool> visited(V, false);

        // Mark the source vertex as visited and enqueue it
        visited[source] = true;
        queue.push(source);

        // Run BFS until the queue is empty
        while (!queue.empty()) {
            // Dequeue a vertex from the queue
            int vertex = queue.front();
            queue.pop();

            // Get all adjacent vertices of the dequeued vertex vertex
            for (auto neighbor : adjList[vertex]) {
                // If a adjacent has not been visited, then mark it visited and enqueue it
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    queue.push(neighbor.first);
                    parent[neighbor.first] = vertex;
                }
            }
        }

        // Check if there is a path from the source to the destination
        if (visited[destination]) {
            // Traverse the path and store it in the vector 'path'
            int vertex = destination;
            while (vertex != -1) {
                path.push_back(vertex);
                vertex = parent[vertex];
            }

            // Reverse the path vector
            std::reverse(path.begin(), path.end());
        }

        return path;
    }
    ~Graph() {
        delete[] adjList;
    }
};




void generateMap(Graph& g) {
    // Set the seed for the random number generator
    srand(int(time(0)));

    int rows = 5;
    int columns = 5;
    int totalVertices = rows * columns;

    bool pathFound = false;

    while (!pathFound) {
        g.clear(); // Clear the graph

        // Create a graph with 'totalVertices' vertices
        for (int i = 0; i < totalVertices; i++) {
            int vertex = i;

            std::vector<int> neighbors;

            // Check if there is a neighbor to the left
            if (vertex % columns != 0) {
                int leftNeighbor = vertex - 1;
                neighbors.push_back(leftNeighbor);
            }

            // Check if there is a neighbor to the right
            if (vertex % columns != columns - 1) {
                int rightNeighbor = vertex + 1;
                neighbors.push_back(rightNeighbor);
            }

            // Check if there is a neighbor above
            if (vertex >= columns) {
                int topNeighbor = vertex - columns;
                neighbors.push_back(topNeighbor);
            }

            // Check if there is a neighbor below
            if (vertex < totalVertices - columns) {
                int bottomNeighbor = vertex + columns;
                neighbors.push_back(bottomNeighbor);
            }

            // Randomly shuffle the neighbors vector
            std::random_shuffle(neighbors.begin(), neighbors.end());

            // Select a random number of neighbors to connect
            int numPaths = std::rand() % (neighbors.size() + 1);
            for (int j = 0; j < numPaths; j++) {
                int neighbor = neighbors[j];
                int weight = 2; // Set a fixed weight for the path
                g.addEdge(vertex, neighbor, weight);
            }
        }

        // Check if there is a path from the top left corner to the bottom right corner
        std::vector<int> path = g.findPath(0, totalVertices - 1);
        if (!path.empty()) {
            pathFound = true;
        }
    }
}

#endif /* Header_h */
