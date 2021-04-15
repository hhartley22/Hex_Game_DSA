/*
 * BaseBoard.h
 *
 *  Created on: 21/02/2021
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <cstdlib>
#include <list>
#include <stack>

#include "Cell.h"
#include "Node.h"

class Board {
private:
	int boardSize;
	int turn;
	int **grid;
	list<Cell> emptyCells;
public:
	Board(int bs) {
		boardSize = bs;
		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++) {
			grid[i] = new int[boardSize];
		}

		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;
				//Insert grid cell into list of empty cells as all new board cells will all be empty
				emptyCells.push_front(Cell{i, j});
			}
		}

		turn = 1;
	}

	virtual ~Board() {

		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(Board &cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				grid[i][j] = 0;

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
				//Add empty cells to list
				if (grid[i][j] == 0) {
					emptyCells.push_front(Cell{i, j});
				}
			}
		turn = cboard.getTurn();
	}

	int getBoardSize() {
		return boardSize;
	}

	int getGrid(int x, int y) {
		return grid[x][y];
	}

	int getTurn() {
		return turn;
	}

	bool validInput(int, int);

	bool addMove(int playerType, int x, int y);

	void removeEmptyCell(int x, int y);

	bool isBoardFull();

	Cell getPossibleMove();

	stack<Cell> getNeighbours(int playerType, int row, int col);

	int checkWinningStatus(int playerType);

	bool checkNode(int playerType, Node node);

	bool nodeVisited(Node node, list<Node> &list);

	int playerHasStraightLine(int playerType, int row, int col);

	void printStack(stack<Node> stack);

	void printBoard();
};

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

bool Board::addMove(int playerType, int x, int y) {

	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;

	turn = -1 * turn;
	return true;
}

//Removes a cell from the emptyCells member
void Board::removeEmptyCell(int x, int y) {
	emptyCells.remove(Cell{x, y});
}

bool Board::isBoardFull() {
	return !(emptyCells.size());
}

//Returns a random empty Cell from the remaining empty board cells
Cell Board::getPossibleMove() {
	int cellPos = rand() % emptyCells.size();

	auto iterator = emptyCells.begin();
	advance(iterator, cellPos);

	return *iterator;
}

stack<Cell> Board::getNeighbours(int playerType, int row, int col) {
	stack<Cell> neighbours;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//Bounds checking
			if (i == -1 && row <= 0) { //No row above
				continue;
			} else if (i == 1 && row >= (boardSize-1) ) { //No row below
				continue;
			} else if(j == -1 && col <= 0) { //No column to left
				continue;
			} else if (j == 1 && col >= (boardSize-1) ) { //No column to right
				continue;
			} else if (i == 0 && j == 0) { //Is the cell we want to check for neighbours around
				continue;
			}

			//Cells exist but are not considered neighbours in the board shape of a rhombus
			if (i == -1 && j == -1) {
				continue;
			} else if (i == 1 && j == 1) {
				continue;
			}

			if (grid[row+i][col+j] == playerType) {
				neighbours.push(Cell{row + i, col + j});
			}
		}
	}

	return neighbours;
}

/**
 * Checks whether the current player has won the game in a complete straight line based on their last move.
 *
 * @param playerType The identifier of the player to check for a straight line for.
 * @param row Row of the players last move.
 * @param col Column of the players last move.
 * @return If a player has won, the players identifier is returned otherwise, 0 is returned.
 */
int Board::playerHasStraightLine(int playerType, int row, int col) {
	switch (playerType) {
		//Red Player
		case 1:
			//Checking cols as the complete lines
			for (int i = 0; i < boardSize; ++i) {
				if (grid[i][col] != playerType) {
					return 0;
				}
			}
			//Will only be reached if the line is all the players type otherwise it returns false above
			return playerType;
		//Blue player
		case -1:
			//Checking rows as teh complete lines
			for (int i = 0; i < boardSize; ++i) {
				if (grid[row][i] != playerType) {
					return 0;
				}
			}
			//Will only be reached if the line is all the players type otherwise it returns false above
			return playerType;
	}

	return false; //Return false by default
}

int Board::checkWinningStatus(int playerType) {
	stack<Node> tree;
	list<Node> visitedNodes;

	//Get starting nodes
	if (playerType == 1) { //Red Player (Rows)
		//Check first row
		for (int i = 0; i < boardSize; ++i) {
			if (grid[0][i] == playerType) {
				tree.push(Node{0, i, true});
			}
		}
	} else { //Blue Player (Columns)
		//Check first column
		for (int i = 0; i < boardSize; ++i) {
			if (grid[i][0] == playerType) {
				tree.push(Node{i, 0, true});
			}
		}
	}

	while(!tree.empty()) {
		//Get node to check
		Node current = tree.top();
		visitedNodes.push_back(current);
		tree.top().isBranch = false; //Node is checked so it is no longer marked as a branch

		//Check node status
		if (checkNode(playerType, current)) {
			return  playerType;
		}

		//Get nodes neighbours
		stack<Cell> neighbours = getNeighbours(playerType, current.x, current.y);
		int numOfNeighbours = neighbours.size();
		int neighboursAdded = 0; //Track number of new nodes added to tree
		while(!neighbours.empty()) {
			Node neighbour;
			neighbour.x = neighbours.top().x;
			neighbour.y = neighbours.top().y;
			neighbour.isBranch = numOfNeighbours > 1;

			if (!nodeVisited(neighbour, visitedNodes)) {
				tree.push(neighbour);
				++neighboursAdded;
			}

			neighbours.pop();
		}

		//Backtrack if current node is an end point with no new neighbours
		if (neighboursAdded == 0) {
			while (!tree.empty()) {
				if (!tree.top().isBranch) {
					tree.pop();
				} else {
					break;
				}
			}
		}

	}

	return 0;
}

/**
 * Function used to print a stack<Node> to the screen for debugging purposes
 * @param stack Copy of the stack to print to the screen
 */
void Board::printStack(stack<Node> stack) {
	while(!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}
}

/**
 * Checks whether the passed node is in a winning position for the player
 * @param playerType Symbol representing the player
 * @param node Node object to check for a win using
 * @return A boolean value representing whether the node represents a winning position
 */
bool Board::checkNode(int playerType, Node node) {
	if(playerType == 1) {
		if (node.x == boardSize-1) {
			return true;
		}
	} else {
		if (node.y == boardSize-1) {
			return true;
		}
	}

	return false;
}

/**
 * Searches list<Nodes> for a passed node object
 * @param node Copy of node instance to find in list
 * @param list List to search
 * @return Boolean value representing the result of the search
 */
bool Board::nodeVisited(Node node, list<Node> &list){
	auto current = list.begin();
	for (int i = 0; i < list.size(); ++i) {
		if (node == *current) {
			return true;
		}
		advance(current, 1);
	}

	return false;
}

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
			cout << "  ";

		if (i < 9)
			cout << " " << i + 1 << " ";
		else
			cout << i + 1 << " ";

		for (int j = 0; j < boardSize; j++) {
			if (grid[i][j] == 0) {
				if (j == 0) {
					cout << "|   |";
				} else {
					cout << "   |";
				}
			} else if (grid[i][j] == 1) {
				if (j == 0) {
					cout << "| R |";
				} else {
					cout << " R |";
				}
			} else {
				if (j == 0) {
					cout << "| B |";
				} else {
					cout << " B |";
				}
			}
		}
		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}

	cout << endl;
	cout << endl;
}

#endif /* BOARD_H_ */
