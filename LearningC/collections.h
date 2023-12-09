#pragma once
#include <stdint.h>

typedef enum COLLECTIONS_RETURN_CODES {
	SUCCESS,
	OUT_OF_MEMORY,
	OUT_OF_BOUNDS,
	NULL_POINTER,
	DOES_NOT_EXIST
}COLLECTIONS_RETURN_CODES;

typedef struct IntegerArray {
	int32_t* data;
	size_t size;
	unsigned __int64 logicalSize;
}IntegerArray;

COLLECTIONS_RETURN_CODES insertIntegerArray(IntegerArray* array, int32_t item, size_t index);

COLLECTIONS_RETURN_CODES appendIntegerArray(IntegerArray* array, int32_t item);

COLLECTIONS_RETURN_CODES removeAtIndexIntegerArray(IntegerArray* array, size_t index);

COLLECTIONS_RETURN_CODES removeFirstInstanceIntegerArray(IntegerArray* array, int32_t item);

IntegerArray* setupIntegerArray(size_t size);

COLLECTIONS_RETURN_CODES destroyIntegerArray(IntegerArray* array);