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
	double minMove(Board *board);
	double maxMove(Board *board);
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

				steps = 5;
				double moveUtility = minMove(&tmpBoard);
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

double SmartPlayer::maxMove(Board *board) {
	if (board->isBoardFull() || steps <= 0) {
		return evaluateBoard(board);
	}

	double maxUtility = -1;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//Copy board
			Board tmpBoard(*board);
			if (tmpBoard.addMove(type ,i, j)) {

				double moveUtility = 0;
				//If move makes player win then set move
				if (tmpBoard.checkWinningStatus(type)) {
					return 1;
				} else {
					moveUtility = minMove(&tmpBoard);
				}

				if (moveUtility > maxUtility) {
					maxUtility = moveUtility;
				}
			} else {
				continue;
			}
		}
	}

	steps--;
	return maxUtility;
}

double SmartPlayer::minMove(Board *board) {
	if (board->isBoardFull() || steps <= 0) {
		return evaluateBoard(board);
	}

	double minUtility = 2;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			//Copy board
			Board tmpBoard(*board);
			if (tmpBoard.addMove(type*-1 ,i, j)) {

				double moveUtility = 0;
				//If move makes player win then set move
				if (tmpBoard.checkWinningStatus(type*-1)) {
					return -1;
				} else {
					moveUtility = maxMove(&tmpBoard);
				}

				if (moveUtility < minUtility) {
					minUtility = moveUtility;
				}
			} else {
				continue;
			}
		}
	}

	steps--;
	return minUtility;
}

double SmartPlayer::evaluateBoard(Board *board) {
	stack<Node> tree;
	list<Node> nodesSeen;
	int longestLineSize = 0;
	int currentLineLength = 0;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			if (board->getGrid(i, j) == type) {
				Node current = Node{i, j, false};
				if (!nodeVisited(current, nodesSeen)) {
					//Get length of line
					tree.push(current);
					currentLineLength = 1;

					while(!tree.empty()) {
						Node top = tree.top();
						nodesSeen.push_back(top);
						tree.top().isBranch = false;
						currentLineLength++;

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

						//printStack(tree);
						//cout << endl;

						//Backtrack if current node is an end point with no new neighbours
						if (neighboursAdded == 0) {
							if (currentLineLength > longestLineSize) {
								longestLineSize = currentLineLength;
							}

							while(!tree.empty()) {
								if (!tree.top().isBranch) {
									tree.pop();
									currentLineLength--;
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
	return (double)longestLineSize / board->getBoardSize();
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