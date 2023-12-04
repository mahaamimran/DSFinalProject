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

void handlingScoreBoard(string name, int score) {
    // Code for handling the scoreboard
}

void manualMode(Graph& g, int rows, int columns, Car& car, int& score, list<Obstacle>& obstacles, list<Coins>& coins, list<PowerUp>& powerups) {
    char c;
    // displaying map
    display(g, rows, columns, car,coins,obstacles,powerups, score);
    cout << "Press a, w, s, d to move the car\nPress q to quit" << endl;
    while (true) {
        // moving car
        cin >> c;
        if (c == 'a') {
            car.moveCar(g, 'a', rows, columns, score, obstacles, coins);
            display(g, rows, columns, car,coins,obstacles,powerups, score);
        }
        else if (c == 'w') {
            car.moveCar(g, 'w', rows, columns, score, obstacles, coins);
            display(g, rows, columns, car,coins,obstacles,powerups, score);
        }
        else if (c == 's') {
            car.moveCar(g, 's', rows, columns, score, obstacles, coins);
            display(g, rows, columns, car,coins,obstacles,powerups, score);
        }
        else if (c == 'd') {
            car.moveCar(g, 'd', rows, columns, score, obstacles, coins);
            display(g, rows, columns, car,coins,obstacles,powerups, score);
        }
        else if (c == 'q') {
            break;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
}

void autoMode(Graph& g, int rows, int columns, Car& car, list<Obstacle>& obstacles, int& score, list<Coins>& coins) {
    // Code for auto mode
    cout << "Press q to quit" << endl;
}

int main() {
    // declaring variables
    Car car;
    list<Obstacle> obstacles;
    list<Coins> coins;
    list<PowerUp> powerups;

    char c;
    int score = 0;
    int rows = 6, columns = 6;
    int vertices = rows * columns;
    int carPlace = 0;
    Graph g(vertices);

    // generating map
    vector<int>path = g.dijkstrasAlgorithm(0, vertices - 1);
    generateMap(g, rows, columns);

    // generating coins obstacles and powerups
    generateCoins(g, rows, columns, coins);
    generateObstacles(g, rows, columns, obstacles);
    generatePowerUps(g, rows, columns, powerups);


    // the game has two modes, manual and auto
    // ask user to choose mode
    cout << "Enter your name: ";
    string name;
    cin >> name;
    cout << "Which mode would you like to select?\n1. Manual\n2. Auto\n";
    int mode;
    cin >> mode;

 if (mode == 1) {
    manualMode(g, rows, columns, car, score, obstacles, coins, powerups);
  } else if (mode == 2) {
    autoMode(g, rows, columns, car, obstacles, score, coins);
  } else {
    cout << "Invalid input" << endl;
  }

    return 0;
}