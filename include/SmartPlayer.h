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
	bool getMove(Board *board, int &x, int &y) override;
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
			if (tmpBoard.getGrid(i,j) == 0) {
				tmpBoard.addMove(type ,i, j);
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
			if (board->getGrid(i, j) == 0) {
				tmpBoard.addMove(type ,i, j);
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
			if (board->getGrid(i, j) == 0) {
				tmpBoard.addMove(type*-1 ,i, j);
				double moveUtility = 0;
				//If move makes opponent win
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

	//Loop over all board locations
	for(int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//If location has players identifier in it
			if (board->getGrid(i, j) == type) {
				Node currentPos = Node{i,j, false};

				//If node has not been visited yet
				if (!nodeVisited(currentPos, nodesSeen)) {
					tree.push(currentPos);

					//Set up heuristic parameters
					int lowestCell;
					int highestCell;

					if (type == 1) {
						lowestCell = currentPos.x;
						highestCell = currentPos.x;
					} else {
						lowestCell = currentPos.y;
						highestCell = currentPos.y;
					}

					//Search tree
					while(!tree.empty()) {
						Node currentTop = tree.top();
						nodesSeen.push_back(currentTop);
						tree.top().isBranch = false;

						//Compare against heuristic parameters
						if (type == 1) {
							if (currentTop.x < lowestCell) {
								lowestCell = currentTop.x;
							}
							if (currentTop.x > highestCell) {
								highestCell = currentTop.x;
							}
						} else {
							if (currentTop.y < lowestCell) {
								lowestCell = currentTop.y;
							}
							if (currentTop.y > highestCell) {
								highestCell = currentTop.y;
							}
						}

						//Get neighbours and expand
						stack<Cell> neighbours = board->getNeighbours(type, currentTop.x, currentTop.y);
						int numOfNeighbours = neighbours.size();
						int neighboursAdded = 0;
						while(!neighbours.empty()) {
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

						//Node is a leaf node
						if (neighboursAdded == 0) {
							//Calculate heuristic value
							int distanceCovered = (highestCell - lowestCell);
							if (distanceCovered > largestDistanceCovered) {
								largestDistanceCovered = distanceCovered;
							}

							//Backtrack
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