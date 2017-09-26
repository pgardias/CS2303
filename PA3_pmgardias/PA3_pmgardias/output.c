// output.c -- Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include "tree.h" // Include tree.h for definition of node structure.
#include "output.h"

extern FILE *output;
extern node *rootNode;
extern int uniqueWords;
extern int totalWords;

/*
 * Recursive function which is called once on the root node. It recursively calls
 * until it reaches the left-most word and then progresses with printing each word
 * until it reaches the right-most word in the tree and finds the final right null
 * node.
 *
 * @param *origin pointer to node which should be checked for printing, and then further used to recursively print rest of tree.
 */
void printWords(node *origin) {
	if (origin == NULL) { // Check if root node is null. If it is, exit, because subsequent calls of printWords would be useless.
		return;
	}
	/*
	 * Recursively print all words to the left, starting with the left-most
	 * word and printing the right-most word last. This guarantees alphabetical
	 * order when printing entire contents of the binary tree.
	 */
	printWords(origin->leftNode);
	fprintf(output, "%6d\t%s\n", origin->count, origin->word); // Prints "count	word\n"
	printWords(origin->rightNode);
} // void printWords(node *origin);

/*
 * Recursively frees memory for all nodes in the tree, beginning with the farthest
 * nodes and ending with the first call of freeNode.
 *
 * @param *origin pointer to node which should be checked for a value to free, and then further used to recursively free memory from rest of nodes.
 */
void freeNode(node *origin) {
	if (origin == NULL) { // Check if root node is null. If it is, exit, because subsequent calls of freeNode would be unnecessary.
		return;
	}
	// Recursively free all nodes which are below this node.
	freeNode(origin->leftNode);
	freeNode(origin->rightNode);
	free(origin->word);
	free(origin);
} // void freeNode(node *origin);

void printResults(FILE *out) {
	printWords(rootNode); // Prints words in given format.
	fprintf(output, "-------------\n");
	fprintf(output, "%6d\tDistinct words\n", uniqueWords); // Prints "uniqueWords	Distinct words\n"
	fprintf(output, "%6d\tTotal words counted (including duplicates)\n",
			totalWords); // Prints "totalWords	Total words counted (including duplicates)\n"
} // void printResults(FILE *out);

