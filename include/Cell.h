//
// Created by Hayden on 1/4/21.
//

#ifndef ASSIGNMENT1_CELL_H
#define ASSIGNMENT1_CELL_H

struct Cell {
	int x;
	int y;

	bool operator==(const Cell &rhs) const {
		return (this->x == rhs.x && this->y == rhs.y);
	}
};


#endif //ASSIGNMENT1_CELL_H
