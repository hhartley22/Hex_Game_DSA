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
#include "SmartPlayer.h"

using namespace std;

int main() {
	srand(time(0));
	int boardSize = 5;
	cout <<"Input the size of board:" << endl;
    cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;

	Board *board = new Board(boardSize);

	Player *p1 = new SmartPlayer(1, "Smart (Red)");
	Player *p2 = new SmartPlayer(-1, "Human (Blue)");

	HexGame game(board, p1, p2);
	game.play();

	delete board;
	delete p1;
	delete p2;

//	system("pause");
	return 0;
}

