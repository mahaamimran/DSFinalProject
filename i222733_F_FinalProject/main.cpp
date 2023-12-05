#include "Header.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <unistd.h>
#include <iomanip>
using namespace std;
void manualMode(Graph&g,int rows,int columns,Car&car,int&score,list<Obstacle>&obstacles,list<Coins>&coins,list<PowerUp>&powerups){
  char c;
  display(g,rows,columns,car,coins,obstacles,powerups,score);
  cout<<"Press A,W,S or D to move the car\nPress Q to quit\n";
  while(true){
    car.displaySteps();
    cin>>c;
    if(c=='a'||c=='w'||c=='s'||c=='d'){
      car.moveCar(g,c,rows,columns,score,obstacles,coins,powerups);
      display(g,rows,columns,car,coins,obstacles,powerups,score);
    }
    else if(c=='q')break;
    else cout<<"Invalid input\n";
  }
}
void autoMode(Graph&g,int rows,int columns,Car&car,list<Obstacle>&obstacles,int&score,list<Coins>&coins,list<PowerUp>&powerUps,vector<int>path){
    cout<<"Shortest Path using dijkstra's algorthm: ";
    for(int i=0; i < path.size(); i++)cout<<path[i]<<" ";
    cout<<endl;
    display(g,rows,columns,car,coins,obstacles,powerUps,score);
    sleep(1);
    // iterate over the path
    for(int i=0;i<path.size()-1;i++){
      system("clear");
      int currentVertex=path[i];
      int nextVertex=path[i + 1];
      char direction=g.findDirection(currentVertex,nextVertex,rows,columns);
      car.moveCar(g,direction,rows,columns,score,obstacles,coins,powerUps);
      display(g,rows,columns,car,coins,obstacles,powerUps,score);
      sleep(1); 
    }
}
void writeToFile(string name,int score){
  fstream fout;
  string filePath="/Users/mahamimran/teesra semester/DS/i222733_F_FinalProject/scoreBoard.csv";
  fout.open(filePath,ios::app);
  fout<<name<<","<<score<<endl;
  fout.close();
}
void viewScoreBoard(){
  // read the scores from the csv and insert them into bst
  string filePath="/Users/mahamimran/teesra semester/DS/i222733_F_FinalProject/scoreBoard.csv";
  ifstream fin(filePath);
  string line;
  NodeBST*root=nullptr;
  while(getline(fin,line)){
    size_t pos=line.find(',');
    if(pos!=string::npos){
      string name=line.substr(0,pos);
      string scoreStr=line.substr(pos + 1);
      int score=stoi(scoreStr);
      root=insert(root,name,score);
    }
  }
  cout<<"Name\tScore\n";
  cout<<"-------------\n";
  inOrderTraversal(root);
  fin.close();
}
void displayAllQueues(){
  // displaying all the queues at the end of the game
  cout<<"Coins: ";
  collectedCoins.display();
  cout<<"Obstacles: ";
  collectedObstacles.display();
  cout<<"PowerUps: ";
  collectedPowerUps.display();
  cout<<endl;
}
int main(){
  Car car;
  // initial obstacles to put in graph
  list<Obstacle>obstacles;
  list<Coins>coins;
  list<PowerUp>powerups;

  char c;
  int score=0;
  int rows=6,columns=6;
  int vertices=rows*columns;
  int carPlace=0;
  Graph g(vertices);

  // generating edges randomly and finding shortest path
  generateMap(g,rows,columns);
  vector<int>path=g.dijkstrasAlgorithm(0,vertices - 1);

  // generating coins obstacles and powerups
  generateItems(g,rows,columns,coins,obstacles,powerups);

  system("clear");
  cout<<"MAIN MENU\n";
  cout<<"--------------\n";
  cout<<"Which mode would you like to select?\n1. Manual\n2. Auto\n--------------\n3. View Scoreboard\n";
  int mode;cin>>mode;

  if(mode==1){
    cout<<"Enter your name: ";
    string name;
    cin>>name;
    system("clear");
    manualMode(g,rows,columns,car,score,obstacles,coins,powerups);
    writeToFile(name,score);
    cout<<"Game Over "<<name<<"! Your score is: "<<score<<endl;
    cout<<"Everything you collected\n";
    displayAllQueues();
  } 
  else if(mode==2){
    system("clear");
    string name="Robot";
    autoMode(g,rows,columns,car,obstacles,score,coins,powerups,path);
    writeToFile(name,score);
    cout<<"Game Over "<<name<<"! Your score is: "<<score<<endl;
    cout<<"Everything you collected\n";
    displayAllQueues();
  } 
  else if(mode==3)viewScoreBoard();
  else cout<<"Invalid input\n";
  
  return 0;
}