/*
 * MiniMaxPlayer.h
 *
 *  Created on: 13/04/2021
 *      Author: Hayden Hartley
 */
#ifndef ASSIGNMENT1_MINIMAXPLAYER_H
#define ASSIGNMENT1_MINIMAXPLAYER_H

#include <queue>
#include <stack>

#include "Move.h"
#include "Node.h"
#include "Cell.h"
#include "GenericFunctions.h"

using namespace std;

class MiniMaxPlayer : public Player {
private:
	int steps;
	double minMove(Board *board, int level);
	double maxMove(Board *board, int level);
	double evaluateBoard(Board *board);
public:
	MiniMaxPlayer(int type, string playerName = "MiniMax");
	bool getMove(Board *board, int &x, int &y) override;
};

MiniMaxPlayer::MiniMaxPlayer(int type, string playerName) : Player(type, playerName) {
	//EMPTY CONSTRUCTOR
}

/**
 * Get players move
 * @param board Pointer to a board object.
 * @param x Integer object to store the moves x value in.
 * @param y Integer object to store the moves y value in.
 * @return A boolean value representing whether a move was chosen successfully
 */
bool MiniMaxPlayer::getMove(Board *board, int &x, int &y) {
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

/**
 * Maximising Step of the MiniMax Algorithm. Chooses the highest utility out of the returned values. Represents the
 * players move.
 * @param board Pointer to a board to play on
 * @param level The amount of remaining levels to traverse before evaluating game state
 * @return A double representing the highest utility seen
 */
double MiniMaxPlayer::maxMove(Board *board, int level) {
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

/**
 * Minimising Step of the MiniMax Algorithm. Chooses the lowest utility out of the returned values. Represents
 * opponents move.
 * @param board Pointer to a board to play on
 * @param level The amount of remaining levels to traverse before evaluating game state
 * @return A double representing the lowest utility seen
 */
double MiniMaxPlayer::minMove(Board *board, int level) {
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

/**
 * Evaluate the board state and return a value representing how advantageous the boards current state is to the player.
 * @param board A pointer to a board representing the current board state
 * @return A double representing the
 */
double MiniMaxPlayer::evaluateBoard(Board *board) {
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
				if (!searchList(currentPos, nodesSeen)) {
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
							if (!searchList(neighbour, nodesSeen)) {
								tree.push(neighbour);
								neighboursAdded++;
							}
							neighbours.pop();
						}

						//Node is a leaf node
						if (neighboursAdded == 0) {
							//Calculate heuristic value
							int distanceCovered = (highestCell - lowestCell) + 1;
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
#endif //ASSIGNMENT1_MINIMAXPLAYER_H