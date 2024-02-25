#include "binary_heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static BinaryHeapReturnCodes siftUp(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context));
static BinaryHeapReturnCodes siftDown(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context));

BinaryHeapReturnCodes setupHeap(BinaryHeap* heap, size_t dataSize) {
	heap->dataSize = dataSize;
	heap->memSize = 16;
	heap->logicalSize = 0;
	heap->data = malloc(dataSize * heap->memSize);
	if (heap->data == NULL) {
		return OUT_OF_MEMORY;
	}
	return SUCCESS;
}

BinaryHeapReturnCodes insert(BinaryHeap* heap, const void* item, void* context, int (*compareFunction)(const void* item1, const void* item2, const void* context)) {
	size_t workingIndex = heap->logicalSize;
	void* temp = NULL;
	char* workingTail = heap->data;
	errno_t error;
	if (heap->logicalSize + 1 > heap->memSize / 2) {
		temp = realloc(heap->data, heap->memSize * 2 * heap->dataSize);
		if (temp == NULL) {
			return OUT_OF_MEMORY;
		}
		heap->data = temp;
		heap->memSize = heap->memSize * 2;
		workingTail = temp;
	}
	workingTail = workingTail + heap->logicalSize * heap->dataSize;
	error = memcpy_s(workingTail, heap->dataSize, item, heap->dataSize);
	if (error) {
		return MEMORY_ERROR;
	}
	heap->logicalSize++;
	if (heap->logicalSize > 1) {
		siftUp(heap, context, compareFunction);
	}
	return SUCCESS;
}

BinaryHeapReturnCodes removeSmallest(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context), void* ans) {
	errno_t error;
	char* end = heap->data;
	if (heap->logicalSize > 0) {
		error = memcpy_s(ans, heap->dataSize, heap->data, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		heap->logicalSize--;
		end = end + heap->logicalSize * heap->dataSize;
		error = memcpy_s(heap->data, heap->dataSize, end, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		if(heap->logicalSize > 1) {
			siftDown(heap, context, compareFunction);
		}
	}
	return SUCCESS;
}

BinaryHeapReturnCodes pushPop(BinaryHeap* heap, const void* item, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context), void* ans) {

	return SUCCESS;
}

BinaryHeapReturnCodes deleteHeap(BinaryHeap* heap) {
	free(heap->data);
	return SUCCESS;
}

static BinaryHeapReturnCodes siftUp(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context)) {
	size_t index = heap->logicalSize - 1;
	char* child = heap->data;
	char* parent = heap->data;
	int comp = 0;
	void* tempItem = malloc(heap->dataSize);
	errno_t error;
	child = child + index * heap->dataSize;
	index = ((index - 1) / 2);
	parent = parent + index * heap->dataSize;
	comp = compareFunction(parent, child, context);
	while (comp > 0) {
		error = memcpy_s(tempItem, heap->dataSize, parent, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		error = memcpy_s(parent, heap->dataSize, child, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		error = memcpy_s(child, heap->dataSize, tempItem, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		if (index == 0) {
			break;
		}
		child = parent;
		index = (index - 1) / 2;
		parent = heap->data;
		parent = parent + index * heap->dataSize;
		comp = compareFunction(parent, child, context);
	}
	free(tempItem);
	return SUCCESS;
}

static BinaryHeapReturnCodes siftDown(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context)) {
	size_t index = 0;
	char* leftChild = heap->data;
	char* parent = heap->data;
	int comp = 0;
	void* tempItem = malloc(heap->dataSize);
	errno_t error;
	leftChild = leftChild + heap->dataSize;
	index = index * 2 + 1;
	if (index + 1 < heap->logicalSize) {
		comp = compareFunction(leftChild, leftChild + heap->dataSize, context);
	} else {
		comp = 0;
	}
	if (comp > 0) {
		leftChild = leftChild + heap->dataSize;
		index++;
	}
	comp = compareFunction(parent, leftChild, context);
	while ((index < heap->logicalSize && comp > 0)) {
		error = memcpy_s(tempItem, heap->dataSize, parent, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		error = memcpy_s(parent, heap->dataSize, leftChild, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		error = memcpy_s(leftChild, heap->dataSize, tempItem, heap->dataSize);
		if (error) {
			return MEMORY_ERROR;
		}
		if (index >= heap->logicalSize) {
			break;
		}
		index = index * 2 + 1;
		parent = leftChild;
		leftChild = heap->data;
		leftChild = leftChild + index * heap->dataSize;
		if (index + 1 < heap->logicalSize) {
			comp = compareFunction(leftChild, leftChild + heap->dataSize, context);
		} else {
			comp = 0;
		}
		if (comp > 0) {
			leftChild = leftChild + heap->dataSize;
			index++;
		}
		comp = compareFunction(parent, leftChild, context);
	}
	free(tempItem);
	return SUCCESS;
}