// input.c -- Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For use of function strlen.
#include <ctype.h> // For use of function tolower.
#include "tree.h" // Include tree.h for definition of node structure.
#include "input.h"
#include "output.h" // Include output.h for use of function printResults.

extern int totalWords;
extern int uniqueWords;

/*
 * Checks the character passed to determine whether it is a valid character
 * or not. Accepted characters are 'A'-'Z', 'a'-'z', '0'-'9'.
 *
 * @param undeterminedChar a single character.
 * @return 0 if the given character is not one the allowed characters, 1 if it is.
 */
int checkValidity(char undeterminedChar) {
	/*
	 * Could check whether not comparing to both upper and lower case
	 * letters or checking only lower case tolower(char) would be faster.
	 */
	if (('A' <= undeterminedChar && undeterminedChar <= 'Z')
			|| ('a' <= undeterminedChar && undeterminedChar <= 'z')
			|| ('0' <= undeterminedChar && undeterminedChar <= '9')) {
		return 1;
	} else {
		return 0;
	}
} // int checkValidity(char character);

/*
 * Changes the value stored at the pointer passed to an acceptable
 * format that can then be used to compare against the other words
 * that are stored in the tree.
 *
 * @param word pointer to the word that is to be formatted.
 */
void formatWord(char* word) {
	// Allocate memory to temporary word. Will not be longer than word passed as parameter.
	int length = strlen(word);
	char formattedWord[length]; // = (char*) malloc(sizeof(char) * length);
	int beginning = -1; // Default values for beginning and end which will be compared later to check for a missing word case.
	int end = -1;

	/*
	 * Set the beginning and end points of the portion of the word which is valid.
	 * If none of the characters are invalid, i and j will be equal to the index of
	 * the first character and the last characters, respectively, and the entire
	 * word will be left at the pointer's location.
	 */
	// Loops from the beginning of the word to the end.
	for (int i = 0; i < length; i++) {
		if (checkValidity(word[i])) {
			beginning = i;
			break;
		}
	}
	// Loops from the end of the word to the beginning.
	for (int j = length - 1; j >= 0; j--) {
		if (checkValidity(word[j])) {
			end = j;
			break;
		}
	}

	// If none of the characters are valid, there is no word to be passed.
	if (beginning == -1 || end == -1) {
		word[0] = '\0';
		return;
	}

	// Transcribes the correct portion of word to formattedWord while also using function tolower to make entire word lowercase.
	int n = 0; // Initialize index for formattedWord.
	for (int k = beginning; k <= end; k++) {
		formattedWord[n++] = tolower(word[k]); // Make lower case and format at the same time.
	}
	formattedWord[n] = '\0'; // Assign end of word char.

	// Transcribe back to original location of the word.
	for (int i = 0; i <= n; i++) {
		word[i] = formattedWord[i];
	}
} // void formatWord(char* word);

/*
 * Compares two words, determining whether they are the same, or which
 * is earlier in alphabetical order. Returns a corresponding value,
 * which is used to then find the node in which the word is being held
 * (or if no node is found, to create a new node).
 *
 * @param wordA pointer to the first word which is being compared.
 * @param wordB pointer to the the second word which is being compared.
 * @return 0 if the words are the same, 1 if word A is earlier in alphabetical order, 2 if word B is earlier.
 */
int compareWords(char *wordA, char *wordB) {
	int lengthA = strlen(wordA);
	int lengthB = strlen(wordB);
	int minimumLength;

	if (lengthA < lengthB) {
		minimumLength = lengthA;
	} else {
		minimumLength = lengthB;
	}

	/*
	 * If the words are the same, should pass over this part. Because then
	 * the values will always be equal to each other an will never be < or
	 * >.
	 */
	for (int i = 0; i < minimumLength; i++) {
		if (wordA[i] < wordB[i]) {
			return 2; // Indicating wordA is earlier in alphabetical order.
		}
		if (wordA[i] > wordB[i]) {
			return 1; // Indicating wordB is earlier in alphabetical order.
		}
	}

	if (lengthA == lengthB) {
		return 0;
	} else if (lengthA > lengthB) {
		return 1;
	} else { // lengthA < lengthB
		return 2;
	}
} // int compareWords(char *wordA, char *wordB);

/*
 * Recursively finds the correct placement of the word within the binary
 * tree. If no correct node is found for the word, creates a new node
 * with the correct default parameters for it and increments uniqueWords.
 * If a correct node is found for the given word, increments totalWords.
 * Returning a pointer to the node is important because as each of the
 * recursive calls of the functions ends, the pointers will be retraced
 * back to the first call of addNode, with the root node as the parameter.
 *
 * @param word pointer to word that is being compared.
 * @param origin pointer to node who's word is being compared.
 * @return pointer to the node which is either modified or the newly created node.
 */
node* addNode(char *word, node *origin) {
	if (origin == NULL) { // If origin is null, creates a new pointer for the word.
		// Increment number of unique words and total words.
		uniqueWords++;
		totalWords++;

		// Allocate memory to store the new node.
		origin = malloc(sizeof(node));
		origin->word = malloc((int) strlen(word) * sizeof(char));

		/*
		 * Create new node  with default parameters. Set word equal to
		 * strdup(word) in order to use memory more efficiently.
		 */
		origin->word = strdup(word);
		origin->count = 1;
		origin->leftNode = NULL;
		origin->rightNode = NULL;

		return origin; // This will make sure that the call to the left or right node will be set to the newly created node.
	} else { // Case if the next node checked is not null.
		if (compareWords(word, origin->word) == 0) { // Case if the word being passed is the same word as the one stored in the node.
			origin->count++; // Increment count of the word.
			totalWords++;
			return origin;
		} else if (compareWords(word, origin->word) == 2) { // Case if the word being passed is earlier in alphabetical order.
			origin->leftNode = addNode(word, origin->leftNode);
		} else { // Case if the word in the node is earlier in alphabetical order.
			origin->rightNode = addNode(word, origin->rightNode);
		}
		return origin;
	}
} // node* addNode(char *word, node *origin);
