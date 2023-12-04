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
struct Node{
    int data;
    Node*next;
};
class LinkedList{
    Node*head;
    int size;
public:
    LinkedList():head(nullptr),size(0){}
    void insert(int data){
      if(head==nullptr){
          head=new Node;
          head->data=data;
          head->next=nullptr;
      }
      else{
        Node*newNode=new Node;
        newNode->data=data;
        newNode->next=nullptr;
      }
    }
};
struct Obstacle {
  char symbol;
  int obstaclePlace;
};
struct Coins{
    char symbol;
    int coinPlace;
    int scoreValue;
    int scoleValueBasedOnSymbol(char symbol){
      if(symbol=='w')scoreValue=10;
      else if(symbol=='V')scoreValue=20;
      else if(symbol=='W')scoreValue=30;
      else scoreValue=0;
      return scoreValue; 
    }
};
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
  void moveCar(Graph &g, char direction, int rows, int cols, list<Obstacle> &obstacles,int score, queue<Obstacle>&obstaclesQueue) {
  system("clear");
  if (direction == 'a') {
    if (carPlace % cols == 0) {
      cout << "Can't move left" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace - 1)) {
        // Check if the car will collide with an obstacle
        auto it = obstacles.begin();
        while (it != obstacles.end()) {
          if (carPlace - 1 == it->obstaclePlace) {
            cout << "You hit an obstacle!" << endl;
            // enqueue the obstacle in a queue of obstacles
            obstaclesQueue.push(*it);
            it = obstacles.erase(it); // Remove the obstacle from the list
            break;
          } else {
            ++it;
          }
        }
        carPlace--;
      } else {
        cout << "Can't move left" << endl;
      }
    }
  } else if (direction == 'w') {
    if (carPlace - cols < 0) {
      cout << "Can't move up" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace - cols)) {
        // Check if the car will collide with an obstacle
        auto it = obstacles.begin();
        while (it != obstacles.end()) {
          if (carPlace - cols == it->obstaclePlace) {
            cout << "You hit an obstacle!\n";
            // enqueue the obstacle in a queue of obstacles

            it = obstacles.erase(it); // Remove the obstacle from the list
            break;
          } else {
            ++it;
          }
        }
        carPlace -= cols;
      } else {
        cout << "Can't move up" << endl;
      }
    }
  } else if (direction == 's') {
    if (carPlace + cols >= rows * cols) {
      cout << "Can't move down" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace + cols)) {
        // Check if the car will collide with an obstacle
        auto it = obstacles.begin();
        while (it != obstacles.end()) {
          if (carPlace + cols == it->obstaclePlace) {
            cout << "You hit an obstacle!" << endl;
            it = obstacles.erase(it); // Remove the obstacle from the list
            break;
          } else {
            ++it;
          }
        }
        carPlace += cols;
      } else {
        cout << "Can't move down" << endl;
      }
    }
  } else if (direction == 'd') {
    if (carPlace % cols == cols - 1) {
      cout << "Can't move right" << endl;
    } else {
      if (g.doesEdgeExist(carPlace, carPlace + 1)) {
        // Check if the car will collide with an obstacle
        auto it = obstacles.begin();
        while (it != obstacles.end()) {
          if (carPlace + 1 == it->obstaclePlace) {
            cout << "You hit an obstacle!" << endl;
            it = obstacles.erase(it); // Remove the obstacle from the list
            break;
          } else {
            ++it;
          }
        }
        carPlace++;
      } else {
        cout << "Can't move right" << endl;
      }
    }
  }
}
};
void display(Graph &g, int rows, int columns, Car &car, list<Obstacle> &obstacles, int score) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int u = i * columns + j;
      int v = i * columns + j + 1;
      
      // Check if the current position is occupied by the car
      if (u == car.getCarPlace()) {
        cout << car.getCarSymbol();
      }
      else {
        bool obstacleFound = false;
        for (auto obstacle : obstacles) {
          if (u == obstacle.obstaclePlace) {
            cout << obstacle.symbol;
            obstacleFound = true;
            break;
          }
        }
        if (!obstacleFound) {
          cout << "x";
        }
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
void generateObstacles(list<Obstacle>& obstacles, int rows, int columns, vector<int>& path, int numofObstacles = 4) {
    // Exclude the 0th vertex from the possible obstacle placement
    vector<int> validPath = path;
    auto it = find(validPath.begin(), validPath.end(), 0);
    if (it != validPath.end()) {
        validPath.erase(it);
    }

    // Enqueue obstacles in the list
    for (int i = 0; i < numofObstacles; i++) {
        // Place obstacles in validPath
        int obstaclePlace = validPath[rand() % validPath.size()];
        Obstacle obstacle;
        obstacle.obstaclePlace = obstaclePlace;
        obstacle.symbol = 'O';
        obstacles.push_back(obstacle);
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