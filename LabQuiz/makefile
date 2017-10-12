# Makefile for Lab7
#		Hugh C. Lauer, October 7, 2012
#		Modified for -m32, Oct 15, 2013
#		Modified to remove -m32 Feb 28, 2017
#

CCXFLAGS = -O2 -g -Wall

all: Lab7.o BinaryTree.o TreeNode.o
	g++ -Wall Lab7.o BinaryTree.o TreeNode.o -o Lab7

Lab7.o: Lab7.cpp
	g++ $(CCXFLAGS) -c Lab7.cpp

BinaryTree.o: BinaryTree.h BinaryTree.cpp
	g++ $(CCXFLAGS) -c BinaryTree.cpp

TreeNode.o: TreeNode.h TreeNode.cpp
	g++ $(CCXFLAGS) -c TreeNode.cpp

clean:
	rm -f *.o *.exe Lab7

		# DO NOT DELETE

BinaryTree.o: TreeNode.h
BinaryTree.o: TreeNode.h
Lab7.o: BinaryTree.h TreeNode.h

