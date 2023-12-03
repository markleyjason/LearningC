#pragma once
#include "stringholder.h"
#include <stdio.h>

typedef enum NODE_INFORMATION {
	BLACK,
	RED,
	NOCOLOR,
	RIGHT,
	LEFT,
	ROOT
} NODE_INFORMATION;

typedef struct RBTreeStringNode {
	StringArray* string;
	NODE_INFORMATION color;
	struct RBTreeStringNode* left;
	struct RBTreeStringNode* right;
	struct RBTreeStringNode* parent;
	NODE_INFORMATION side;
}RBTreeStringNode;

typedef struct RBTreeString {
	RBTreeStringNode* head;
}RBTreeString;

RBTreeStringNode* createRBStringNodeInformation(StringArray* information);
RBTreeStringNode* createRBStringNodeBlank();
__int32 insertRBTreeStringNode(RBTreeString* tree, RBTreeStringNode* newNode);
RBTreeStringNode* removeRBTreeStringNode(RBTreeString* tree, char* information);
void printRBSAtringStrings(const RBTreeString* tree);
void printRBSAtringStringsFile(RBTreeString* tree, FILE* wfptr);
void destroyRBStringArrayNode(RBTreeStringNode** node);