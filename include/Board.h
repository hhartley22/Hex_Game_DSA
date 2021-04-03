/*
 * BaseBoard.h
 *
 *  Created on: 21/02/2021
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include "Cell.h"

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

	int checkWinningStatus(int playerType) {
		//To be implemented
		return 0;
	}

	int playerHasStraightLine(int playerType, int row, int col);

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
	for (int i = 0; i < cellPos; ++i) {
		advance(iterator, 1);
	}

	return *iterator;
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
