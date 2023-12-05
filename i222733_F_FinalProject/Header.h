#ifndef Header_h
#define Header_h
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <random>
#include <unistd.h>
#include <vector>
#include <set>
#include <queue> // only used in dijkstrasAlgorithm

using namespace std;
struct Obstacle {
  char symbol;
  int obstaclePlace;
  // overloading the << operator
  friend ostream &operator<<(ostream &os, const Obstacle &obstacle) {
    os << obstacle.symbol;
    return os;
  }
};
struct Coins {
  char symbol;
  int coinPlace;
  // overloading the << operator
  friend ostream &operator<<(ostream &os, const Coins &coin) {
    os << coin.symbol;
    return os;
  }
};
struct PowerUp {
  char symbol;
  int powerUpPlace;
  // overloading the << operator
  friend ostream &operator<<(ostream &os, const PowerUp &powerUp) {
    os << powerUp.symbol;
    return os;
  }
};

template <typename Type>
struct NodeLinkedList{
  Type data;
  NodeLinkedList *next;
};
template <typename Type>
class LinkedList{
  NodeLinkedList<Type> *head;
  int size;
public:
  LinkedList():head(nullptr), size(0){}
  void insert(Type data){
    NodeLinkedList<Type> *newNode = new NodeLinkedList<Type>;
    newNode->data = data;
    newNode->next = nullptr;
    if(head == nullptr){
      head = newNode;
    }
    else{
      NodeLinkedList<Type> *temp = head;
      while(temp->next != nullptr){
        temp = temp->next;
      }
      temp->next = newNode;
    }
    size++;
  }
  void display(){
    NodeLinkedList<Type> *temp = head;
    while(temp != nullptr){
      cout << temp->data << endl;
      temp = temp->next;
    }
  }
  int getSize(){
    return size;
  }
  ~LinkedList(){
    NodeLinkedList<Type> *temp = head;
    while(temp != nullptr){
      NodeLinkedList<Type> *next = temp->next;
      delete temp;
      temp = next;
    }
  }
};
template <typename Type>
struct NodeQueue{
  Type data;
  NodeQueue *next;
};
template <typename Type>
class Queue{
  NodeQueue<Type> *front;
  NodeQueue<Type> *rear;
  int size;
public:
  Queue():front(nullptr), rear(nullptr), size(0){}
  void push(Type data){
    NodeQueue<Type> *newNode = new NodeQueue<Type>;
    newNode->data = data;
    newNode->next = nullptr;
    if(front == nullptr){
      front = newNode;
      rear = newNode;
    }
    else{
      rear->next = newNode;
      rear = newNode;
    }
    size++;
  }
  void pop(){
    if(front == nullptr){
      cout << "Queue is empty" << endl;
    }
    else{
      NodeQueue<Type> *temp = front;
      front = front->next;
      delete temp;
      size--;
    }
  }
  Type getFront(){
    return front->data;
  }
  Type getRear(){
    return rear->data;
  }
  int getSize(){
    return size;
  }
  bool isEmpty(){
    return size == 0;
  }
  void display(){
    NodeQueue<Type> *temp = front;
    while(temp != nullptr){
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }
  ~Queue(){
    NodeQueue<Type> *temp = front;
    while(temp != nullptr){
      NodeQueue<Type> *next = temp->next;
      delete temp;
      temp = next;
    }
  }
};
struct NodeBST {
  string name;
  int score;
  NodeBST *left;
  NodeBST *right;
  NodeBST(string n, int s) : name(n), score(s), left(nullptr), right(nullptr) {}
};
NodeBST *insert(NodeBST *root, string name, int score) {
  if (root == nullptr) {
    return new NodeBST(name, score);
  }

  if (score < root->score) {
    root->left = insert(root->left, name, score);
  } else if (score > root->score) {
    root->right = insert(root->right, name, score);
  }

  return root;
}
void inOrderTraversal(NodeBST *root) {
  if (root != nullptr) {
    inOrderTraversal(root->left);
    cout << root->name << "\t" << root->score << endl;
    inOrderTraversal(root->right);
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
Queue<Coins> collectedCoins;
Queue<Obstacle> collectedObstacles;
Queue<PowerUp> collectedPowerUps;
bool isPlaceTakenByObstacles(int position, const list<Obstacle> &items) {
  for (const auto &item : items) {
    if (item.obstaclePlace == position) { // Adjust the comparison based on the
                                          // actual structure of your items
      return true;
    }
  }
  return false;
}
bool isPlaceTakenByPowerUps(int position, list<PowerUp>& powerUps){
  for (const auto &powerUps : powerUps) {
    if (powerUps.powerUpPlace == position) { // Adjust the comparison based on the
                                         // actual structure of your items
      return true;
    }
  }
  return false;
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
  char findDirection(int currentVertex,int nextVertex,int rows,int columns){
    char direction;
    if(nextVertex == currentVertex + 1){
      direction = 'd';
    }
    else if(nextVertex == currentVertex - 1){
      direction = 'a';
    }
    else if(nextVertex == currentVertex + columns){
      direction = 's';
    }
    else if(nextVertex == currentVertex - columns){
      direction = 'w';
    }
    return direction;
  }
  vector<int> dijkstrasAlgorithm(int source, int destination) {
    vector<int> dist(V, INT_MAX); // Initialize distances to infinity
    vector<int> parent(V, -1);    // Initialize parent pointers
    priority_queue<pair<int, int>, vector<pair<int, int> >,
                        greater<pair<int, int> > >
        pq;

    dist[source] = 0; // Distance from source to source is 0
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      for (auto neighbor : adjList[u]) {
        int v = neighbor.first;
        int weight = neighbor.second;

        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          parent[v] = u;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    // Reconstruct the path from source to destination
    vector<int> path;
    int vertex = destination;
    while (vertex != -1) {
      path.push_back(vertex);
      vertex = parent[vertex];
    }
    reverse(path.begin(), path.end());

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
    Queue<int> queue;

    // Create a vector to store the parent of each vertex
    vector<int> parent(V, -1);

    // Create a vector to store whether a vertex has been visited or not
    vector<bool> visited(V, false);

    // Mark the source vertex as visited and enqueue it
    visited[source] = true;
    queue.push(source);

    // Run BFS until the queue is empty
    while (!queue.isEmpty()) {
      // Dequeue a vertex from the queue
      int vertex = queue.getFront();
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
  int stepsTaken;
public:
  Car() : symbol('C'), carPlace(0), stepsTaken(0) {}
  Car(char s, int c, int st) : symbol(s), carPlace(c), stepsTaken(st) {}
  void setCarSymbol(char s) { symbol = s; }
  char getCarSymbol() { return symbol; }
  int getCarPlace() { return carPlace; }
  void setCarPlace(int c) { carPlace = c; }
  int getStepsTaken() { return stepsTaken; }
  void setStepsTaken(int st) { stepsTaken = st; }
  void checkForItems(Graph &g, int carPlace, list<Obstacle> &obstacles,
                     list<Coins> &coins, list<PowerUp> &powerUps, int &score) {}
  void moveUp(Graph &g, int rows, int cols, int &score,list<Obstacle> &obstacles, list<Coins> &coins,list<PowerUp> &powerUps) {
    system("clear");
    int newCarPlace = carPlace - cols;
    if (newCarPlace < 0) {
        cout << "Can't move up" << endl;
    } else {
        if (g.doesEdgeExist(carPlace, newCarPlace)) {
            checkForCollision(g, newCarPlace, score, obstacles, coins, powerUps);
            carPlace = newCarPlace;
            checkForLastVertex(g, carPlace, score);
            stepsTaken++;
        } else {
            cout << "Can't move up" << endl;
        }
    }
}

void moveDown(Graph &g, int rows, int cols, int &score,list<Obstacle> &obstacles, list<Coins> &coins,list<PowerUp> &powerUps) {
    system("clear");
    int newCarPlace = carPlace + cols;

    if (newCarPlace >= rows * cols) {
        cout << "Can't move down" << endl;
    } else {
        if (g.doesEdgeExist(carPlace, newCarPlace)) {
            checkForCollision(g, newCarPlace, score, obstacles, coins, powerUps);
            carPlace = newCarPlace;
            checkForLastVertex(g, carPlace, score);
            stepsTaken++;
        } else {
            cout << "Can't move down" << endl;
        }
    }
}

void moveLeft(Graph &g, int rows, int cols, int &score,
              list<Obstacle> &obstacles, list<Coins> &coins,
              list<PowerUp> &powerUps) {
    system("clear");
    int newCarPlace = carPlace - 1;

    if (carPlace % cols == 0) {
        cout << "Can't move left" << endl;
    } else {
        if (g.doesEdgeExist(carPlace, newCarPlace)) {
            checkForCollision(g, newCarPlace, score, obstacles, coins, powerUps);
            carPlace = newCarPlace;
            checkForLastVertex(g, carPlace, score);
            stepsTaken++;
        } else {
            cout << "Can't move left" << endl;
        }
    }
}

void moveRight(Graph &g, int rows, int cols, int &score,
               list<Obstacle> &obstacles, list<Coins> &coins,
               list<PowerUp> &powerUps) {
    system("clear");
    int newCarPlace = carPlace + 1;

    if (newCarPlace % cols == 0) {
        cout << "Can't move right" << endl;
    } else {
        if (g.doesEdgeExist(carPlace, newCarPlace)) {
            checkForCollision(g, newCarPlace, score, obstacles, coins, powerUps);
            carPlace = newCarPlace;
            checkForLastVertex(g, carPlace, score);
            stepsTaken++;
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
void checkForCollision(Graph &g, int newCarPlace, int &score,
                       list<Obstacle> &obstacles, list<Coins> &coins,
                       list<PowerUp> &powerUps) {
    // Check for collision with obstacles
    if (isPlaceTakenByObstacles(newCarPlace, obstacles)) {
        cout << "You hit an obstacle! -10 to score" << endl;
        score -= 10;
        for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
            if (it->obstaclePlace == newCarPlace) {
                // adding it to the queue
                collectedObstacles.push(*it);
                obstacles.erase(it);
                break;
            }
        }
    }
    else if(isPlaceTakenByCoins(newCarPlace, coins)){
      // coinscorevalue taken from coins list
        cout << "You collected a coin! +10 to score" << endl;
        score += 10;
        // remove the coin from the list
        for (auto it = coins.begin(); it != coins.end(); it++) {
            if (it->coinPlace == newCarPlace) {
                // adding it to the queue
                collectedCoins.push(*it);
                coins.erase(it);
                break;
            }
        }
    }
    else if(isPlaceTakenByPowerUps(newCarPlace, powerUps)){
      // powerupscorevalue taken from powerups list
        cout << "You collected a powerup! +20 to score" << endl;
        score += 20;
        // remove the powerup from the list
        for (auto it = powerUps.begin(); it != powerUps.end(); it++) {
            if (it->powerUpPlace == newCarPlace) {
                // adding it to the queue
                collectedPowerUps.push(*it);
                powerUps.erase(it);
                break;
            }
        }
    }
    else {
        cout << "Race Car Game" << endl;
    }
}
  void checkForLastVertex(Graph &g, int carPlace, int &score) {
    int lastVertex = g.getV() - 1;
    if (carPlace == lastVertex) {
      cout << "Congratulations! You reached the finish line. Game Over!\n";
      cout<<"You scored "<<score<<" points!\n";
      cout<<"Press q to quit\n";
    }
  }
  void displaySteps() const {
    cout << "Number of steps taken: " << stepsTaken << endl;
  }
};
void generateItems(Graph &g, int rows, int cols, list<Coins> &coins, list<Obstacle> &obstacles, list<PowerUp> &powerups) {

    srand(time(0));

    int numCoins = 4;
    int numObstacles = 4;
    int numPowerups = 4;

    int totalLocations = rows * cols;

    // Track occupied locations
    set<int> occupied;

    // Generate coins
    for (int i = 0; i < numCoins; i++) {
        int loc;
        do {
            loc = rand() % totalLocations;
        } while (occupied.count(loc) || loc == 0 || loc == totalLocations - 1);

        occupied.insert(loc);

        Coins coin;
        coin.coinPlace = loc;
        coin.symbol = 'O';
        coins.push_back(coin);
    }

    // Generate obstacles
    for (int i = 0; i < numObstacles; i++) {
        int loc;
        do {
            loc = rand() % totalLocations;
        } while (occupied.count(loc) || loc == 0 || loc == totalLocations - 1);

        occupied.insert(loc);

        Obstacle obstacle;
        obstacle.obstaclePlace = loc;
        obstacle.symbol = 'B';
        obstacles.push_back(obstacle);
    }

    // Generate powerups
    for (int i = 0; i < numPowerups; i++) {
        int loc;
        do {
            loc = rand() % totalLocations;
        } while (occupied.count(loc) || loc == 0 || loc == totalLocations - 1);

        occupied.insert(loc);

        PowerUp powerup;
        powerup.powerUpPlace = loc;
        powerup.symbol = 'P';

        powerups.push_back(powerup);
    }
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
        cout << coins.front().symbol;
      } else if (isPlaceTakenByObstacles(u, obstacles)) {
        cout << obstacles.front().symbol;
      } else if (isPlaceTakenByPowerUps(u, powerUps)) {
        cout << powerUps.front().symbol;
      } else if (u == g.getV() - 1) {
        cout << 'F';
      }
      else {
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