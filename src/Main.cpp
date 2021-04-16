/*
 * Main.cpp
 *
 *  Created on: 21/02/2021
 *      Author: dongmo
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "HexGame.h"
#include "RandomPlayer.h"
#include "MiniMaxPlayer.h"
#include "MonteCarloPlayer.h"

using namespace std;

void printMenu();

int main() {
	srand(time(0));
	int boardSize = 5;
	cout <<"Input the size of board:" << endl;
    cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;

	Board *board = new Board(boardSize);

	int option;
	bool validInput = false;

	printMenu();
	do {
		cin >> option;
		validInput = option >= 1 && option <= 8;
		if (!validInput) {
			cout << "Invalid Option" << endl;
		}
	} while(!validInput);

	Player *p1;
	Player *p2;

	switch (option) {
		case 1:
			p1 = new HumanPlayer(1, "Human (Red)");
			p2 = new HumanPlayer(-1, "Human (Blue)");
			break;
		case 2:
			p1 = new HumanPlayer(1, "Human (Red)");
			p2 = new RandomPlayer(-1, "Random (Blue)");
			break;
		case 3:
			p1 = new HumanPlayer(1, "Human (Red)");
			p2 = new MiniMaxPlayer(-1, "MiniMax (Blue)");
			break;
		case 4:
			p1 = new HumanPlayer(1, "Human (Red)");
			p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
			break;
		case 5:
			p1 = new MiniMaxPlayer(1, "MiniMax (Red)");
			p2 = new MiniMaxPlayer(-1, "MiniMax (Blue)");
			break;
		case 6:
			p1 = new MiniMaxPlayer(1, "MiniMax (Red)");
			p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
			break;
		case 7:
			p1 = new MonteCarloPlayer(1, "MonteCarlo (Red)");
			p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
			break;
		case 8:
			p1 = new RandomPlayer(1, "Random (Red)");
			p2 = new RandomPlayer(-1, "Random (Blue)");
			break;
	}

	HexGame game(board, p1, p2);
	game.play();

	delete board;
	delete p1;
	delete p2;

//	system("pause");
	return 0;
}

void printMenu() {
	cout << "Choose an option: " << endl;
	cout << "1. Human vs Human" << endl;
	cout << "2. Human vs Random" << endl;
	cout << "3. Human vs MiniMax" << endl;
	cout << "4. Human vs MonteCarlo" << endl;
	cout << "5. MiniMax vs MiniMax" << endl;
	cout << "6. MiniMax vs MonteCarlo" << endl;
	cout << "7. MonteCarlo vs MonteCarlo" << endl;
	cout << "8. Random vs Random" << endl;
}

