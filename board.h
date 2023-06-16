#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"

using namespace std;
using namespace constants;

class BoardStateBase {
protected:
    vector<int> queens; // Stores the positions of the queens on the board

public:
    BoardStateBase() {} // Default constructor

    BoardStateBase(const vector<int>&); // Constructor that takes a vector of queen positions

    // Checks if a pair of queens at given positions is attacking each other
    bool isAttacking(int, int, int, int) const;

    // Checks if the current state is a goal state (all queens are non-attacking)
    bool isGoalState() const;

    // Calculates the heuristic value of the current state (a measure of how close it is to the goal state)
    int calculateHeuristic() const;

    // Returns a reference to the vector of queen positions
    const vector<int>& getQueens() const;

    // Sets the vector of queen positions
    void setQueens(const vector<int>&);

    // Generates and returns a vector of all possible next states from the current state
    vector<BoardStateBase> getNextStates() const;

    // Overloads the equality operator to compare two board states
    bool operator==(const BoardStateBase&) const;

    // Overloads the less-than operator to define a strict weak ordering for board states
    bool operator<(const BoardStateBase&) const;
};

// Specialization of the hash template for BoardStateBase class, used for unordered containers
template<>
struct hash<BoardStateBase> {
    size_t operator()(const BoardStateBase& state) const {
        size_t hashVal = 0;
        const vector<int>& queens = state.getQueens();

        // Generates a hash value based on the positions of the queens
        for (int i = 0; i < QUEENS_SIZE; i++) {
            hashVal ^= hash<int>()(queens[i]);
        }

        return hashVal;
    }
};