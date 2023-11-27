#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
    int V;
    list<int>* adjList;

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

    void display() {
        for (int i = 0; i < V; i++) {
            cout << i << "=>";
            for (int x : adjList[i]) {
                cout << x << ",";
            }
            cout << endl;
        }
    }
    void display2() {
    for (int i = 0; i < V; i++) {
        cout << string(adjList[i].size() + 1, '-'); // Display dashes based on the number of adjacent vertices
        if (!adjList[i].empty()) {
            cout << "|" << endl; // Display a vertical bar if there are adjacent vertices
        }
    }
}

    ~Graph() {
        delete[] adjList;
    }
};

void generateMap(Graph& g) {
    // Add edges to create the road-like pattern
    g.addEdge(0, 1);
    g.addEdge(1, 2);
}

void startGame(Graph& g) {
    // The game logic goes here
    generateMap(g);
    g.display2();

    // Additional game implementation...
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    startGame(g);

    return 0;
}