// game.c -- Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include "life.h"

// Declare accessible global variables that are initialized in life.c
extern int gens;
extern char print, pause;
// terminationCondition is used to keep track of why the game ended and printing appropriate information.
int terminationCondition = 0;

/**
 * Handles printing out information at the end of runtime such as how
 * many generations the game ran and why the game ended.
 *
 * @param genCounter count of generations passed.
 * @param terminationCondition value passed indicating reason for end of game.
 */
void endGame(int genCounter, int terminationCondition) {
	printf("The Game of Life ran for %d generations.\n", genCounter);
	printf("The Game ended because ");
	switch (terminationCondition) {
	case (0):
		printf("the predefined number of generations was reached.\n");
		break;
	case (1):
		printf("the board state repeats itself.\n");
		break;
	case (2):
		printf("the board state is looping every other generation.\n");
		break;
	case (3):
		printf("all of the cells are dead.\n");
		break;
	default:
		printf("the program terminated for an unknown reason.\n");
		break;
	}
	exit(0); // Program successfully ended.
} // void endGame(int genCounter, int terminationCondition);

/**
 * Takes two arrays and their respective lengths and checks if they are
 * the same.
 *
 * @param *A[] pointer to first array to compare.
 * @param *B[] pointer to second array to compare.
 * @param rows number of rows in the board.
 * @param cols number of columns in the board.
 * @return 1 if the arrays are the same, 0 if the arrays are different.
 */
int compareArrays(int rows, int cols, int *A[], int *B[]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (A[i][j] != B[i][j]) {
				return 0;
			}
		}
	}
	return 1;
} // int compareArrays(int rows, int cols, int *A[], int *B[]);

/**
 * Takes the current state of the cell and the number of neighbors that the cell
 * has, and determines the state of the given cell for the next generation.
 *
 * @param currentState current state of the cell (1 if alive, 0 if dead).
 * @param neighborCount number of neighbors.
 * @return 1 if the new state of the cell is alive, 0 if the new state is dead.
 */
int updateCell(int currentState, int neighborCount) {
	/*
	 * Adjusts the cell state for the next generation based upon the following
	 * conditions:
	 *
	 * 1.	Death. If an occupied cell has 0, 1, 4, 5, 6, 7, or 8 occupied neighbors,
	 * the organism dies (0 or 1 of loneliness; 4 thru 8 of overcrowding).
	 * 2.	Survival. If an occupied cell has two or three neighbors, the organism
	 * survives to the next generation.
	 * 3.	Birth. If an unoccupied cell has precisely three occupied neighbors, it
	 * becomes occupied by a new organism.
	 */
	if (neighborCount <= 1 || neighborCount >= 4) { // Condition 1 for death.
		return 0;
	} else if (currentState == 1) { // Condition 2 for survival.
		return 1;
	} else if (currentState == 0 && neighborCount == 3) { // Condition 3 for birth.
		return 1;
	} else {
		return 0;
	}
} // int updateCell(int currentState, int neighborCount);

/**
 * Checks if all of the cells in the board are dead.
 *
 * @param rows number of rows in the board.
 * @param cols number of columns in the board.
 * @param *C[] pointer to array that is being checked.
 * @return 1 if the board is "dead", 0 if it is "alive".
 */
int isDead(int rows, int cols, int *C[]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (C[i][j]) {
				return 0;
			}
		}
	}
	return 1;
} // int isDead(int rows, int cols, int *A[]);

/*
 * Prints the board state which is passed.
 *
 * @param rows number of rows in the board.
 * @param cols number of columns in the board.
 * @param *A[] pointer to array storing the board state to print.
 */
void printBoard(int rows, int cols, int *A[]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (A[i][j]) { // 1 = 'x'
				printf("x");
			} else {
				printf("o");
			}
		}
		printf("\n");
	}
} // void printBoard(int rows, int cols, int *A[]);

/**
 * Plays one generation of the Game of Life. Before continuing the game, checks if the
 * game should end. Uses the array neighborCount to check the number of neighbors each
 * cell has. Afterwards, determines the state of the next generation using the number of
 * neighbors and the current state of each cell. Before proceeding to next generation,
 * checks print and pause conditions and acts according to their values.
 *
 * @param rows number of rows in the board.
 * @param cols number of columns in the board.
 * @param *A[] pointer to array storing previous generation.
 * @param *B[] pointer to array storing most recent generation.
 * @param genCounter count of generations that have passed.
 */
void PlayOne(int rows, int cols, int *A[], int *B[], int genCounter) {
	// C is the next board state that is filled.
	// neighborCount is a temporary array that is used to track the number of alive neighbors.
	int **C, **neighborCount;

	// Termination condition
	if (genCounter == gens) {
		endGame(genCounter, terminationCondition);
		return;
	}

	// Always print board state if it will be the last generation.
	if (genCounter == gens - 1) {
		print = 'y';
	}

	// Allocate memory for the arrays that are used to determine next board state.
	C = malloc(rows * sizeof(int *));
	if (C) {
		for (int i = 0; i < rows; i++) {
			C[i] = (int *) malloc(cols * sizeof(int));
			if (!C[i]) {
				exit(-8);
			}
		}
	}

	neighborCount = malloc(rows * sizeof(int *));
	if (neighborCount) {
		for (int i = 0; i < rows; i++) {
			neighborCount[i] = (int *) malloc(cols * sizeof(int));
			if (!neighborCount[i]) {
				exit(-9);
			}
		}
	}

	// Initialize new board states.
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			C[i][j] = 0;
			neighborCount[i][j] = 0;
		}
	}

	/*
	 * The for loop fills the temporary array "neighborCount" which counts the
	 * number of neighbors each cell has in the given board state. This array will
	 * later be used to generate the next board state by checking the value of
	 * neighbors that each of the cells has and determining the given cells state.
	 */
	for (int i = 0; i < rows; i++) { // Iterates through X axis (rows) of board.
		for (int j = 0; j < cols; j++) { // Iterates through Y axis (cols) of board.
			if (B[i][j] != 0) {
				// Only if not on the left edge, increment neighbor count for cell on left.
				if (i > 0) {
					neighborCount[i - 1][j]++;
				}

				// Only if not on right edge, increment neighbor count for cell on right.
				if (i + 1 < rows) {
					neighborCount[i + 1][j]++;
				}

				// Only if not on bottom edge, increment neighbor count for cell below.
				if (j > 0) {
					neighborCount[i][j - 1]++;
				}

				// Only if not on top edge, increment neighbor count for cell above.
				if (j + 1 < cols) {
					neighborCount[i][j + 1]++;
				}

				// Only if not in bottom left corner, increment neighbor count for cell on bottom left.
				if (i != 0 && j != 0) {
					neighborCount[i - 1][j - 1]++;
				}

				// Only if not in bottom right, increment neighbor count for cell on bottom right.
				if (i + 1 < rows && j != 0) {
					neighborCount[i + 1][j - 1]++;
				}

				// Only if not in top left corner, increment neighbor count for cell on top left.
				if (i != 0 && j + 1 < cols) {
					neighborCount[i - 1][j + 1]++;
				}

				// Only if not in top right, increment neighbor count for cell on top right.
				if (i + 1 < rows && j + 1 < cols) {
					neighborCount[i + 1][j + 1]++;
				}
			}
		}
	}

	// Loops through all cells and determines new value for next generation.
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			C[i][j] = updateCell(B[i][j], neighborCount[i][j]);
		}
	}

	/*
	 * Check values for pause and print before proceeding to printing the next generation
	 * of the board state.
	 */
	if (pause == 'y') {
		printf("Press ENTER to continue...");
		getchar(); // No need to save keystroke.
	}

	if (print == 'y') {
		printBoard(rows, cols, C);
		printf("\n");
	}

	/*
	 * Checks if the previously passed generation and the newly generated generation are
	 * the same. If they are, prepare to stop the program.
	 */
	if (compareArrays(rows, cols, B, C)) {
		terminationCondition = 1;
	}

	/*
	 * Checks if the generation before the previous one and the newly generated generation
	 * are the same. If they are, prepare to stop the program.
	 */
	if (compareArrays(rows, cols, A, C)) {
		terminationCondition = 2;
	}

	// Checks if all cells are dead. If they are, set the terminationCondition.
	if (isDead(rows, cols, C)) {
		terminationCondition = 3;
	}

	/*
	 * Free memory previous allocated to the neighborCount array before recursively
	 * calling PlayOne().
	 */
	for (int i = 0; i < rows; i++) {
		free(neighborCount[i]);
	}
	free(neighborCount);

	if (terminationCondition != 0) {
		endGame(genCounter + 1, terminationCondition);
		return;
	}

	PlayOne(rows, cols, B, C, genCounter + 1);

	for (int i = 0; i < rows; i++) {
		free(C[i]);
	}
	free(C);

	return;
} // void PlayOne(int rows, int cols, int *A[], int *B[], int gens);

