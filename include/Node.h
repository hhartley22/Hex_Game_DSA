/*
 * Node.h
 *
 *  Created on: 10/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_NODE_H
#define ASSIGNMENT1_NODE_H

struct Node {
	int x;
	int y;
	bool isBranch;

	bool operator==(Node &rhs) const;
};

bool Node::operator==(Node &rhs) const {
	return this->x == rhs.x && this->y == rhs.y;
}

ostream &operator<<(ostream &os, Node &node) {
	os << "x: " << node.x << " y: " << node.y << " Branch: " << node.isBranch << endl;
	return os;
}

#endif //ASSIGNMENT1_NODE_H
