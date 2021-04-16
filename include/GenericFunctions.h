/*
 * GenericFunctions.h
 *
 *  Created on: 16/04/2021
 *      Author: Hayden Hartley
 */

#ifndef ASSIGNMENT1_GENERICFUNCTIONS_H
#define ASSIGNMENT1_GENERICFUNCTIONS_H

#include <stack>
#include <list>

using namespace std;

/**
 * Function used to print a stack<Node> to the screen for debugging purposes
 * @param stack Copy of the stack to print to the screen
 */
template<class Type>
void printStack(stack<Type> stack) {
	while(!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}
}

/**
 * Searches a list structure to find the passed object
 * @param toFind Copy of object instance to find
 * @param list List to search
 * @return Boolean value representing the result of the search
 */
template<class Type>
bool searchList(Type toFind, list<Type> &list) {
	auto current = list.begin();
	for (int i = 0; i < list.size(); ++i) {
		if (toFind == *current) {
			return true;
		}
		advance(current, 1);
	}

	return false;
}

#endif //ASSIGNMENT1_GENERICFUNCTIONS_H
