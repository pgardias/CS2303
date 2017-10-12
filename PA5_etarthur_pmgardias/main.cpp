// main.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include "Organism.h"
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "Doodlebug.h"
#include "Ant.h"
#include <iostream>
using namespace std;

Organism*** grid;
int numD;
int numA;
int totalD;
int totalA;
int gridLen;

/**
 * onEdge() checks the cell which whose coordinates
 * are passed and returns a boolean indicating whether
 * it is on the edge of the grid or not
 *
 * @return boolean indicating whether the given cell is on the edge
 */
bool onEdge(int x, int y) {
	return (x == 0) || (x == gridLen - 1) || (y == 0) || (y == gridLen - 1);
}

/**
 * canAttack() returns a boolean indicating whether
 * the object in the given cell coordinates is able to attack
 *
 * @return boolean indicating whether the given cell contains an organism which is able to attack
 */
bool canAttack(int x, int y) {
	if (grid[x][y] == NULL) {
		return false;
	} else {
		return grid[x][y]->isPrey;
	}
}

/**
 * update() loops through the grid, updating canMove
 * for all organisms and then updates all organisms on the
 * grid, updating all doodlebugs first and all ants
 */
void update() {
	for (int i = 0; i < gridLen; i++) {
		for (int j = 0; j < gridLen; j++) {
			if (grid[i][j] == NULL) {

			} else {
				grid[i][j]->canMove = true;
			}
		}
	}

	// Loops through entire board, updating the state of all doodlebugs before the ants
	for (int i = 0; i < gridLen; i++) {
		for (int j = 0; j < gridLen; j++) {
			if (grid[i][j] != NULL && grid[i][j]->canMove) {
				if (grid[i][j]->isPrey == false) {
					grid[i][j]->action();
				}
			}
		}
	}

	// Loops through entire board, updating the state of all ants after the doodlebugs
	for (int i = 0; i < gridLen; i++) {
		for (int j = 0; j < gridLen; j++) {
			if (grid[i][j] != NULL && grid[i][j]->canMove) {
				if (grid[i][j]->isPrey == true) {
					if (grid[i][j] == NULL) {

					} else {
						grid[i][j]->action();
					}
				}
			}
		}
	}
}

/**
 * printBoard() loops through the grid, printing out
 * the current state of the grid with x's indicating
 * a doodlebug and o's indicating an ant
 */
void printBoard() {
	std::cout << endl << "|--------------------";
	for (int i = 0; i < gridLen; i++) {
		std::cout << "|" << endl << "|";
		for (int j = 0; j < gridLen; j++) {
			if (grid[i][j] == NULL) {
				std::cout << " ";
			} else {
				if (grid[i][j]->isPrey) {
					std::cout << "o";
				} else {
					std::cout << "x";
				}
			}
		}
	}
	std::cout << "|" << endl << "|--------------------|" << endl;
}

/**
 * main() handles running the simulation, passing arguments
 * initializing the grid, looping through eat step of the
 * simulation, printing out the results, and then deallocating
 * memory
 *
 * @return 0 for a successful program execution
 */
int main(int argc, char **argv) {
	gridLen = 20;
	int doodlebugs = 5;
	int ants = 100;
	int steps = 1000;
	int seed = 1;
	int pause = 0;
	switch (argc) {
	case 7:
		pause = atoi(argv[6]);
	case 6:
		if (atoi(argv[5]) == 0) {
			seed = time(NULL);
		} else {
			seed = (atoi(argv[5]));
		}
	case 5:
		steps = (atoi(argv[4]));
	case 4:
		ants = atoi(argv[3]);
	case 3:
		doodlebugs = atoi(argv[2]);
	case 2:
		gridLen = atoi(argv[1]);
	default:
		break;
	}
	srand(seed);

	if (pause != 0) {
		std::cout << "The board will be printed every " << pause
				<< " turns, enter a character and press enter to continue the program when this occurs."
				<< endl;
	}
	if (ants + doodlebugs > gridLen * gridLen) {
		std::cout
				<< "There are more Organisms than space on the board, will terminate"
				<< endl;
		return 1;
	}

	grid = (Organism***) malloc(sizeof(Organism**) * gridLen);
	for (int i = 0; i < gridLen; i++) {
		grid[i] = (Organism**) malloc(sizeof(Organism*) * gridLen);
	}

	for (int i = 0; i < gridLen; i++) {
		for (int j = 0; j < gridLen; j++) {
			grid[i][j] = NULL;
		}
	}

	for (int i = 0; i < doodlebugs; i++) {
		int x = rand() % gridLen;
		int y = rand() % gridLen;
		if (grid[x][y] == NULL) {
			Doodlebug* temp = new Doodlebug(x, y);
			grid[x][y] = temp;
		} else {
			i--;
		}
	}
	for (int i = 0; i < ants; i++) {
		int x = rand() % gridLen;
		int y = rand() % gridLen;
		if (grid[x][y] == NULL) {
			Ant* temp = new Ant(x, y);
			grid[x][y] = temp;
		} else {
			i--;
		}
	}

	int time = 0;
	char getChar;
	while (time < steps) {
		if (numD <= 0 || numA <= 0) {
			break;
		}
		update();
		if (pause != 0) {
			if (time % pause == 0) {
				printBoard();
				std::cin >> getChar;
			}
		}
		time++;
	}

	std::cout << "Command line: ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << " ";
	}
	std::cout << endl;
	std::cout << "The number of steps simulated was: " << time << endl;
	std::cout << "The total number of ants was: " << totalA
			<< " and the number of ants remaining was: " << numA << endl;
	std::cout << "The total number of Doodlebugs was: " << totalD
			<< " and the number of Doodlebugs remaining was: " << numD << endl;
	std::cout << "The final board was: " << endl;
	printBoard();

	for (int i = 0; i < gridLen; i++) {
		for (int j = 0; j < gridLen; j++) {
			if (grid[i][j] != NULL) {
				delete grid[i][j];
			}
		}
	}

	for (int i = 0; i < gridLen; i++) {
		free(grid[i]);
	}
	free(grid);
	return 0;
}
