#include "board.h"

BoardStateBase::BoardStateBase(const vector<int>& _queens) : queens(_queens) {}

const vector<int>& BoardStateBase::getQueens() const
{
    return queens;
}

void BoardStateBase::setQueens(const vector<int>& _queens) {
    queens = _queens;
}

bool BoardStateBase::isAttacking(int row1, int col1, int row2, int col2) const {
    return (row1 == row2) || (col1 == col2) || (abs(row1 - row2) == abs(col1 - col2));
}

bool BoardStateBase::isGoalState() const {
    for (int i = 0; i < QUEENS_SIZE; i++) {
        for (int j = i + 1; j < QUEENS_SIZE; j++) {
            if (isAttacking(i, queens[i], j, queens[j])) {
                return false;
            }
        }
    }
    return true;
}

int BoardStateBase::calculateHeuristic() const {
    int conflicts = 0;
    for (int i = 0; i < QUEENS_SIZE; i++) {
        for (int j = i + 1; j < QUEENS_SIZE; j++) {
            if (isAttacking(i, queens[i], j, queens[j])) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

vector <BoardStateBase> BoardStateBase::getNextStates() const {
    vector<BoardStateBase> nextStates;
    for (int i = 0; i < QUEENS_SIZE; i++) {
        for (int j = 0; j < QUEENS_SIZE; j++) {
            if (queens[i] != j) {
                BoardStateBase successor = *this;
                successor.queens[i] = j;
                nextStates.push_back(successor);
            }
        }
    }

    return nextStates;
}

bool BoardStateBase::operator==(const BoardStateBase& other) const {
    return queens == other.queens;
}

bool BoardStateBase::operator<(const BoardStateBase& other) const {
    return calculateHeuristic() > other.calculateHeuristic();
}
