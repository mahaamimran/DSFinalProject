#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Header.h"
class Car{
    char symbol;
public:
    Car():symbol('C'){}
    Car(char s):symbol(s){}
    char getSymbol(){return symbol;}
    void setSymbol(char s){symbol = s;}
    void moveCar(Graph&g, char direction,int& carPlace,int rows,int cols) {
        system("clear");
        if(direction=='a') {
            if(carPlace%cols == 0) {
                cout<<"Can't move left"<<endl;
            }
            else {
                if(g.doesEdgeExist(carPlace, carPlace-1)) {
                    carPlace--;
                }
                else {
                    cout<<"Can't move left"<<endl;
                }
            }
        }
        else if(direction == 'w') {
            if(carPlace-cols < 0) {
                cout<<"Can't move up"<<endl;
            }
            else {
                if(g.doesEdgeExist(carPlace, carPlace-cols)) {
                    carPlace-=cols;
                }
                else {
                    cout<<"Can't move up"<<endl;
                }
            }
        }
        else if(direction == 's') {
            if(carPlace+cols >= rows*cols) {
                cout<<"Can't move down"<<endl;
            }
            else {
                if(g.doesEdgeExist(carPlace, carPlace+cols)) {
                    carPlace+=cols;
                }
                else {
                    cout<<"Can't move down"<<endl;
                }
            }
        }
        else if(direction == 'd') {
            if(carPlace%cols == cols-1) {
                cout<<"Can't move right"<<endl;
            }
            else {
                if(g.doesEdgeExist(carPlace, carPlace+1)) {
                    carPlace++;
                }
                else {
                    cout<<"Can't move right"<<endl;
                }
            }
        }
    }
};
int main() {
    Car car;
    int rows=6,columns=8;
    // if row 
    int vertices = rows*columns;
    Graph g(vertices);
    generateMap(g,rows,columns);
    char c;
    int carPlace = 0;
    g.display(rows,columns,carPlace);
    cout<<"Press a,w,s,d to move the car\nPress q to quit"<<endl;
    while(true) {
        cin>>c;
        if(c == 'a') {
            car.moveCar(g, 'a',carPlace,rows,columns);
            g.display(rows,columns,carPlace);
        }
        else if(c == 'w') {
            car.moveCar(g, 'w',carPlace,rows,columns);
            g.display(rows,columns,carPlace);
        }
        else if(c == 's') {
            car.moveCar(g, 's',carPlace,rows,columns);
            g.display(rows,columns,carPlace);
        }
        else if(c == 'd') {
            car.moveCar(g, 'd',carPlace,rows,columns);
            g.display(rows,columns,carPlace);
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
