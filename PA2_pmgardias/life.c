// life.c -- Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include "life.h"

// Declaring global variables for life.c.
// gens, print, pause are externally declared in game.c.
int rows, cols, gens;
char print, pause;

/**
 * Handles command line parameters, checking for possible errors.
 * Allocates memory for the array used in first generation, then
 * initializes the array and passes contents of the input file to
 * fill the initial board state. Begins playing the game and passes
 * the initial generation. Afterwards, frees memory which was
 * allocated.
 *
 * @param argc number of arguments passed through the command line.
 * @param *argv[] array containing the arguments passed.
 * @return integer 0 to indicate that the program ran correctly.
 */
int main(int argc, char *argv[]) {
	FILE *input; // Pointer to input file.
	int **A; // Stores the first generation, which is taken from input file.s.

	// Default values for both print and pause if no parameters passed for these options.
	print = 'n';
	pause = 'n';

	/*
	 * The argument argv[0] contains the name of your program,
	 * argv[1] is the value X, argv[2] is the value Y, argv[3]
	 * is the value gens, and argv[4] is a string containing
	 * the name of the input file.
	 */
	if (argc < 5) {
		printf("ERROR: Insufficient arguments passed\n");
		exit(-1);
	}

	rows = atoi(argv[1]);
	cols = atoi(argv[2]);
	gens = atoi(argv[3]);
	input = fopen(argv[4], "r");
	print = argv[5][0];
	pause = argv[6][0];

	if (!input) {
		printf("ERROR: Unable to open input file\n");
		exit(-2);
		return 0;
	}

	if (rows < 1 || cols < 1) {
		printf("ERROR: Bad dimensions for game board\n");
		exit(-3);
		return 0;
	}

	if (print != 'y' && print != 'n') {
		printf("ERROR: Wrong character for print parameter\n");
		exit(-4);
	}

	if (pause != 'y' && pause != 'n') {
		printf("ERROR: Wrong character for pause parameter\n");
		exit(-5);
	}

	// Allocate memory for array that stores first generation.
	A = malloc(rows * sizeof(int *));
	if (A) {
		for (int i = 0; i < rows; i++) {
			A[i] = (int *) malloc(cols * sizeof(int));
			if (A[i] == 0) {
				exit(-6);
			}
		}
	}

	/*
	 * Count number of rows and columns which are actually included in
	 * the input file. If there are not enough to fill the board, then
	 * the content of the input file must be centered by both rows and
	 * columns. To do this, the number of columns is counted in the first
	 * row, and the number of total rows is counted by incrementing row
	 * count when a newline character appears.
	 */

	char inputText[250];
	for (int n = 0; n < 250; n++) {
		inputText[n] = 'e'; // Default value which will be later used to determine end of inputText.
	}
	char stream; // Used to get the next character in the input file.
	int centerColCount = 0; // Initialize counters for rows and columns.
	int centerRowCount = 0;

	int i = 0; // Initialize loop variables.
	while (fscanf(input, "%c", &stream) == 1) {
		if (stream == '\n') {
			centerRowCount++;
			inputText[i++] = '\n';
		} else {
			if (centerRowCount == 0) { // If on the first row, continue incrementing the centerColCount.
				centerColCount++;
				inputText[i++] = stream;
			} else { // If not on first row, continue streaming input to inputText and incrementing centerRowCount at end of line.
				inputText[i++] = stream;
			}
		}
	}

	/*
	 * The following nested for loops transfer data from the inputText array
	 * to the array A.If it is necessary, the offset of the contents of the
	 * input file is set to ((rows - centerRowCount) / 2) or
	 * ((cols - centerColCount) / 2).
	 */

	int k = 0; // Used as index for inputText to make sure no out of bounds exception or segmentation faults occur.

	for (int f = ((rows - centerRowCount) / 2); f < rows; f++) { // Initialize f with an offset to center the input.
		if (k >= 249 || inputText[k] == 'e') { // Check to prevent out of bounds exceptions and segmentation faults.
			break;
		}
		for (int g = ((cols - centerColCount) / 2); g < cols; g++) { // Initialize g with an offset to center the input.
			if (k >= 249 || inputText[k] == 'e') { // Check to prevent out of bounds exceptions and segmentation faults.
				break;
			}
			if (inputText[k] == '\n') {
				g = cols;
				k++;
			} else {
				if (inputText[k] != 'x' && inputText[k] != 'o') { // Invalid character checker
					printf("ERROR: Invalid character found in input\n");
					exit(-7);
				} else if (inputText[k] == 'x') {
					A[f][g] = 1;
					k++;
				} else { // inputText[k] == 'o'
					k++;
				}
			}
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
		printBoard(rows, cols, A);
		printf("\n");
	}

	PlayOne(rows, cols, A, A, 0); // Pass 0 as initialization of genCounter, which keeps track of generations passed through.

	// Free memory at the end of the program.
	for (int i = 0; i < rows; i++) {
		free(A[i]);
	}
	free(A);

	return 0;
} // int main(int argc, char *argv[]);
