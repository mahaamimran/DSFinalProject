#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Header.h"

int main() {
    Car car;
    int rows=6,columns=6;
    int vertices = rows*columns;
    Graph g(vertices);
    generateMap(g,rows,columns);
    char c;
     vector<int> path = g.dijkstrasAlgorithm(0, vertices - 1);
    cout << "Shortest path: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;

    int carPlace = 0;
    display(g,rows, columns, car);
    cout<<"Press a,w,s,d to move the car\nPress q to quit"<<endl;
    // move car
    while(true) {
        cin>>c;
        if(c == 'a') {
            car.moveCar(g, 'a',rows,columns);
            display(g,rows, columns, car);
        }
        else if(c == 'w') {
            car.moveCar(g, 'w',rows,columns);
           display(g,rows, columns, car);
        }
        else if(c == 's') {
            car.moveCar(g, 's',rows,columns);
            display(g,rows, columns, car);
        }
        else if(c == 'd') {
            car.moveCar(g, 'd',rows,columns);
            display(g,rows, columns, car);
        }
        else if(c == 'q') {
            break;
        }
        else {
            cout<<"Invalid input"<<endl;
        }
    }
    
    return 0;
}
