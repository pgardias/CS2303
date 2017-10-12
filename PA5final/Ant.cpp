// Ant.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include "Ant.h"
#include <stdlib.h>
#include "main.h"
#include "Organism.h"

extern Organism*** grid;
extern int numA;
extern int totalA;
extern int gridLen;

/**
 * Ant() is the constructor for an Ant object
 * with no parameters
 */
Ant::Ant() {
	// TODO Auto-generated constructor stub
}

/**
 * Ant() is the constructor for an Ant object with
 * coordinates as parameters, and is initialized with default
 * values. It icrements the count of total and current ants
 */
Ant::Ant(int x, int y) {
	this->x = x;
	this->y = y;
	this->age = 0;
	this->isPrey = true;
	totalA++;
	numA++;
}

/**
 * ~Ant() is the destructor for an Ant object, it
 * decrements the number of current ants
 */
Ant::~Ant() {
	// TODO Auto-generated destructor stub
	numA--;
}

/**
 *  getTime() is a getter function for the turns
 *  which the ant has been alive
 *
 *  @return age of the Ant object
 */
int Ant::getTime() {
	return age;
}

/**
 * isMove() checks the state of the given cell
 * to see whether the object can be moved into
 * by an existing Ant
 *
 * @return a boolean for if the cell can be moved into
 */
bool Ant::isMove(int x, int y) {
	return grid[x][y] == NULL;
}

/**
 * move() attempts to move an ant into an adjacent
 * cell, choosing one randomly and trying the rest. If
 * none of the cases which were tried work, move()
 * calls itself recursively to try again. It also
 * checks whether it is on the edge of the grid, and
 * terminates if the ant is unable to move
 */
void Ant::move() {
	int random = rand() % 4;
	int basex = this->x;
	int basey = this->y;
	switch (random) {
	case 0: // Cell above
		if (basey == gridLen - 1) {
		} else {
			if (isMove(x, y + 1)) {
				this->y++;
				return;
			}
		}
	case 1: // Cell to right
		if (basex == gridLen - 1) {
		} else {
			if (isMove(x + 1, y)) {
				this->x++;
				return;
			}
		}
	case 2: // Cell below
		if (basey == 0) {
		} else {
			if (isMove(x, y - 1)) {
				this->y--;
				return;
			}
		}
	case 3: // Cell to left
		if (basex == 0) {
		} else {
			if (isMove(x - 1, y)) {
				this->x--;
				return;
			}
		}
	}

	// Check the original coordinates of the ant to see if it is in a position where it cannot move
	if (onEdge(basex, basey)) {
		if (basex == 0 && basey == 0) {
			if (!(isMove(x, y + 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == 0 && basey == gridLen - 1) {
			if (!(isMove(x, y - 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == gridLen - 1 && basey == 0) {
			if (!(isMove(x - 1, y + 1) || isMove(x, y + 1))) {
				return;
			}
		}
		if (basey == gridLen - 1 && basex == gridLen - 1) {
			if (!(isMove(x, y - 1) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basex == 0) {
			if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == gridLen - 1) {
			if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basey == 0) {
			if (!(isMove(x, y + 1) || isMove(x + 1, y) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basey == gridLen - 1) {
			if (!(isMove(x, y - 1) || isMove(x + 1, y) || isMove(x - 1, y))) {
				return;
			}
		}
	} else {
		if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x + 1, y)
				|| isMove(x - 1, y))) {
			return;
		}
	}
	if (basey == y && basex == x) {
		move();
	}
}

/**
 * breed() checks the age of the ant and creates a new
 * ant if the age of the ant is at least 3. Upon creating
 * a new ant, moves it into an adjacent cell and resets the
 * age of the current ant
 *
 * @return pointer to the newly born ant or a null
 * object if breeding conditions are not met
 */
Ant* Ant::breed() {
	if (age >= 3) {
		Ant* temp = new Ant(x, y);
		totalA--;
		temp->move();
		int nx = temp->x;
		int ny = temp->y;
		delete temp;
		if (nx != x || ny != y) {
			Ant* baby = new Ant(nx, ny);
			age = 0;
			return baby;
		}
	}
	return NULL;
}

/**
 * action() processes a regular turn of an ant, moving the
 * ant and checking if it can breed in the current turn
 */
void Ant::action() {
	grid[this->x][this->y] = NULL;
	this->move();
	grid[this->x][this->y] = this;
	this->age++;
	this->canMove = false;
	if (this->age < 3) {
		return;
	} else {
		Ant* child = this->breed();
		if (child == NULL) {
			this->move();
			delete child;
			return;
		} else {
			grid[child->x][child->y] = child;
		}
	}
}

