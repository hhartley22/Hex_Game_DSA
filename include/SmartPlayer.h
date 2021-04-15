/*
 * SmartPlayer.h
 *
 *  Created on: 13/04/2021
 *      Author: Hayden Hartley
 */
#ifndef ASSIGNMENT1_SMARTPLAYER_H
#define ASSIGNMENT1_SMARTPLAYER_H

#include <queue>
#include <stack>

#include "Move.h"
#include "Node.h"
#include "Cell.h"

using namespace std;

class SmartPlayer : public Player {
private:
	int steps;
	double minMove(Board *board, int level);
	double maxMove(Board *board, int level);
	double evaluateBoard(Board *board);
	bool nodeVisited(Node node, list<Node> &list);
	void printStack(stack<Node> stack);
public:
	SmartPlayer(int type, string playerName = "Smart");
	bool getMove(Board *board, int &x, int &y);
};

SmartPlayer::SmartPlayer(int type, string playerName) : Player(type, playerName) {
	//EMPTY CONSTRUCTOR
}

bool SmartPlayer::getMove(Board *board, int &x, int &y) {

	priority_queue<Move> moves;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//Copy board
			Board tmpBoard(*board);
			if (tmpBoard.addMove(type ,i, j)) {
				//If move makes player win then set move
				if (tmpBoard.checkWinningStatus(type)) {
					x = i;
					y = j;
					return true;
				}

				steps = 3;
				double moveUtility = minMove(&tmpBoard, steps);
				Move move{i, j, moveUtility};
				moves.push(move);
			} else {
				continue;
			}
		}
	}

	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		cout << "MiniMax Utility = " << moves.top().heuristic << " at (" << x << ", " << y << ")" << endl;
	}

	return true;
}

double SmartPlayer::maxMove(Board *board, int level) {
	if (board->isBoardFull() || level <= 0) {
		return evaluateBoard(board);
	}

	double maxUtility = -100;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//Copy board
			Board tmpBoard(*board);
			if (tmpBoard.addMove(type ,i, j)) {
				double moveUtility = 0;
				//If move makes player win
				if (tmpBoard.checkWinningStatus(type)) {
					return 100;
				} else {
					moveUtility = minMove(&tmpBoard, level-1);
				}

				if (moveUtility > maxUtility) {
					maxUtility = moveUtility;
				}
			} else {
				continue;
			}
		}
	}

	return maxUtility;
}

double SmartPlayer::minMove(Board *board, int level) {
	if (board->isBoardFull() || level <= 0) {
		return evaluateBoard(board);
	}

	double minUtility = 100;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//Copy board
			Board tmpBoard(*board);
			if (tmpBoard.addMove(type*-1 ,i, j)) {
				double moveUtility = 0;
				//If move makes player win
				if (tmpBoard.checkWinningStatus(type*-1)) {
					return -1;
				} else {
					moveUtility = maxMove(&tmpBoard, level-1);
				}

				if (moveUtility < minUtility) {
					minUtility = moveUtility;
				}
			} else {
				continue;
			}
		}
	}

	return minUtility;
}

double SmartPlayer::evaluateBoard(Board *board) {
	stack<Node> tree;
	list<Node> nodesSeen;
	int largestDistanceCovered = 0;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			if (board->getGrid(i, j) == type) {
				Node current = Node{i, j, false};

				if (!nodeVisited(current, nodesSeen)) {
					tree.push(current);
					int lowestCell;
					int highestCell;

					if (type == 1) {
						lowestCell = current.x;
						highestCell = current.x;
					} else {
						lowestCell = current.y;
						highestCell = current.y;
					}

					while(!tree.empty()) {
						Node top = tree.top();
						nodesSeen.push_back(top);
						tree.top().isBranch = false;

						if (type == 1) {
							if (top.x < lowestCell) {
								lowestCell = top.x;
							}
							if (top.x > highestCell) {
								highestCell = top.x;
							}

						} else {
							if (top.y < lowestCell) {
								lowestCell = top.y;
							}
							if (top.y > highestCell) {
								highestCell = top.y;
							}
						}


						//Get Neighbours
						stack<Cell> neighbours = board->getNeighbours(type, top.x, top.y);
						int numOfNeighbours = neighbours.size();
						int neighboursAdded = 0;
						for (int k = 0; k < numOfNeighbours; ++k) {
							Node neighbour;
							neighbour.x = neighbours.top().x;
							neighbour.y = neighbours.top().y;
							neighbour.isBranch = numOfNeighbours > 1;
							if (!nodeVisited(neighbour, nodesSeen)) {
								tree.push(neighbour);
								neighboursAdded++;
							}
							neighbours.pop();
						}


						//Backtrack if current node is an end point with no new neighbours
						if (neighboursAdded == 0) {
							int distanceCovered = ((highestCell - lowestCell));
							if (distanceCovered > largestDistanceCovered) {
								largestDistanceCovered = distanceCovered;
							}

							while(!tree.empty()) {
								if (!tree.top().isBranch) {
									tree.pop();
								} else {
									break;
								}
							}
						}
					}
				}
			}
		}
	}

//Heuristic value of the size of the longest line as a percentage of the boardsize
	return largestDistanceCovered;

}

void SmartPlayer::printStack(stack<Node> stack) {
	while(!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}
}

bool SmartPlayer::nodeVisited(Node node, list<Node> &list){
	auto current = list.begin();
	for (int i = 0; i < list.size(); ++i) {
		if (node == *current) {
			return true;
		}
		advance(current, 1);
	}

	return false;
}
#endif //ASSIGNMENT1_SMARTPLAYER_H