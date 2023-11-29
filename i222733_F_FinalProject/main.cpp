#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    void display(int rows, int columns) {
        // Each node is represented by a 'x'
        // Each edge is represented by a '-' or '|'
        // check if edge exists between two nodes
        // if yes, print '-' or '|'
        // else print ' '
        // print edge based on weight, eg. weight 1 = '-', weight 2 = '--', weight 3 = '---' 
        // or weight 2 =
        // |
        // |

        for(int i=0; i<rows; i++) {
            for(int j=0; j<columns; j++) {
                cout << "x";
                if(j != columns-1) {
                    if(doesEdgeExist(i*columns+j, i*columns+j+1)) {
                        for(int i=0; i<getWeight(i*columns+j, i*columns+j+1); i++) {
                            cout << "-";
                        }
                    } else {
                        cout << " ";
                    }
                }
            }
            cout << endl;
            if(i != rows-1) {
                for(int j=0; j<columns; j++) {
                    if(doesEdgeExist(i*columns+j, (i+1)*columns+j)) {
                        cout << "|";
                    } else {
                        cout << " ";
                    }
                    if(j != columns-1) {
                        cout << " ";
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
    g.addEdge(1,2,1);
    g.addEdge(1,4,1);
    g.addEdge(2,5,1);
    g.addEdge(3,4,1);
    g.addEdge(4,5,1);
    g.addEdge(3,6,1);
    g.addEdge(4,7,1);
    g.addEdge(6,7,1);
    g.addEdge(5,8,1);
    g.addEdge(7,8,1);
}
int main() {
    Graph g(9);
    generateMap(g);
    g.display(3,3);

    return 0;
}
