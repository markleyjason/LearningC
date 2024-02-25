#pragma once
#include <stdint.h>

typedef enum hashtableReturnCodes {
	SUCCESS,
	OUT_OF_MEMORY,
	OUT_OF_BOUNDS,
	COPY_ERROR,
	NO_ITEM,
	MEMORY_ERROR
}hashtableReturnCodes;

typedef struct hashlist {
	void* data;
	size_t memSize;
	size_t logicalSize;
}hashlist;

typedef struct hashtable {
	hashlist* lists;
	size_t dataSize;
	size_t numBuckets;
	size_t numItems;
}hashtable;

hashtableReturnCodes setUpHashTable(hashtable* table, size_t numBuckets, size_t dataSize);

hashtableReturnCodes insertHashTable(hashtable* table, void* item, void* context, int32_t (hashFunct(const void* data, const void* context)));

hashtableReturnCodes removeItem(hashtable* table, void* item, void* hashContext, int32_t (hashFunct(void* data, void* hashContext)), void* compContext, int32_t* compare(void* firstData, void* secondData, void* context));

hashtableReturnCodes replaceItem(hashtable* table, void* item, void* hashContext, int32_t (hashFunct(void* data, void* hashContext)), void* compContext, int32_t* compare(void* firstData, void* secondData, void* context));

void* containsItem(hashtable* table, void* item, void* hashContext, int32_t (hashFunct(void* data, void* hashContext)), void* compContext, int32_t compare(void* firstData, void* secondData, void* context));