// binaryTree for Programming Assignment #4
//		H. C. Lauer	Febuary 14, 2010

#include <iostream>
#include <string>
#include <iomanip>
using std::string;
using std::endl;
using std::setw;


#include "BinaryTree.h"
#include "TreeNode.h"

int BinaryTree::totalNodes = 0;

int BinaryTree::getTotalNodes() const {
	return totalNodes;
}	// getTotalNodes()

TreeNode *BinaryTree::AddNode(const string &word){
	if (!root){
		totalNodes++;
		return root = new TreeNode(word);
	} else
		return AddNode(root, word);
}	//	AddNode(one arg)


TreeNode * BinaryTree::AddNode(TreeNode *subtree, const string &word){
	
	int result = subtree -> compare(word);
	if (result == 0) {
		subtree -> incr();
		return subtree;
	}
	if (result > 0){
		if (subtree -> getLeft())
			return AddNode(subtree -> getLeft(), word);
		else {
			totalNodes++;
			return subtree -> setLeft(new TreeNode(word));
		}
	} 
	else {
		if (subtree -> getRight())
			return AddNode(subtree -> getRight(), word);
		else {
			totalNodes++;
			return subtree -> setRight(new TreeNode(word));
		}
	}

}	//	AddNode


void BinaryTree::PrintTree(std::ostream &output) {
	PrintTree(root, output);
}	//	PrintTree(one arg)

void BinaryTree::PrintTree(TreeNode *subtree, std::ostream &output) {
	if (subtree->getLeft())
		PrintTree(subtree->getLeft(), output);

	output << setw(6) << subtree->getCount() << "  " << subtree->getWord() << endl;

	if (subtree->getRight())
		PrintTree(subtree->getRight(), output);
}	//	PrintTree(subtree, ...)

BinaryTree::BinaryTree() :
	root(NULL)
{
}	//	BinaryTree constructor

BinaryTree::~BinaryTree() {
	if (root) 
		delete root;			// Recursive deletes the tree nodes
}	//	~BinaryTree
