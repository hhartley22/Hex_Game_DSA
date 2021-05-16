/*
 * MiniMaxPlayer.h
 *
 *  Created on: 15/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_MONTECARLOPLAYER_H
#define ASSIGNMENT1_MONTECARLOPLAYER_H

#include <string>
#include <queue>

#include "Player.h"
#include "Board.h"
#include "Move.h"

#define NUM_OF_SIMS 1000

class MonteCarloPlayer : public Player {
private:
	double simulate(Board *board, int player);
	int expand(Board board, int player);
public:
	MonteCarloPlayer(int type, string name);
	bool getMove(Board *board, int &x, int &y) override;

};

MonteCarloPlayer::MonteCarloPlayer(int type, string name) : Player(type, name){
	//EMPTY CONSTRUCTOR
}

/**
 * Get move of player.
 * @param board Pointer to Board representing the current game state.
 * @param x Address of an integer to store the x position of the move.
 * @param y Address of an integer to store the x position of the move.
 * @return Boolean value representing whether a move was retrieved successfully.
 */
bool MonteCarloPlayer::getMove(Board *board, int &x, int &y) {

	priority_queue<Move> moves;

	for (int i = 0; i < board->getBoardSize(); ++i) {
		for (int j = 0; j < board->getBoardSize(); ++j) {
			if (board->cellIsEmpty(i, j)) {
				Board tmpBoard(*board);

				//Check if making move results in win
				int gameStatus = tmpBoard.checkWinningStatus(type);
				if (gameStatus == type) { //Win
					Move move{i, j, 1};
					moves.push(move);
					continue;
				} else if (gameStatus == type*-1) { //Loss
					Move move{i, j, -1};
					moves.push(move);
					continue;
				}

				tmpBoard.addMove(type, i, j);
				double moveUtility = simulate(&tmpBoard, type*-1);

				Move move{i, j, moveUtility};
				moves.push(move);
			}
		}
	}

	if (!moves.empty()) {
		x = moves.top().x;
		y = moves.top().y;
		cout << "MonteCarlo Utility: " << moves.top().heuristic << endl;
	}

	return true;
}

/**
 * Simulate game.
 * @param board Pointer to Board representing the beginning state of the simulation
 * @param player Integer representing the current player who's move it is.
 * @return A double representing frequency of player wins.
 */
double MonteCarloPlayer::simulate(Board *board, int player) {

	if (player == 1) {
		player = -1;
	} else {
		player = 1;
	}

	double utilityTotal = 0;
	for (int i = 0; i < NUM_OF_SIMS; ++i) {
		double simOutcome = expand(*board, player);
		utilityTotal += simOutcome;
	}

	return utilityTotal / NUM_OF_SIMS;
}

/**
 * Expand on the current board state of the simulation
 * @param board Current state of the board.
 * @param player Integer representing the player who's move it currently is.
 * @return A integer representing whether the player has won or lost the current simulation.
 */
int MonteCarloPlayer::expand(Board board, int player) {
	//Get Board State
	if (board.checkWinningStatus(type)) { //Win
		return 1;
	} else if(board.checkWinningStatus(type*-1)){ //Loss
		return 0;
	}

	//Add Move
	Cell move = board.getPossibleMove();
	board.addMove(board.getTurn(), move.x, move.y);

	//Recurse
	if (player == 1) {
		player = -1;
	} else {
		player = 1;
	}

	return expand(board, player);
}

#endif //ASSIGNMENT1_MONTECARLOPLAYER_H
