#include "binarysearchtreestring.h"
#include "stringholder.h"
#include <stdio.h>
#include <stdlib.h>

#define NUMCHARS 16

//void testing() {
////main() {
//	FILE* inputFile;
//	FILE* outputFile;
//	errno_t inputError;
//	errno_t outputError;
//	RBTreeString tree = { .head = NULL };
//	RBTreeStringNode* tempNode = NULL;
//	StringArray* tempString = NULL;
//	unsigned __int32 index = 0;
//	__int32 inputted = 0;
//	char insertArray[NUMCHARS] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p' };
//	
//	while (index < NUMCHARS) {
//		tempString = createBlankStringArrayStruct();
//		createStringArrayFromChar(tempString, insertArray[index]);
//		tempNode = createRBStringNodeInformation(tempString);
//		inputted = insertRBTreeStringNode(&tree, tempNode);
//		printRBSAtringStrings(&tree);
//		printf("\n");
//		if (inputted == 0) {
//			destroyRBStringArrayNode(&tempNode);
//		}
//		index++;
//	}
//	
//
//}