//	treeNode implementation for Programming Assignment #4
//		H.C. Lauer	February 14, 2010

#include <iostream>
#include "TreeNode.h"

using std::cerr;
using std::endl;

TreeNode *TreeNode::getLeft() const {
	return left;
}	//	getLeft

TreeNode *TreeNode::getRight() const {
	return right;
}	//	getRight

int TreeNode::getCount() const {
	return count;
}	//	getCount

string TreeNode::getWord() const {
	return word;
}	//	getWord

TreeNode *TreeNode::setLeft(TreeNode *newItem){
	if (!left)
		return left = newItem;
	else {
		cerr << "Attempt to replace left subtree" << endl;
		return NULL;
	}
}	//	setLeft

TreeNode *TreeNode::setRight(TreeNode *newItem){
	if (!right)
		return right = newItem;
	else {
		cerr << "Attempt to replace right subtree" << endl;
		return NULL;
	}
}	//	setRight

int TreeNode::incr(){
	return ++count;
}	// incr

int TreeNode::compare(const string &newWord) const {
	return word.compare(newWord);
}	// compare

TreeNode::TreeNode(const string &newWord)
	:word(newWord),	//initialize word
	count(1),		//initialize count
	left(NULL),
	right(NULL)
{
}	//	TreeNode constructor

TreeNode::~TreeNode() {
	if (left) {
		delete left;
		left = NULL;
	}
	if (right) {
		delete right;
		right = NULL;
	}
}	//	TreeNode destructor
