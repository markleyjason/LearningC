#define _CRTDBG_MAP_ALLOC
#include "stringholder.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

StringArray* createBlankStringArrayStruct() {
	StringArray* newArray = (StringArray*)malloc(sizeof(StringArray));
	if (newArray != NULL) {
		if (createBlankStringArray(newArray) == 1) {
			return newArray;
		}
	}
	return NULL;
}

__int32 createBlankStringArray(StringArray* stringArray) {
	stringArray->string = (char*)malloc(STRINGSTARTERSIZE * sizeof(char));
	if (stringArray->string != NULL) {
		stringArray->string[0] = '\0';
		stringArray->logicSize = 0;
		stringArray->memSize = STRINGSTARTERSIZE;
	} else {
		return 0;
	}

	return 1;
}

__int32 createStringArrayFromChar(StringArray* stringArray, const char firstChar) {
	stringArray->string = (char*)malloc(STRINGSTARTERSIZE * sizeof(char));
	if (stringArray->string != NULL) {
		stringArray->string[0] = firstChar;
		stringArray->string[1] = '\0';
		stringArray->logicSize = 1;
		stringArray->memSize = STRINGSTARTERSIZE;
	} else {
		return 0;
	}

	return 1;
}

__int32 createStringArrayFromCharArray(StringArray* stringArray, const char* startString) {
	stringArray->string = (char*)malloc(2 * strlen(startString) * sizeof(char));
	stringArray->memSize = 2 * strlen(startString);
	if (stringArray->string != NULL) {
		strcpy_s(stringArray->string, stringArray->memSize, startString);
		stringArray->logicSize = strlen(startString);
		stringArray->memSize = 2 * strlen(startString);
	} else {
		return 0;
	}
	return 1;
}

__int32 destroyStringArray(StringArray** stringArray) {
	free((*stringArray)->string);
	(*stringArray)->string = NULL;
	(*stringArray)->memSize = 0;
	(*stringArray)->logicSize = 0;
	free((*stringArray));
	*stringArray = NULL;
	return 0;
}

__int32 increaseMemSize(StringArray* stringArray) {
	char* tempString = realloc(stringArray->string, stringArray->memSize * 2 * sizeof(char));
	if (tempString != NULL) {
		stringArray->memSize *= 2;
		stringArray->string = tempString;
	} else {
		return 0;
	}
	return 1;
}

__int32 increaseMemSizeNewSize(StringArray* stringArray, size_t newSize) {
	char* tempString = realloc(stringArray->string, newSize * sizeof(char));
	if (tempString != NULL) {
		stringArray->memSize = newSize;
		stringArray->string = tempString; 
	} else {
		return 0;
	}
	return 1;
}

__int32 decreaseMemSize(StringArray* stringArray) {
	char* tempString = (char*)malloc(stringArray->memSize / 2 * sizeof(char));
	if (tempString != NULL) {
		stringArray->memSize = stringArray->memSize / 2;
		strcpy_s(tempString, stringArray->memSize, stringArray->string);
		free(stringArray->string);
		stringArray->string = tempString;
	} else {
		return 0;
	}
	return 1;
}

__int32 appendChar(StringArray* stringArray, const char addition) {
	if (stringArray->logicSize + 1 > stringArray->memSize / 2) {
		if (increaseMemSize(stringArray) == 0) {
			return 0;
		}
	}
	stringArray->string[stringArray->logicSize] = addition;
	stringArray->logicSize++;
	stringArray->string[stringArray->logicSize] = '\0';
	return 1;
}


__int32 appendString(StringArray* stringArray, const char* addition) {
	size_t newSize = stringArray->memSize;
	while (stringArray->logicSize + strlen(addition) > stringArray->memSize / 2) {
		while (newSize < stringArray->logicSize + strlen(addition)) {
			newSize *= 2;
		}
		newSize *= 2;
		if (increaseMemSizeNewSize(stringArray, newSize) == 0) {
			return 0;
		}
	}
	strcat_s(stringArray->string, stringArray->memSize - 1, addition);
	stringArray->logicSize += strlen(addition);
	return 1;
}

__int32 appendSubstring(StringArray* stringArray, const char* addition, size_t start, size_t end) {
	if (end != start) {
		size_t newSize = stringArray->memSize;
		while ((stringArray->logicSize + end - start) > stringArray->memSize / 2) {
			while (newSize < (stringArray->logicSize + end - start)) {
				newSize *= 2;
			}
			newSize *= 2;
			if (increaseMemSizeNewSize(stringArray, newSize) == 0) {
				return 0;
			}
		}
		strncat_s(stringArray->string, stringArray->memSize - 1, addition + start, end - start);
		stringArray->logicSize += end - start;
	}
	
	return 1;
}