#pragma once
#include <unordered_set>
#include "board.h"
#include <algorithm>
#include <queue>
#include <set>

class RBFS_alg : public BoardStateBase {
    static int totalNodesVisited; // counter of roots

public:
    // Constructor that takes a vector of queen's positions as input
    RBFS_alg(const vector<int>&);

    // Reset the counter for the total number of nodes visited
    void resetTotalNodesVisited();

    // Get the total number of nodes visited
    int getTotalNodesVisited() const;

    // Friend function declaration for the RBFS algorithm
    friend bool RBFS(const BoardStateBase&, int, int, int, vector<BoardStateBase>&, unordered_set<BoardStateBase>&);
};