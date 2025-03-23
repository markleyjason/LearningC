#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

hashtableReturnCodes setUpHashTable(hashtable* table, size_t numBuckets, size_t dataSize) {
	size_t index = 0;
	table->dataSize = dataSize;
	table->numBuckets = numBuckets;
	
	table->lists = malloc(numBuckets * sizeof(hashlist));
	if (table->lists == NULL) {
		return OUT_OF_MEMORY;
	}
	for (index = 0; index < numBuckets; index++) {
		table->lists[index].logicalSize = 0;
		table->lists[index].memSize = 8;
		table->lists[index].data = malloc(dataSize * 8);
		if (table->lists[index].data == NULL) {
			return OUT_OF_MEMORY;
		}
	}
	return SUCCESS;
}

hashtableReturnCodes insertHashTable(hashtable* table, void* item, void* context, int32_t (hashFunct(const void* data, const void* context))) {
	int32_t hash = hashFunct(item, context);
	void* temp = NULL;
	unsigned char* adding;
	unsigned char* itemMoving;
	errno_t error = 0;
	size_t movingSize = 0;
	hash = hash % table->numBuckets;

	if (table->lists[hash].logicalSize + 1 > table->lists[hash].memSize / 2) {
		temp = realloc((table->lists[hash].data), table->lists[hash].memSize * table->dataSize * 2);
		if (temp == NULL) {
			return OUT_OF_MEMORY;
		}
		table->lists[hash].data = temp;
		table->lists[hash].memSize = table->lists[hash].memSize * 2;
	}
	adding = table->lists[hash].data;
	movingSize = table->dataSize;
	itemMoving = item;
	while (movingSize > 0) {
		error = memcpy_s(adding + table->dataSize * table->lists[hash].logicalSize, movingSize, itemMoving, sizeof(char));
		adding++;
		itemMoving++;
		movingSize--;
	}
	if (error) {
		return COPY_ERROR;
	}
	table->lists[hash].logicalSize++;
	table->numItems++;
	return SUCCESS;
}

hashtableReturnCodes removeItem(hashtable* table, void* item, void* hashContext, int32_t(hashFunct(void* data, void* hashContext)), void* compContext, int32_t* compare(void* firstData, void* secondData, void* context)) {
	int32_t hash = hashFunct(item, hashContext);
	void* ans = NULL;
	unsigned char* read = NULL;
	size_t movingSize = 0;
	size_t index = 0;
	char* pointer = table->lists[hash].data;
	char found = 0;

	hash = hash % table->numBuckets;

	while (found == 0 && index < table->lists[hash].logicalSize) {
		if (compare((void*)(pointer + index * table->dataSize), item, compContext) == 0) {
			ans = (void*)(pointer + index * table->dataSize);
			found = 1;
		}
		index++;
	}
	if (found == 0) {
		return NO_ITEM;
	}

	movingSize = table->dataSize * (table->lists[hash].memSize - index - 1);
	read = ans;
	read = read + table->dataSize;
	index = table->dataSize * (table->lists[hash].memSize - index);
	memmove_s(ans, index, read, movingSize);
	table->lists[hash].logicalSize--;
	table->numItems--;
	return SUCCESS;
}

hashtableReturnCodes replaceItem(hashtable* table, void* item, void* hashContext, int32_t(hashFunct(void* data, void* hashContext)), void* compContext, int32_t* compare(void* firstData, void* secondData, void* context)) {
	int32_t hash = hashFunct(item, hashContext);
	void* ans = NULL;
	unsigned char* itemOverwriting = NULL;
	unsigned char* itemMoving = NULL;
	size_t movingSize = 0;
	size_t index = 0;
	char* pointer = table->lists[hash].data;
	char found = 0;

	hash = hash % table->numBuckets;

	while (found == 0 && index < table->lists[hash].logicalSize) {
		if (compare((void*)(pointer + index * table->dataSize), item, compContext) == 0) {
			ans = (void*)(pointer + index * table->dataSize);
			found = 1;
		}
		index++;
	}
	if (found == 0) {
		return NO_ITEM;
	}
	errno_t error = 0;
	itemOverwriting = ans;
	movingSize = table->dataSize;
	itemMoving = item;
	while (movingSize > 0) {
		error = memcpy_s(itemOverwriting + table->dataSize * table->lists[hash].logicalSize, movingSize, itemMoving, sizeof(char));
		itemOverwriting++;
		itemMoving++;
		movingSize--;
	}
	return SUCCESS;
}

void* containsItem(hashtable* table, void* item, void* hashContext, int32_t (hashFunct(void* data, void* hashContext)), void* compContext, int32_t compare(void* firstData, void* secondData, void* context)) {
	void* ans = NULL;
	int32_t hash = hashFunct(item, hashContext);
	hash = hash % table->numBuckets;
	size_t index = 0;
	char* pointer = table->lists[hash].data;
	char found = 0;

	while (found == 0 && index < table->lists[hash].logicalSize) {
		if (compare((void*)(pointer + index * table->dataSize), item, compContext) == 0) {
			ans = (void*)(pointer + index * table->dataSize);
			found = 1;
		}
		index++;
	}
	
	return ans;
}