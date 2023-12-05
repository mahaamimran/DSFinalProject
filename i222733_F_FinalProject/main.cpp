#include "Header.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;
void manualMode(Graph &g, int rows, int columns, Car &car, int &score,
                list<Obstacle> &obstacles, list<Coins> &coins,
                list<PowerUp> &powerups) {
  char c;
  // displaying map
  display(g, rows, columns, car, coins, obstacles, powerups, score);
  cout << "Press A, W, S or D to move the car\nPress Q to quit" << endl;
  while (true) {
    car.displaySteps();
    cin >> c;
    if (c == 'a' || c == 'w' || c == 's' || c == 'd') {
      car.moveCar(g, c, rows, columns, score, obstacles, coins, powerups);
      display(g, rows, columns, car, coins, obstacles, powerups, score);
    } else if (c == 'q') {
      break;
    } else {
      cout << "Invalid input" << endl;
    }
  }
}
void autoMode(Graph &g, int rows, int columns, Car &car, list<Obstacle> &obstacles, int &score, list<Coins> &coins, list<PowerUp>& powerUps, vector<int> path){
    // Print path
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    // Iterate over the path
    for (int i = 0; i < path.size() - 1; i++) {
        int currentVertex = path[i];
        int nextVertex = path[i + 1];

        // Find the direction of the next vertex
        char direction = g.findDirection(currentVertex, nextVertex, rows, columns);

        // Display intermediate state
        car.moveCar(g, direction, rows, columns, score, obstacles, coins, powerUps);
        display(g, rows, columns, car, coins, obstacles, powerUps, score);

        // Move the car based on the direction

        // Check for collision or other events
        // Note: Implement collision and event checks here if needed

        //display(g, rows, columns, car, coins, obstacles, powerUps, score);
        // Introduce a delay for visibility (adjust as needed)
      sleep(1); 
    }

    // Display the final state after reaching the destination

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
  string filePath = "/Users/mahamimran/teesra "
                    "semester/DS/i222733_F_FinalProject/scoreBoard.csv";
  ifstream fin(filePath);
  string line;
  NodeBST *root = nullptr;

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
  cout << "Name "
       << "\t"
       << "Score\n";
  cout << "-------------\n";
  inOrderTraversal(root);
  fin.close();
}
void displayAllQueues() {
  // displaying all the queues at the end of the game
  cout << "Coins: ";
  collectedCoins.display();
  cout << "Obstacles: ";
  collectedObstacles.display();
  cout << "PowerUps: ";
  collectedPowerUps.display();
  cout << endl;
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
  generateMap(g, rows, columns);
  vector<int> path = g.dijkstrasAlgorithm(0, vertices - 1);

  // generating coins obstacles and powerups
  generateItems(g, rows, columns, coins, obstacles, powerups);

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
    // clear screen
    system("clear");
    manualMode(g, rows, columns, car, score, obstacles, coins, powerups);
    writeToFile(name, score);
    cout << "Game Over " << name << "! Your score is: " << score << endl;
    cout << "Everything you bumped into:\n";
    displayAllQueues();
  } else if (mode == 2) {
    //system("clear");
    string name="auto mode";
    autoMode(g, rows, columns, car, obstacles, score, coins, powerups, path);
    writeToFile(name, score);
    cout << "Game Over " << name << "! Your score is: " << score << endl;
    cout << "Everything you bumped into:\n";
    displayAllQueues();
  } else if (mode == 3) {
    viewScoreBoard();
  } else {
    cout << "Invalid input" << endl;
  }
  return 0;
}