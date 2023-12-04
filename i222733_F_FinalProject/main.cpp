#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Header.h"
using namespace std;
void handlingScoreBoard(string name, int score){
    cout << "Score: " << score << "\n";
    // write to file
    ofstream file;
    file.open("scoreboard.txt", ios::app);
    file << name << "%" << score << "\n";
    file.close();
}
int main() {
    Car car;
    list<Obstacle>obstacles;
    int score = 0;
    int rows=6,columns=6;
    int vertices=rows*columns;
    Graph g(vertices);
    generateMap(g,rows,columns);
    vector<int>path=g.dijkstrasAlgorithm(0, vertices - 1);
    enqueObstacles(obstacles,rows,columns,path);


    char c;
    cout << "Shortest path: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;

    int carPlace = 0;
    display(g,rows, columns, car, obstacles, score);
    cout<<"Press a,w,s,d to move the car\nPress q to quit"<<endl;
    // move car
    while(true) {
        cin>>c;
        if(c == 'a') {
            car.moveCar(g, 'a',rows,columns,obstacles, score);
            display(g,rows, columns, car, obstacles, score);
        }
        else if(c == 'w') {
            car.moveCar(g, 'w',rows,columns,obstacles, score);
            display(g,rows, columns, car, obstacles, score);
        }
        else if(c == 's') {
            car.moveCar(g, 's',rows,columns,obstacles, score);
            display(g,rows, columns, car, obstacles, score);
        }
        else if(c == 'd') {
            car.moveCar(g, 'd',rows,columns,obstacles, score);
            display(g,rows, columns, car, obstacles, score);
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
