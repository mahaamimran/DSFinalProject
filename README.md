# Racing Car Game by Maham and Fatima

## Description

This is a simple racing car game developed by Maham and Fatima as a project. The game allows users to navigate a car through a maze, collect points, and reach the end. It features both manual and auto modes.

## Features

- **Manual Mode:** Users can control the car using the keys 'a', 'w', 's', and 'd'.
- **Auto Mode:** The game can run automatically, demonstrating the shortest path using Dijkstra's algorithm.
- **Scoring:** Players earn points by collecting coins and powerups, and lose points by encountering obstacles.
- **Scoreboard:** View the scoreboard to see the scores of different players.

## Structures
- Obstacle
- Coins
- PowerUp

## Queues
- collectedCoins
- collectedObstacles
- collectedPowerUps

## Node Structure
Node: Binary search tree (BST) node for storing player scores

## Functions
- insert: Inserts a new node into the BST.
- inOrderTraversal: Performs an in-order traversal of the BST.
- isPlaceTakenByCoins: Checks if a position is taken by coins.
- isPlaceTakenByObstacles: Checks if a position is taken by obstacles.
- isPlaceTakenByPowerUps: Checks if a position is taken by power-ups.

## Classes
- Graph: Represents the game map and provides graph-related functionalities.
- Car: Represents the player's car and provides movement and collision detection functionalities.

## Miscellaneous Functions
- generateItems: Generates coins, obstacles, and power-ups on the map.
- display: Displays the game map.
- generateMap: Generates a random map with connected paths.

## Compilation and Execution

Ensure you have a C++ compiler installed

## Dependencies
The game relies on standard C++ libraries. No additional dependencies are required.

## Authors
- Maham Imran
- Fatima Wajahat

## Scoreboard
Check the scoreBoard.csv file for the scores. The scoreboard is displayed in ascending order.
