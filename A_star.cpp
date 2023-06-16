#include "A_star.h"

int A_star::totalNodesVisited = 1;

void A_star::resetTotalNodesVisited() {
	totalNodesVisited = 1;
}

int A_star::getTotalNodesVisited() const {
	return totalNodesVisited;
}

A_star::A_star() : BoardStateBase() {}

A_star::A_star(const vector<int>& queens) : BoardStateBase(queens) {}

vector<BoardStateBase> solve(const BoardStateBase& initialState) {
	priority_queue<BoardStateBase> openSet;
	unordered_map<BoardStateBase, int> gScores; 
	unordered_map<BoardStateBase, BoardStateBase> cameFrom; 
	openSet.push(initialState);
	gScores[initialState] = 0;

	while (!openSet.empty()) {
		BoardStateBase current = openSet.top();
		openSet.pop();
		A_star::totalNodesVisited--;
		if (current.isGoalState()) {
			vector<BoardStateBase> solution;
			solution.push_back(current);
			while (cameFrom.count(current) > 0) {
				current = cameFrom[current];
				solution.push_back(current);
			}
			return solution;
		}

		vector<BoardStateBase> nextStates = current.getNextStates();
		for (const BoardStateBase& nextState : nextStates) {
			A_star::totalNodesVisited++;
			int newGScore = gScores[current] + 1;
			if (gScores.count(nextState) == 0 || newGScore < gScores[nextState]) {
				gScores[nextState] = newGScore;
				openSet.push(nextState);
				cameFrom[nextState] = current;
			}
		}
	}

	return vector<BoardStateBase>();
}