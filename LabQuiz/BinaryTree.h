// binaryTree for Programming Assignment #4
//		H. C. Lauer	Febuary 14, 2010

#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include <string>
using std::string;
using std::ostream;

#include "TreeNode.h"

class BinaryTree{
public:
	TreeNode *AddNode(const string &word);
	int getTotalNodes() const;
	void PrintTree(ostream &output);
	BinaryTree();	//Default constructor
	~BinaryTree();	//Destructor
private:
	static int totalNodes;
	void PrintTree(TreeNode *subtree, ostream &output);
	TreeNode *AddNode(TreeNode *subtree, const string &word);
	TreeNode *root;
};	//	class BinaryTree



#endif
