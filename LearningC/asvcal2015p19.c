#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringholder.h"
#include "binarysearchtreestring.h"

#define TEMPSIZE 100
#define REPLACESIZE 20
#define KEYSIZE 3
#define TRANSFORMATIONCOUNT 43
#define NUMBERMAPPINGS 12

struct Mappings {
	char key[KEYSIZE];
	char replaceValue[REPLACESIZE];
};

struct AdvLetterMapping {
	char letter;
	unsigned __int32 size;
	struct Mappings keyValues[REPLACESIZE];
};

//void adv2015p19(){
main() {
	FILE* fptr;
	FILE* wfptr;
	errno_t error;
	char tempString[TEMPSIZE] = { '\0' };
	char tempChar = '\0';
	struct AdvLetterMapping allMaps[NUMBERMAPPINGS];
	size_t index = 0;
	unsigned __int32 sIndex = 0;
	unsigned __int32 s2Index = 0;
	__int32 insertedCount = 0;
	char* token = NULL;
	char* tokenContext = NULL;
	const char seperator[2] = " ";
	StringArray mainString = { .logicSize = 0, .memSize = 0, .string = NULL };
	RBTreeString tree = { .head = NULL };
	RBTreeStringNode* tempNode = NULL;
	StringArray* tempStringArray;
	__int32 tempCount = 0;
	
	if (createBlankStringArray(&mainString) == 0) {
		return -1;
	}

	error = fopen_s(&fptr, "input2015p19.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		for (index = 0; index < NUMBERMAPPINGS; index++) {
			allMaps[index].letter = '\0';
		}
		index = 0;
		while (strcmp(fgets(tempString, TEMPSIZE, fptr), "\n") != 0) {
			tokenContext = NULL;
			token = NULL;
			tempString[strlen(tempString) - 1] = '\0';
			token = strtok_s(tempString, seperator, &tokenContext);
			while (index < NUMBERMAPPINGS && allMaps[index].letter != token[0] && allMaps[index].letter != '\0') {
				index++;
			}
			if (allMaps[index].letter == '\0') {
				allMaps[index].letter = token[0];
				allMaps[index].size = 0;
			}
			allMaps[index].keyValues[allMaps[index].size].key[0] = token[0];
			allMaps[index].keyValues[allMaps[index].size].key[1] = '\0';
			if (token[1] != '\0') {
				allMaps[index].keyValues[allMaps[index].size].key[1] = token[1];
				allMaps[index].keyValues[allMaps[index].size].key[2] = '\0';
			}
			token = strtok_s(NULL, seperator, &tokenContext);
			token = strtok_s(NULL, seperator, &tokenContext);
			strcpy_s(allMaps[index].keyValues[allMaps[index].size].replaceValue, REPLACESIZE - 1, token);
			allMaps[index].size++;
		}
		tempChar = fgetc(fptr);
		while (tempChar != '\n' && tempChar != EOF) {
			if (appendChar(&mainString, tempChar) == 0) {
				return -1;
			}
			tempChar = fgetc(fptr);
		}
		fclose(fptr);
		
		for (index = 0; index < mainString.logicSize; index++) {
			tempChar = mainString.string[index];
			sIndex = 0;
			s2Index = 0;
			while (sIndex < NUMBERMAPPINGS && s2Index == 0) {
				if (allMaps[sIndex].letter == tempChar) {
					for (s2Index = 0; s2Index < allMaps[sIndex].size; s2Index++) {
						if (allMaps[sIndex].keyValues[s2Index].key[1] != '\0') {
							if (allMaps[sIndex].keyValues[s2Index].key[1] == mainString.string[index + 1]) {
								tempStringArray = createBlankStringArrayStruct();
								if (tempStringArray != NULL) {
									appendSubstring(tempStringArray, mainString.string, 0, index);
									appendString(tempStringArray, allMaps[sIndex].keyValues[s2Index].replaceValue);
									appendSubstring(tempStringArray, mainString.string, index + 2, mainString.logicSize);
									tempNode = createRBStringNodeInformation(tempStringArray);
									tempCount = insertRBTreeStringNode(&tree, tempNode);
									insertedCount += tempCount;
									if (tempCount == 0) {
										destroyRBStringArrayNode(&tempNode);
									}
								}
							}
						} else {
							tempStringArray = createBlankStringArrayStruct();
							if (tempStringArray != NULL) {
								appendSubstring(tempStringArray, mainString.string, 0, index);
								appendString(tempStringArray, allMaps[sIndex].keyValues[s2Index].replaceValue);
								appendSubstring(tempStringArray, mainString.string, index + 1, mainString.logicSize);
								tempNode = createRBStringNodeInformation(tempStringArray);
								tempCount = insertRBTreeStringNode(&tree, tempNode);
								insertedCount += tempCount;
								if (tempCount == 0) {
									destroyRBStringArrayNode(&tempNode);
								}
							}
						}
					}
				}
				sIndex++;
			}
		}
		error = fopen_s(&wfptr, "output.txt", "w");
		if (!error) {
			printRBSAtringStringsFile(&tree, wfptr);
			fclose(wfptr);
		}
		printf("%s\n", mainString.string);
		printRBSAtringStrings(&tree);
		printf("inserted count: %d\n", insertedCount);
		return 0;
		
	}
	return error;
}