#pragma once
#include <stdlib.h>

typedef struct BinaryHeap {
	void* data;
	size_t memSize;
	size_t logicalSize;
	size_t dataSize;
}BinaryHeap;

typedef enum BinaryHeapReturnCodes {
	SUCCESS,
	OUT_OF_MEMORY,
	MEMORY_ERROR,
	ERROR
}BinaryHeapReturnCodes;

BinaryHeapReturnCodes setupHeap(BinaryHeap* heap, size_t dataSize);
BinaryHeapReturnCodes insert(BinaryHeap* heap, const void* item, void* context, int (*compareFunction)(const void* item1, const void* item2, const void* context));
BinaryHeapReturnCodes removeSmallest(BinaryHeap* heap, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context), void* ans);
BinaryHeapReturnCodes pushPop(BinaryHeap* heap, const void* item, void* context, int(*compareFunction)(const void* item1, const void* item2, const void* context), void* ans);
BinaryHeapReturnCodes deleteHeap(BinaryHeap* heap);