/*
 * Move.h
 *
 *  Created on: 15/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_MOVE_H
#define ASSIGNMENT1_MOVE_H

struct Move {
	int x;
	int y;
	double heuristic;

	bool operator<(const Move &rhs) const {
		return this->heuristic < rhs.heuristic;
	}

	bool operator>(const Move &rhs) const {
		return this->heuristic > rhs.heuristic;
	}
};

#endif //ASSIGNMENT1_MOVE_H
