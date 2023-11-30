#ifndef Header_h
#define Header_h
#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>

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
                        for (int k = 0; k < getWeight(i * columns + j, v); k++) {
                            cout << "-";
                        }
                    } else {
                        for (int k = 0; k < getWeight(i * columns + j, v); k++) {
                            cout << " ";
                        }
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
                            //cout << " ";
                    // }
                    }
                    if (j != columns - 1) {
                        for (int k = 0; k < getWeight(u, i * columns + j + 1); k++) {
                            cout << " ";
                        }
                    }
                }
            }
            cout << endl;
        }
    }
    ~Graph() {
        delete[] adjList;
    }
};

void generateMap(Graph& g) {    
    // creating a graph with 25 vertices (5*5)
    // 0  1  2  3  4
    // 5  6  7  8  9
    // 10 11 12 13 14
    // 15 16 17 18 19
    // 20 21 22 23 24
    g.addEdge(0, 1, 2);
    g.addEdge(0, 5, 2);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 6, 2);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 7, 2);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 8, 2);
    g.addEdge(4, 9, 2);
    g.addEdge(5, 6, 2);
    g.addEdge(5, 10, 2);
    g.addEdge(6, 7, 2);
    g.addEdge(6, 11, 2);
    g.addEdge(7, 8, 2);
    g.addEdge(7, 12, 2);
    g.addEdge(8, 9, 2);
    g.addEdge(8, 13, 2);
    g.addEdge(9, 14, 2);
    g.addEdge(10, 11, 2);
    g.addEdge(10, 15, 2);
    g.addEdge(11, 12, 2);
    g.addEdge(11, 16, 2);
    g.addEdge(12, 13, 2);
    g.addEdge(12, 17, 2);
    g.addEdge(13, 14, 2);
    g.addEdge(13, 18, 2);
    g.addEdge(14, 19, 2);
    g.addEdge(15, 16, 2);
    g.addEdge(15, 20, 2);
    g.addEdge(16, 17, 2);
    g.addEdge(16, 21, 2);
    g.addEdge(17, 18, 2);
    g.addEdge(17, 22, 2);
    g.addEdge(18, 19, 2);
    g.addEdge(18, 23, 2);
    g.addEdge(19, 24, 2);
    g.addEdge(20, 21, 2);
    g.addEdge(21, 22, 2);
    g.addEdge(22, 23, 2);
    g.addEdge(23, 24, 2);
  
}


#endif /* Header_h */
