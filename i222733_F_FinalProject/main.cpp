#include "Header.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void manualMode(Graph &g, int rows, int columns, Car &car, int &score,
                list<Obstacle> &obstacles, list<Coins> &coins,
                list<PowerUp> &powerups) {
  char c;
  // displaying map
  display(g, rows, columns, car, coins, obstacles, powerups, score);
  cout << "Press a, w, s, d to move the car\nPress q to quit" << endl;
  while (true) {
    // moving car
    cin >> c;
    if (c == 'a') {
      car.moveCar(g, 'a', rows, columns, score, obstacles, coins, powerups);
      display(g, rows, columns, car, coins, obstacles, powerups, score);
    } else if (c == 'w') {
      car.moveCar(g, 'w', rows, columns, score, obstacles, coins, powerups);
      display(g, rows, columns, car, coins, obstacles, powerups, score);
    } else if (c == 's') {
      car.moveCar(g, 's', rows, columns, score, obstacles, coins, powerups);
      display(g, rows, columns, car, coins, obstacles, powerups, score);
    } else if (c == 'd') {
      car.moveCar(g, 'd', rows, columns, score, obstacles, coins, powerups);
      display(g, rows, columns, car, coins, obstacles, powerups, score);
    } else if (c == 'q') {
      break;
    } else {
      cout << "Invalid input" << endl;
    }
  }
}

void autoMode(Graph &g, int rows, int columns, Car &car,
              list<Obstacle> &obstacles, int &score, list<Coins> &coins) {
  // Code for auto mode
  cout << "Press q to quit" << endl;
}

void writeToFile(string name, int score) {
  fstream fout;
  string filePath = "/Users/mahamimran/teesra "
                    "semester/DS/i222733_F_FinalProject/scoreBoard.csv";
  fout.open(filePath, ios::app);
  fout << name << "," << score << endl;
  fout.close();
}


void viewScoreBoard() {
// Read the scores from the CSV file and insert them into the BST
    string filePath = "/Users/mahamimran/teesra semester/DS/i222733_F_FinalProject/scoreBoard.csv";
    ifstream fin(filePath);
    string line;
    Node* root = nullptr;

    while (getline(fin, line)) {
        // Find the position of the comma to separate name and score
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string scoreStr = line.substr(pos + 1);
            int score = stoi(scoreStr);
            root = insert(root, name, score);
        }
    }

    // Display the scores in ascending order
    cout << "Name "<< "\t" << "Score\n";
    cout<<"-------------\n";
    inOrderTraversal(root);
    fin.close();
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
  vector<int> path = g.dijkstrasAlgorithm(0, vertices - 1);
  generateMap(g, rows, columns);

  // generating coins obstacles and powerups
  generateCoins(g, rows, columns, coins);
  generateObstacles(g, rows, columns, obstacles);
  generatePowerUps(g, rows, columns, powerups);

  // the game has two modes, manual and auto
  // ask user to choose mode
  cout << "Which mode would you like to select?\n1. Manual\n2. Auto\n3. View "
          "Scoreboard\n";
  int mode;
  cin >> mode;
  if (mode == 1) {
    cout << "Enter your name: ";
    string name;
    cin >> name;
    manualMode(g, rows, columns, car, score, obstacles, coins, powerups);
    writeToFile(name, score);
  } else if (mode == 2) {
    cout << "Enter your name: ";
    string name;
    cin >> name;
    autoMode(g, rows, columns, car, obstacles, score, coins);
    writeToFile(name, score);
  } else if (mode == 3) {
    viewScoreBoard();
  } else {
    cout << "Invalid input" << endl;
  }
  return 0;
}