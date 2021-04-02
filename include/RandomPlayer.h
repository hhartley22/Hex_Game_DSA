//
// Created by Hayden on 1/4/21.
//

#ifndef ASSIGNMENT1_RANDOMPLAYER_H
#define ASSIGNMENT1_RANDOMPLAYER_H

#include <string>

#include "Player.h"
#include "Cell.h"
#include "Board.h"

using namespace std;

class RandomPlayer : public Player {
public:
	RandomPlayer(int t, string name = "Random");
	bool getMove(Board *board, int &x, int &y) override;
};

RandomPlayer::RandomPlayer(int t, string name) : Player(t, name) {
	//Empty Constructor
}

bool RandomPlayer::getMove(Board *board, int &x, int &y) {
	Cell cell = board->getPossibleMove();

	//Add one to convert it to the same form a human move would have
	x = cell.x;
	y = cell.y;

	return true;
}

#endif //ASSIGNMENT1_RANDOMPLAYER_H
