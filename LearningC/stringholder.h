#pragma once
#include <stdlib.h>
#define STRINGSTARTERSIZE 16

typedef struct StringArray {
	size_t memSize;
	size_t logicSize;
	char *string;
}StringArray;

StringArray* createBlankStringArrayStruct();
__int32 createBlankStringArray(StringArray* stringArray);
__int32 createStringArrayFromChar(StringArray* stringArray, const char firstChar);
__int32 createStringArrayFromCharArray(StringArray* stringArray, const char* startString);
__int32 destroyStringArray(StringArray** stringArray);
__int32 increaseMemSize(StringArray* stringArray);
__int32 increaseMemSizeNewSize(StringArray* stringArray, size_t newSize);
__int32 decreaseMemSize(StringArray* stringArray);
__int32 appendChar(StringArray* stringArray, const char addition);
__int32 appendString(StringArray* stringArray, const char* addition);
__int32 appendSubstring(StringArray* stringArray, const char* addition, size_t start, size_t end);