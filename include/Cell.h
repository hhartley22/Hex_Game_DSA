/*
 * Cell.h
 *
 *  Created on: 01/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_CELL_H
#define ASSIGNMENT1_CELL_H

#include <ostream>

struct Cell {
	int x;
	int y;

	bool operator==(const Cell &rhs) const;
};

bool Cell::operator==(const Cell &rhs) const {
	return (this->x == rhs.x && this->y == rhs.y);
}

ostream &operator<<(ostream &os, Cell &cell) {
	os << "x: " << cell.x << " y: " << cell.y;
	return os;
}

#endif //ASSIGNMENT1_CELL_H
