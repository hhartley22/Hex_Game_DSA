/*
 * RandomPlayer.h
 *
 *  Created on: 01/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_RANDOMPLAYER_H
#define ASSIGNMENT1_RANDOMPLAYER_H

#include <string>

#include "Player.h"
#include "Cell.h"
#include "Board.h"

using namespace std;

class RandomPlayer : public Player {
public:
	RandomPlayer(int type, string name = "Random");
	bool getMove(Board *board, int &x, int &y) override;
};

RandomPlayer::RandomPlayer(int type, string name) : Player(type, name) {
	//Empty Constructor
}

/**
 * Get player move
 * @param board Pointer to board representing the current game state
 * @param x Address of integer variable to store the moves x pos in
 * @param y Address of integer variable to store the moves y pos in
 * @return Boolean value representing the whether a move was retrieved successfully
 */
bool RandomPlayer::getMove(Board *board, int &x, int &y) {
	Cell cell = board->getPossibleMove();

	//Add one to convert it to the same form a human move would have
	x = cell.x;
	y = cell.y;

	return true;
}

#endif //ASSIGNMENT1_RANDOMPLAYER_H
