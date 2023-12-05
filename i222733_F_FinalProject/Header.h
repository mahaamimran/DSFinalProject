#ifndef Header_h
#define Header_h
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <unistd.h>
#include <vector>

using namespace std;
struct Obstacle {
  char symbol;
  int obstaclePlace;
};
struct Coins {
  char symbol;
  int coinPlace;
  int scoreValue;
};
struct PowerUp {
  char symbol;
  int powerUpPlace;
};
struct Node {
  string name;
  int score;
  Node *left;
  Node *right;
  Node(string n, int s) : name(n), score(s), left(nullptr), right(nullptr) {}
};
Node *insert(Node *root, string name, int score) {
  if (root == nullptr) {
    return new Node(name, score);
  }

  if (score < root->score) {
    root->left = insert(root->left, name, score);
  } else if (score > root->score) {
    root->right = insert(root->right, name, score);
  }

  return root;
}
void inOrderTraversal(Node *root) {
  if (root != nullptr) {
    inOrderTraversal(root->left);
    cout << root->name << "\t" << root->score << endl;
    inOrderTraversal(root->right);
  }
}
class Graph {
  int V;
  list<pair<int, int> > *adjList;

public:
  Graph() : V(0), adjList(nullptr) {}
  Graph(int v) : V(v) { adjList = new list<pair<int, int> >[V]; }
  int getV() { return V; }
  void setV(int v) { V = v; }
  list<pair<int, int> > *getAdjList() { return adjList; }
  void setAdjList(list<pair<int, int> > *adjlist) { adjList = adjlist; }
  void addEdge(int u, int v, int weight = 0, bool bidir = true) {
    adjList[u].push_back(make_pair(v, weight));
    if (bidir)
      adjList[v].push_back(make_pair(u, weight));
  }
  bool doesEdgeExist(int u, int v) {
    for (auto i : adjList[u]) {
      if (i.first == v) {
        return true;
      }
    }
    return false;
  }
  int getWeight(int u, int v) {
    for (auto i : adjList[u]) {
      if (i.first == v) {
        return i.second;
      }
    }
    return 0;
  }

  vector<int> dijkstrasAlgorithm(int source, int destination) {
    std::vector<int> dist(V, INT_MAX); // Initialize distances to infinity
    std::vector<int> parent(V, -1);    // Initialize parent pointers
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >,
                        std::greater<std::pair<int, int> > >
        pq;

    dist[source] = 0; // Distance from source to source is 0
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      for (auto neighbor : adjList[u]) {
        int v = neighbor.first;
        int weight = neighbor.second;

        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          parent[v] = u;
          pq.push(std::make_pair(dist[v], v));
        }
      }
    }

    // Reconstruct the path from source to destination
    std::vector<int> path;
    int vertex = destination;
    while (vertex != -1) {
      path.push_back(vertex);
      vertex = parent[vertex];
    }
    std::reverse(path.begin(), path.end());

    return path;
  }
  void clear() {
    for (int i = 0; i < V; i++) {
      adjList[i].clear();
    }
  }
  vector<int> findPath(int source, int destination) {
    vector<int> path;

    // Create a queue for BFS
    queue<int> queue;

    // Create a vector to store the parent of each vertex
    vector<int> parent(V, -1);

    // Create a vector to store whether a vertex has been visited or not
    vector<bool> visited(V, false);

    // Mark the source vertex as visited and enqueue it
    visited[source] = true;
    queue.push(source);

    // Run BFS until the queue is empty
    while (!queue.empty()) {
      // Dequeue a vertex from the queue
      int vertex = queue.front();
      queue.pop();

      // Get all adjacent vertices of the dequeued vertex vertex
      for (auto neighbor : adjList[vertex]) {
        // If a adjacent has not been visited, then mark it visited and enqueue
        // it
        if (!visited[neighbor.first]) {
          visited[neighbor.first] = true;
          queue.push(neighbor.first);
          parent[neighbor.first] = vertex;
        }
      }
    }
    // Check if there is a path from the source to the destination
    if (visited[destination]) {
      // Traverse the path and store it in the vector 'path'
      int vertex = destination;
      while (vertex != -1) {
        path.push_back(vertex);
        vertex = parent[vertex];
      }

      // Reverse the path vector
      reverse(path.begin(), path.end());
    }

    return path;
  }
  ~Graph() { delete[] adjList; }
};
class Car {
  char symbol;
  int carPlace;

public:
  Car() : symbol('C'), carPlace(0) {}
  Car(char s, int c) : symbol(s), carPlace(c) {}
  void setCarSymbol(char s) { symbol = s; }
  char getCarSymbol() { return symbol; }
  int getCarPlace() { return carPlace; }
  void setCarPlace(int c) { carPlace = c; }
  void checkForItems(Graph &g, int carPlace, list<Obstacle> &obstacles,
                     list<Coins> &coins, list<PowerUp> &powerUps, int &score) {}
  void moveUp(Graph &g, int rows, int cols, int &score,
              list<Obstacle> &obstacles, list<Coins> &coins,
              list<PowerUp> &powerUps) {
    system("clear");
    if (carPlace - cols < 0) {
      cout << "Can't move up" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace - cols)) {
        carPlace -= cols;
        // checkForItems(g, obstacles, coins, score);
        checkForLastVertex(g, carPlace, score);
      } else {
        cout << "Can't move up" << endl;
      }
    }
  }

  void moveDown(Graph &g, int rows, int cols, int &score,
                list<Obstacle> &obstacles, list<Coins> &coins,
                list<PowerUp> &powerUps) {
    system("clear");
    if (carPlace + cols >= rows * cols) {
      cout << "Can't move down" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace + cols)) {
        carPlace += cols;
        // checkForItems(g, obstacles, coins, score);
        checkForLastVertex(g, carPlace, score);
      } else {
        cout << "Can't move down" << endl;
      }
    }
  }

  void moveLeft(Graph &g, int rows, int cols, int &score,
                list<Obstacle> &obstacles, list<Coins> &coins,
                list<PowerUp> &powerUps) {
    system("clear");
    if (carPlace % cols == 0) {
      cout << "Can't move left" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace - 1)) {
        carPlace--;
        checkForItems(g, carPlace, obstacles, coins, powerUps, score);
        checkForLastVertex(g, carPlace, score);
      } else {
        cout << "Can't move left" << endl;
      }
    }
  }

  void moveRight(Graph &g, int rows, int cols, int &score,
                 list<Obstacle> &obstacles, list<Coins> &coins,
                 list<PowerUp> &powerUps) {
    system("clear");
    if (carPlace % cols == cols - 1) {
      cout << "Can't move right" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace + 1)) {
        carPlace++;
        checkForItems(g, carPlace, obstacles, coins, powerUps, score);
        checkForLastVertex(g, carPlace, score);
      } else {
        cout << "Can't move right" << endl;
      }
    }
  }
  void moveCar(Graph &g, char direction, int rows, int cols, int &score,
               list<Obstacle> &obstacles, list<Coins> &coins,
               list<PowerUp> &powerUps) {
    switch (direction) {
    case 'a':
      moveLeft(g, rows, cols, score, obstacles, coins, powerUps);
      break;
    case 'w':
      moveUp(g, rows, cols, score, obstacles, coins, powerUps);
      break;
    case 's':
      moveDown(g, rows, cols, score, obstacles, coins, powerUps);
      break;
    case 'd':
      moveRight(g, rows, cols, score, obstacles, coins, powerUps);
      break;
    default:
      cout << "Invalid input" << endl;
    }
  }

  void checkForLastVertex(Graph &g, int carPlace, int &score) {
    int lastVertex = g.getV() - 1;
    if (carPlace == lastVertex) {
      cout << "Congratulations! You reached the finish line. Game Over!"
           << endl;
      cout << "Your final score: " << score << endl;
      // Add any other end-of-game logic as needed
      exit(0); // Terminate the program
    }
  }
};
void generateCoins(Graph &g, int rows, int columns, list<Coins> &coins) {
  srand(int(time(0)));
  int totalVertices = rows * columns;
  int numCoins = rand() % (totalVertices / 2);
  for (int i = 0; i < numCoins; i++) {
    int coinPlace = rand() % totalVertices;
    int scoreValue = rand() % 10 + 1;
    Coins coin;
    coin.coinPlace = coinPlace;
    coin.scoreValue = scoreValue;
    coin.symbol = 'O';
    coins.push_back(coin);
  }
}
void generateObstacles(Graph &g, int rows, int columns,
                       list<Obstacle> &obstacles) {
  srand(int(time(0)));
  int totalVertices = rows * columns;
  int numObstacles = rand() % (totalVertices / 2);
  for (int i = 0; i < numObstacles; i++) {
    int obstaclePlace = rand() % totalVertices;
    Obstacle obstacle;
    obstacle.obstaclePlace = obstaclePlace;
    obstacle.symbol = 'B';
    obstacles.push_back(obstacle);
  }
}
void generatePowerUps(Graph &g, int rows, int columns,
                      list<PowerUp> &powerups) {
  srand(int(time(0)));
  int totalVertices = rows * columns;
  int numPowerUps = rand() % (totalVertices / 2);
  for (int i = 0; i < numPowerUps; i++) {
    int powerUpPlace = rand() % totalVertices;
    PowerUp powerup;
    powerup.powerUpPlace = powerUpPlace;
    powerup.symbol = 'P';
    powerups.push_back(powerup);
  }
}
bool isPlaceTakenByCoins(int position, const list<Coins> &items) {
  for (const auto &item : items) {
    if (item.coinPlace == position) { // Adjust the comparison based on the
                                      // actual structure of your items
      return true;
    }
  }
  return false;
}
bool isPlaceTakenByObstacles(int position, const list<Obstacle> &items) {
  for (const auto &item : items) {
    if (item.obstaclePlace == position) { // Adjust the comparison based on the
                                          // actual structure of your items
      return true;
    }
  }
  return false;
}
bool isPlaceTakenByPowerUps(int position, const list<PowerUp> &items) {
  for (const auto &item : items) {
    if (item.powerUpPlace == position) { // Adjust the comparison based on the
                                         // actual structure of your items
      return true;
    }
  }
  return false;
}
void display(Graph &g, int rows, int columns, Car &car, list<Coins> &coins,
             list<Obstacle> &obstacles, list<PowerUp> &powerUps, int score) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int u = i * columns + j;
      int v = i * columns + j + 1;

      // Check if the current position is occupied by the car
      if (u == car.getCarPlace()) {
        cout << car.getCarSymbol();
      } else if (isPlaceTakenByCoins(u, coins)) {
        cout << "O";
      } else if (isPlaceTakenByObstacles(u, obstacles)) {
        cout << "B";
      } else if (isPlaceTakenByPowerUps(u, powerUps)) {
        cout << "P";
      } else {
        cout << "x";
      }

      if (j != columns - 1) {
        if (g.doesEdgeExist(u, v)) {
          cout << "--";
        } else {
          cout << "  ";
        }
      }
    }
    cout << endl;

    if (i != rows - 1) {
      for (int j = 0; j < columns; j++) {
        int u = i * columns + j;
        int v = (i + 1) * columns + j;

        if (g.doesEdgeExist(u, v)) {
          cout << "|";
        } else {
          cout << " ";
        }

        if (j != columns - 1) {
          cout << "  ";
        }
      }
    }
    cout << endl;
  }
}
void generateMap(Graph &g, int rows, int columns) {
  // this function generates a random map and adds edges bertween vertices
  srand(int(time(0)));
  int totalVertices = rows * columns;
  bool pathFound = false;
  while (!pathFound) {
    g.clear();
    // Create a graph with 'totalVertices' vertices
    for (int i = 0; i < totalVertices; i++) {
      int vertex = i;
      vector<int> neighbors;
      // Check if there is a neighbor to the left
      if (vertex % columns != 0) {
        int leftNeighbor = vertex - 1;
        neighbors.push_back(leftNeighbor);
      }
      // Check if there is a neighbor to the right
      if (vertex % columns != columns - 1) {
        int rightNeighbor = vertex + 1;
        neighbors.push_back(rightNeighbor);
      }
      // Check if there is a neighbor above
      if (vertex >= columns) {
        int topNeighbor = vertex - columns;
        neighbors.push_back(topNeighbor);
      }
      // Check if there is a neighbor below
      if (vertex < totalVertices - columns) {
        int bottomNeighbor = vertex + columns;
        neighbors.push_back(bottomNeighbor);
      }
      // Randomly shuffle the neighbors vector
      // for xcode
      random_device rd;
      mt19937 gr(rd());
      shuffle(neighbors.begin(), neighbors.end(), gr);
      // random_shuffle(neighbors.begin(), neighbors.end());
      // Select a random number of neighbors to connect
      int numPaths = rand() % (neighbors.size() + 1);
      for (int j = 0; j < numPaths; j++) {
        int neighbor = neighbors[j];
        int weight = 2; // Set a fixed weight for the path
        g.addEdge(vertex, neighbor, weight);
      }
    }
    // Check if there is a path from the top left corner to the bottom right
    // corner
    vector<int> path = g.findPath(0, totalVertices - 1);
    if (!path.empty()) {
      pathFound = true;
    }
  }
}
#endif /* Header_h */