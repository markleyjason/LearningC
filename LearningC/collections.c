#include "collections.h"
#include <stdlib.h>
#include <assert.h>

static COLLECTIONS_RETURN_CODES doubleSizeIntegerArray(IntegerArray* array) {
	__int32* tempHolder;
	unsigned __int64 index;
	assert(2 * array->size > array->size);
	tempHolder = malloc(2 * array->size * sizeof(__int32));
	if (tempHolder != NULL) {
		for (index = 0; index < array->logicalSize; index++) {
			tempHolder[index] = array->data[index];
		}
		free(array->data);
		array->data = tempHolder;
		array->size = 2 * array->size;
	} else {
		return OUT_OF_MEMORY;
	}
	return SUCCESS;
}

static COLLECTIONS_RETURN_CODES halfSizeIntegerArray(IntegerArray* array) {
	__int32* tempHolder;
	unsigned __int64 index;
	tempHolder = malloc(array->size / 2 * sizeof(__int32));
	if (tempHolder != NULL) {
		for (index = 0; index < array->logicalSize; index++) {
			tempHolder[index] = array->data[index];
		}
		free(array->data);
		array->data = tempHolder;
		array->size = array->size / 2;
	} else {
		return OUT_OF_MEMORY;
	}
	return SUCCESS;
}

COLLECTIONS_RETURN_CODES insertIntegerArray(IntegerArray* array, __int32 item, unsigned __int64 index) {
	unsigned __int64 curPos;
	COLLECTIONS_RETURN_CODES returnValue;
	assert(array->logicalSize >= index);
	assert(array->logicalSize + 1 < array->size);
	array->logicalSize++;
	if (array->logicalSize > array->size / 2) {
		returnValue = doubleSizeIntegerArray(array);
		if (returnValue == OUT_OF_MEMORY) {
			if (array->logicalSize + 1 >= array->size) {
				return OUT_OF_MEMORY;
			}
		}
	}
	
	for (curPos = array->logicalSize; curPos > index; curPos--) {
		array->data[curPos] = array->data[curPos - 1];
	}
	array->data[index] = item;
	return SUCCESS;
}

COLLECTIONS_RETURN_CODES appendIntegerArray(IntegerArray* array, __int32 item) {
	COLLECTIONS_RETURN_CODES returnValue;
	assert(array->logicalSize + 1 < array->size);

	array->logicalSize++;

	if (array->logicalSize > array->size / 2) {
		returnValue = doubleSizeIntegerArray(array);
		if (returnValue == OUT_OF_MEMORY) {
			if (array->logicalSize + 1 >= array->size) {
				return OUT_OF_MEMORY;
			}
		}
	}
	array->data[array->logicalSize - 1] = item;
	return SUCCESS;
}

__int32 removeAtIndexIntegerArray(IntegerArray* array, unsigned __int64 index) {
	assert(index < array->logicalSize);
	unsigned __int64 curPos;
	__int32 value = array->data[index];
	COLLECTIONS_RETURN_CODES returnVal;

	for (curPos = index; curPos < array->logicalSize; curPos++) {
		array->data[curPos] = array->data[curPos + 1];
	}
	array->logicalSize--;

	if ((array->logicalSize) * 3 < array->size) {
		returnVal = halfSizeIntegerArray(array);
		if (returnVal != SUCCESS) {
			return OUT_OF_MEMORY;
		}
	}
	return value;
}

COLLECTIONS_RETURN_CODES removeFirstInstanceIntegerArray(IntegerArray* array, __int32 data) {
	unsigned __int64 index = 0;
	while (index < array->logicalSize && data != array->data[index]) {
		index++;
	}
	if (array->data[index] == data) {
		removeAtIndexIntegerArray(array, index);
	} else {
		return DOES_NOT_EXIST;
	}
	return SUCCESS;
}

IntegerArray* setupIntegerArray(unsigned __int64 size) {
	IntegerArray* array = malloc(sizeof(IntegerArray));
	if (array != NULL) {
		array->size = size;
		array->logicalSize = 0;
		array->data = malloc(size * sizeof(__int32));
		if (array->data != NULL) {
			return array;
		} else {
			free(array);
		}
	}
	return NULL;
}

COLLECTIONS_RETURN_CODES destroyIntegerArray(IntegerArray* array) {
	free(array->data);
	free(array);
	return SUCCESS;
}