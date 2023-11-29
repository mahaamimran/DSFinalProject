#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
    int V;
    list<int>*adjList;

public:
    Graph(int v) : V(v) {
        adjList = new list<int>[V];
    }

    int getV() {
        return V;
    }

    void setV(int v) {
        V = v;
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void display2() {
        // 0 1 2
        // 3 4 5
        // 6 7 8
        // each node is represented by a 'x'
        // each edge is represented by a '-' or '|'
        // each corner is represented by a '+'
        // each empty space is represented by a ' '
        // displaying this 
        // +-+-+
        // | | |
        // +-+-+
        // | | |
        // +-+-+
        
    }

    ~Graph() {
        delete[] adjList;
    }
};

void generateMap(Graph& g) {    
    // creating a graph with 9 vertices (3*3)
    // 0 1 2
    // 3 4 5
    // 6 7 8
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(1,4);
    g.addEdge(2,5);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(3,6);
    g.addEdge(4,7);
    g.addEdge(6,7);
    g.addEdge(5,8);
    g.addEdge(7,8);
}

void startGame(Graph& g) {
    // The game logic goes here
    generateMap(g);
    g.display2();

    // Additional game implementation...
}

int main() {
    Graph g(9);
    startGame(g);

    return 0;
}
