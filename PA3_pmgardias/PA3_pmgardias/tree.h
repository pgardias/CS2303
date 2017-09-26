// tree.h -- Przemek Gardias (pmgardias)

#ifndef TREE_H_
#define TREE_H_

// Define structure for a tree node.
typedef struct BSTnode {
	char *word; // Pointer to the word which is at this node. The BST is ordered alphabetically,
				// where 'A'/'a' is a lower integer value than 'Z'/'z', respectively. Within the
				// addNode function, lower integer values are assigned to the left.
	int count; // Number of times this word has been counted.
	struct BSTnode *leftNode;
	struct BSTnode *rightNode;
} node;
// Alternatively, "typedef struct BSTnode node".

#endif /* TREE_H_ */
