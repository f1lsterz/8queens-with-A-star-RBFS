#include "RBFS.h"

int RBFS_alg::totalNodesVisited = 0;

void RBFS_alg::resetTotalNodesVisited() {
    totalNodesVisited = 0;
}

int RBFS_alg::getTotalNodesVisited() const {
    return totalNodesVisited;
}

RBFS_alg::RBFS_alg(const vector<int>& queens) : BoardStateBase(queens) {}

bool RBFS(const BoardStateBase& currentState, int gValue, int fLimit, int recursionCount, std::vector<BoardStateBase>& solution, std::unordered_set<BoardStateBase>& visitedStates) {
    if (visitedStates.find(currentState) != visitedStates.end()) {
        RBFS_alg::totalNodesVisited--;
        return false;
    }

    visitedStates.insert(currentState);

    if (currentState.calculateHeuristic() == 0) {
        solution.push_back(currentState);
        return true;
    }

    if (recursionCount >= MAX_RECURSION || gValue + currentState.calculateHeuristic() > fLimit) {
        RBFS_alg::totalNodesVisited--;
        return false;
    }

    std::vector<BoardStateBase> successors = currentState.getNextStates();

    std::sort(successors.begin(), successors.end(), [](const BoardStateBase& a, const BoardStateBase& b) {
        return a.calculateHeuristic() < b.calculateHeuristic();
        });

    for (const BoardStateBase& successor : successors) {
        RBFS_alg::totalNodesVisited++;
        int newGValue = gValue + 1;

        if (visitedStates.find(successor) != visitedStates.end()) {
            RBFS_alg::totalNodesVisited--;
            continue;
        }

        int newFLimit = std::max(fLimit, successor.calculateHeuristic() + newGValue);

        std::vector<BoardStateBase> currentSolution;
        bool result = RBFS(successor, newGValue, newFLimit, recursionCount + 1, currentSolution, visitedStates);
        if (result) {
             solution.push_back(currentState);
             solution.insert(solution.end(), currentSolution.begin(), currentSolution.end());
             return true;
        }
    }
    return false;
}