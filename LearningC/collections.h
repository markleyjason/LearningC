#pragma once

typedef enum COLLECTIONS_RETURN_CODES {
	SUCCESS,
	OUT_OF_MEMORY,
	OUT_OF_BOUNDS,
	NULL_POINTER,
	DOES_NOT_EXIST
}COLLECTIONS_RETURN_CODES;

typedef struct IntegerArray {
	__int32* data;
	unsigned __int64 size;
	unsigned __int64 logicalSize;
}IntegerArray;

COLLECTIONS_RETURN_CODES insertIntegerArray(IntegerArray* array, __int32 item, unsigned __int64 index);

COLLECTIONS_RETURN_CODES appendIntegerArray(IntegerArray* array, __int32 item);

COLLECTIONS_RETURN_CODES removeAtIndexIntegerArray(IntegerArray* array, unsigned __int64 index);

COLLECTIONS_RETURN_CODES removeFirstInstanceIntegerArray(IntegerArray* array, __int32 item);

IntegerArray* setupIntegerArray(unsigned __int64 size);

COLLECTIONS_RETURN_CODES destroyIntegerArray(IntegerArray* array);