
#include <iostream>
#include "Header.h"
#include <list>
using namespace std;

struct Node{
    int data;
    Node*next;
};
class Graph{
    int V;
    list<int>*adjList;
public:
    Graph(int v):V(v){
        adjList = new list<int>[V];
    }
    void addEdge(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    // display like 2D array
    void display(){
        for(int i=0;i<V;i++){
            cout<<i<<"=>";
            for(int x:adjList[i]){
                cout<<x<<",";
            }
            cout<<endl;
        }
    }
       void displayAsGraphMatrix() {
        // Create a 2D array for the adjacency matrix
        int** matrix = new int*[V];
        for (int i = 0; i < V; i++) {
            matrix[i] = new int[V];
            for (int j = 0; j < V; j++) {
                matrix[i][j] = 0; // Initialize all elements to 0
            }
        }

        // Fill the adjacency matrix
        for (int i = 0; i < V; i++) {
            for (int x : adjList[i]) {
                matrix[i][x] = 1; // Set matrix[i][x] to 1 if there is an edge between i and x
            }
        }

        // Display the adjacency matrix
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        // Deallocate memory
        for (int i = 0; i < V; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    ~Graph() {
        delete[] adjList;
    }


};

int main() {
    Graph g(5); 
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.display();
    g.displayAsGraphMatrix();
    

    return 0;
}
