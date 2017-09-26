// tree.c -- Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "input.h" // Include input.h for use of functions addNode and formatWord.
#include "output.h" // Include output.h for use of functions printResult and freeNode.

FILE *output;
FILE **input;
node *rootNode;
int totalWords;
int uniqueWords;

/*
 * Creates and allocates memory to an array of pointers that point to
 * the multiple input file streams. Then loops through each of these file
 * streams, calling functions to assist with processing words and creating
 * new nodes or updating already created nodes. Then prints the results of
 * the program.
 *
 * @param argc number of parameters passed through the command line.
 * @param *argv pointer to the array of pointers to what was passed through the command line, where argv[0] is the name of the program by default.
 * @return 0 to indicate that the program ran correctly.
 */
int main(int argc, char *argv[]) {
	output = fopen(argv[1], "w"); // Open output to writing only.
	input = malloc((argc - 2) * sizeof(FILE)); // argc = # of input files + output file + program name.

	int n = 0; // Initialize index for input array of file streams.
	for (int i = 0; i < argc - 2; i++) { // Create an array which points to the input files passed as parameters.
		input[n++] = fopen(argv[i + 2], "r"); // Open a stream to each input file for reading only.
	}

	char *word; // Hold each word streamed through using function fscanf.
	word = malloc(1000 * sizeof(char));

	_Bool firstRun = 0; // Unsigned integer type
	for (int j = 0; j < argc - 2; j++) {
		while (fscanf(input[j], "%s", word) == 1) {
			formatWord(word);
			if (word[0] != '\0') { // End of word character.
				if (firstRun == 0) {
					rootNode = addNode(word, rootNode);
					firstRun++;
				} else {
					addNode(word, rootNode);
				}
			}

		}
	}

	// Prints results of the program.
	printResults(output);

	// Free memory which was allocated at the beginning of main.
	free(word);
	fclose(output); // Close output write stream.
	freeNode(rootNode); // Free memory which was assigned to nodes (entire tree).

	for (int k = 0; k < argc - 2; k++) {
		free(input[k]);
	}
	free(input);

	return 0;
} // int main(in argc, char *argv[]);
