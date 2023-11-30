//
//  Header.h
//  i222733_F_FinalProject
//
//  Created by Maham on 27/11/2023.
//

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
class Car{
    char symbol;
public:
    Car():symbol('x'){}
    Car(char s):symbol(s){}
    char getSymbol(){return symbol;}
    void setSymbol(char s){symbol = s;}




};
class Graph {
    int V;
    list<pair<int, int> >*adjList; // for weighted graph

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
            if(i*columns+j==carPlace)cout<<'C';
            else cout << "x";
            if (j != columns - 1) {
                if (doesEdgeExist(i * columns + j, i * columns + j + 1)) {
                    for (int k = 0; k < getWeight(i * columns + j, i * columns + j + 1); k++) {
                        cout << "-";
                    }
                } else {
                    for (int k = 0; k < getWeight(i * columns + j, i * columns + j + 1); k++) {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
        if (i != rows - 1) {
            for (int j = 0; j < columns; j++) {
                if (doesEdgeExist(i * columns + j, (i + 1) * columns + j)) {
                    //for (int k = 0; k < getWeight(i * columns + j, (i + 1) * columns + j); k++) {
                        cout << "|";
                   // }
                } else {
                    // for (int k = 0; k < getWeight(i * columns + j, (i + 1) * columns + j); k++) {
                        //cout << " ";
                   // }
                }
                if (j != columns - 1) {
                     for (int k = 0; k < getWeight(i * columns + j, i * columns + j + 1); k++) {
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
    // creating a graph with 9 vertices (3*3)
    // 0 1 2
    // 3 4 5
    // 6 7 8
    g.addEdge(0,1,2);
    g.addEdge(0,3,2);
    g.addEdge(1,2,2);
    g.addEdge(1,4,2);
    g.addEdge(2,5,2);
    g.addEdge(3,4,2);
    g.addEdge(4,5,2);
    g.addEdge(3,6,2);
    g.addEdge(4,7,2);
    g.addEdge(6,7,2);
    g.addEdge(5,8,2);
    g.addEdge(7,8,2);
}


#endif /* Header_h */
