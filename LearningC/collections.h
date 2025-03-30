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
	size_t logicalSize;
}IntegerArray;

typedef struct gen_array {
	void* data;
	size_t mem_size;
	size_t log_size;
	size_t data_size;
}gen_array;

COLLECTIONS_RETURN_CODES insertIntegerArray(IntegerArray* array, int32_t item, size_t index);

COLLECTIONS_RETURN_CODES appendIntegerArray(IntegerArray* array, int32_t item);

COLLECTIONS_RETURN_CODES removeAtIndexIntegerArray(IntegerArray* array, size_t index);

COLLECTIONS_RETURN_CODES removeFirstInstanceIntegerArray(IntegerArray* array, int32_t item);

IntegerArray* setupIntegerArray(size_t size);

gen_array* setup_gen_array(size_t size, size_t data_size);

COLLECTIONS_RETURN_CODES setupIntegerArrayPassing(IntegerArray* array, size_t size);

COLLECTIONS_RETURN_CODES destroyIntegerArray(IntegerArray* array);
COLLECTIONS_RETURN_CODES clearArray(IntegerArray* array, size_t newSize);