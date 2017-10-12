// Main function for Laboratory #7
//		Adapted from Programming Assignment #4 of C-term 2010
//		H. C. Lauer, February 15, 2010

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using std::ifstream;
using std::ofstream;
using std::string;
using std::cerr;
using std::endl;
using std::ios;
using std::setw;
using std::tolower;


#include "BinaryTree.h"

void ScanInputFile(char *fileName, BinaryTree &tree);
void PrintOutput(ofstream &output, BinaryTree &tree);

int main(const int argc, char *argv[]) {
	BinaryTree wordTree;

	if (argc < 3) {
		cerr << "Usage: Lab7 outputFile inputFile1 ... " << endl;
		return -1;
	}	//	if (argc < 3)

	//	Open output file
	ofstream output(argv[1]);
	if (!output) {
		cerr << "Unable to open output file " << argv[1] << endl;
		return -1;
	}	//	if (!output)

	for (int i = 2; i < argc; i++)
		ScanInputFile(argv[i], wordTree);

	PrintOutput(output, wordTree);

}	//	main

void ScanInputFile(char *filename, BinaryTree &tree){
	ifstream input(filename);
	if (!input) {
		cerr << "Unable to open input file " << filename 
			<< ". Ignoring." << endl;
		return;
	} else
		cerr << "Scanning input file " << filename << endl;

	int wordCount = 0, emptyCount = 0;
	string nextWord;
	while (!input.eof()) {
		input >> nextWord;
		if (nextWord.empty())
			emptyCount++;
		else {
			for (unsigned int i = 0; i < nextWord.length(); i++)
				nextWord[i] = tolower(nextWord[i]);
			tree.AddNode(nextWord);
			wordCount++;
		}
	}	//	while (!input.eof())

	cerr << "Input file " << filename << " scanned successfully. " <<
		wordCount << " words added to tree. " << endl;
	cerr << "    " << emptyCount <<
		" empty strings encountered during scan." << 
		"Closing file." << endl;

	input.close();

}	//	ScanInputFile


void PrintOutput(ofstream &output, BinaryTree &tree){
	tree.PrintTree(output);
	output << "------------" << endl;
	output << setw(6) << tree.getTotalNodes() << 
		"  different words encountered." << endl;
	output.close();
}	//	PrintOutput
