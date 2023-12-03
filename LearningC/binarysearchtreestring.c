#include "binarysearchtreestring.h"
#include "stringholder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void balanceTree(RBTreeString* tree, RBTreeStringNode* currentNode);
static void leftRotation(RBTreeString* tree, RBTreeStringNode* currentNode);
static void rightRotation(RBTreeString* tree, RBTreeStringNode* currentNode);
static void printNode(RBTreeStringNode* node);
static void printNodeFile(RBTreeStringNode* node, FILE* wfptr);

RBTreeStringNode* createRBStringNodeInformation(StringArray* information) {
	RBTreeStringNode* nextNode = (RBTreeStringNode*)malloc(sizeof(RBTreeStringNode));
	if (nextNode != NULL) {
		nextNode->parent = NULL;
		nextNode->left = NULL;
		nextNode->right = NULL;
		nextNode->color = NOCOLOR;
		nextNode->string = information;
	}
	return nextNode;
}

RBTreeStringNode* createRBStringNodeBlank() {
	RBTreeStringNode* nextNode = malloc(sizeof(RBTreeStringNode));
	if (nextNode != NULL) {
		nextNode->parent = NULL;
		nextNode->left = NULL;
		nextNode->right = NULL;
		nextNode->color = NOCOLOR;
		nextNode->string = NULL;
	}
	return nextNode;
}
__int32 insertRBTreeStringNode(RBTreeString* tree, RBTreeStringNode* newNode) {
	char inserted = 0;
	__int32 sort;
	newNode->color = RED;
	RBTreeStringNode* current = tree->head;

	if (tree->head == NULL) {
		tree->head = newNode;
		tree->head->color = BLACK;
		tree->head->side = ROOT;
		return 1;
	}

	while (inserted == 0) {
		if (current == NULL) {
			if (newNode->side == RIGHT) {
				newNode->parent->right = newNode;
			} else {
				newNode->parent->left = newNode;
			}
			inserted = 1;
		}else {
			sort = strcmp(current->string->string, newNode->string->string);
			if (sort < 0) {
				newNode->parent = current;
				newNode->side = LEFT;
				current = current->left;
			} else if (sort > 0) {
				newNode->parent = current;
				newNode->side = RIGHT;
				current = current->right;
			} else if (sort == 0) {
				return 0;
			}
		}
	}
	balanceTree(tree, newNode);
	tree->head->color = BLACK;
	return inserted;
}

RBTreeStringNode* removeRBTreeStringNode(RBTreeString* tree, char* information) {

	return tree->head;
}

void printRBSAtringStrings(const RBTreeString* tree) {
	printf("%s\n", tree->head->string->string);
	if (tree->head->left != NULL) {
		printNode(tree->head->left);
	}
	if (tree->head->right != NULL) {
		printNode(tree->head->right);
	}
}

void printRBSAtringStringsFile(RBTreeString* tree, FILE* wfptr) {
	fprintf(wfptr, "%s\n", tree->head->string->string);
	if (tree->head->left != NULL) {
		printNodeFile(tree->head->left, wfptr);
	}
	if (tree->head->right != NULL) {
		printNodeFile(tree->head->right, wfptr);
	}
}

static void balanceTree(RBTreeString* tree, RBTreeStringNode* currentNode) {
	RBTreeStringNode* curParent = currentNode->parent;
	while (1) {
		if (currentNode->color != BLACK && curParent != NULL && curParent->color == RED && curParent->parent != NULL) {
			switch (curParent->side) {
			case LEFT:
				if (curParent->parent->right != NULL && curParent->parent->right->color == RED) {
					curParent->color = BLACK;
					curParent->parent->right->color = BLACK;
					currentNode->color = RED;
					currentNode = curParent->parent;
					currentNode->color = RED;
					curParent = currentNode->parent;
				} else {
					if (currentNode->side == RIGHT) {
						leftRotation(tree, currentNode->parent);
						rightRotation(tree, currentNode->parent);
						currentNode->color = BLACK;
						currentNode->left->color = RED;
						currentNode->right->color = RED;
						curParent = currentNode->parent;
					} else {
						rightRotation(tree, currentNode->parent->parent);
						currentNode = currentNode->parent;
						currentNode->color = BLACK;
						currentNode->left->color = RED;
						currentNode->right->color = RED;
						curParent = currentNode->parent;
					}
				}
				break;
			case RIGHT:
				if (curParent->parent->left != NULL && curParent->parent->left->color == RED) {
					curParent->color = BLACK;
					curParent->parent->left->color = BLACK;
					currentNode->color = RED;
					currentNode = curParent->parent;
					currentNode->color = RED;
					curParent = currentNode->parent;
				} else {
					if (currentNode->side == LEFT) {
						rightRotation(tree, currentNode->parent);
						leftRotation(tree, currentNode->parent);
						currentNode->color = BLACK;
						currentNode->left->color = RED;
						currentNode->right->color = RED;
						curParent = currentNode->parent;
					} else {
						leftRotation(tree, currentNode->parent->parent);
						currentNode = currentNode->parent;
						currentNode->color = BLACK;
						currentNode->left->color = RED;
						currentNode->right->color = RED;
						curParent = currentNode->parent;
					}
				}
				break;
			}
		} else {
			break;
		}
	}
}

void destroyRBStringArrayNode(RBTreeStringNode** node) {
	destroyStringArray(&((*node)->string));
	free(*node);
	*node = NULL;
}

static void leftRotation(RBTreeString* tree, RBTreeStringNode* currentNode) {
	RBTreeStringNode* newHead = currentNode->right;
	RBTreeStringNode* switchingLeft = NULL;
	if (newHead->left != NULL) {
		switchingLeft = newHead->left;
	}
	newHead->parent = currentNode->parent;
	newHead->left = currentNode;
	newHead->side = currentNode->side;
	if (newHead->side == LEFT) {
		newHead->parent->left = newHead;
	} else if (newHead->side == RIGHT) {
		newHead->parent->right = newHead;
	} else {
		tree->head = newHead;
	}
	currentNode->side = LEFT;
	currentNode->parent = newHead;
	if (switchingLeft != NULL) {
		currentNode->right = switchingLeft;
		switchingLeft->side = RIGHT;
	} else {
		currentNode->right = NULL;
	}
}

static void rightRotation(RBTreeString* tree, RBTreeStringNode* currentNode) {
	RBTreeStringNode* newHead = currentNode->left;
	RBTreeStringNode* switchingRight = NULL;
	if (newHead->right != NULL) {
		switchingRight = newHead->right;
	}
	newHead->parent = currentNode->parent;
	newHead->right = currentNode;
	newHead->side = currentNode->side;
	if (newHead->side == LEFT) {
		newHead->parent->left = newHead;
	} else if(newHead->side == RIGHT) {
		newHead->parent->right = newHead;
	} else {
		tree->head = newHead;
	}
	currentNode->side = RIGHT;
	currentNode->parent = newHead;
	if (switchingRight != NULL) {
		currentNode->left = switchingRight;
		switchingRight->side = LEFT;
	} else {
		currentNode->left = NULL;
	}
}

static void printNode(RBTreeStringNode* node) {
	printf("%s\n", node->string->string);
	if (node->left != NULL) {
		printNode(node->left);
	}
	if (node->right != NULL) {
		printNode(node->right);
	}
}

static void printNodeFile(RBTreeStringNode* node, FILE* fwptr) {
	fprintf(fwptr, "%s\n", node->string->string);
	if (node->left != NULL) {
		printNodeFile(node->left, fwptr);
	}
	if (node->right != NULL) {
		printNodeFile(node->right, fwptr);
	}
}