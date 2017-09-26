//============================================================================
// Name        : Lab4_C++_sample.cpp
// Author      : Hugh C. Lauer
// Version     :
// Copyright   : 
// Description : Sample program for Eclipse debugging lab
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "SortedList.h"

SortedList S;


int main(int argc, char *argv[]) {

	for (int i = 1; i < argc; i++)
		S.InsertItem(atol(argv[i]));	// insert the arguments into list

	S.printReverseList();
	std::cout << "The sum of the items in the list is " << S.getSum() << std::endl;

	return EXIT_SUCCESS;
}
