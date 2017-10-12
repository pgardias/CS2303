//	treeNode for Programming Assignment #4
//		H.C. Lauer	February 14, 2010

#ifndef _TREENODE_H
#define _TREENODE_H

#include <string>
using std::string;

class TreeNode {
public:
	int incr();
	int getCount() const;
	string getWord() const;
	int compare(const string &newWord) const;
	TreeNode *setLeft(TreeNode *newItem);
	TreeNode *setRight(TreeNode *newItem);
	TreeNode *getLeft() const;
	TreeNode *getRight() const;
	TreeNode(const string &newWord);	//constructor
	~TreeNode();					//destructor

private:
	const string word;
	int count;
	TreeNode *left, *right;
};




#endif
