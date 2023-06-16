#pragma once
#include "board.h"
#include <queue>
#include <unordered_map>

class A_star : public BoardStateBase {
    static int totalNodesVisited; // counter of roots

public:
    A_star();
    // Default constructor

    A_star(const vector<int>&);
    // Constructor with queen's positions as input
    // Takes a vector of integers representing the positions of queens on the board

    void resetTotalNodesVisited();
    // Resets the totalNodesVisited counter to 0
    // Sets the number of visited nodes (roots) to zero

    int getTotalNodesVisited() const;
    // Returns the total number of visited nodes (roots)
    // Retrieves the value of the totalNodesVisited counter

    friend vector<BoardStateBase> solve(const BoardStateBase&);
    // Friend function that implements the A* algorithm to solve the problem
    // Takes a reference to a BoardStateBase object as input and returns a vector of BoardStateBase objects
};
