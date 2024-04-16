#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compareTesting(const void* item1, const void* item2, const void* context);

static void testing() {
//main() {
	/*FILE* inputFile;
	FILE* outputFile;
	errno_t inputError;
	errno_t outputError;*/
	int64_t one = 1;
	int64_t two = 2;
	int64_t max = LLONG_MAX;
	int64_t min = LLONG_MIN;
	BinaryHeap heap = { .data = NULL, .dataSize = 0, .memSize = 0, .logicalSize = 0 };
	int64_t ans;
	setupHeap(&heap, sizeof(int64_t));
	insert(&heap, &max, NULL, &compareTesting);
	insert(&heap, &one, NULL, &compareTesting);
	insert(&heap, &two, NULL, &compareTesting);
	insert(&heap, &min, NULL, &compareTesting);
	while (heap.logicalSize > 0) {
		removeSmallest(&heap, NULL, &compareTesting, &ans);
		printf("%lld\n", ans);
	}
	insert(&heap, &max, NULL, &compareTesting);
	insert(&heap, &one, NULL, &compareTesting);
	insert(&heap, &two, NULL, &compareTesting);
	insert(&heap, &min, NULL, &compareTesting);
	while (heap.logicalSize > 0) {
		removeSmallest(&heap, NULL, &compareTesting, &ans);
		printf("%lld\n", ans);
	}
	insert(&heap, &one, NULL, &compareTesting);
	insert(&heap, &two, NULL, &compareTesting);
	insert(&heap, &max, NULL, &compareTesting);
	insert(&heap, &min, NULL, &compareTesting);
	while (heap.logicalSize > 0) {
		removeSmallest(&heap, NULL, &compareTesting, &ans);
		printf("%lld\n", ans);
	}
	deleteHeap(&heap);
}

static int compareTesting(const void* item1, const void* item2, const void* context) {
	int64_t i1 = *(int64_t*)item1;
	int64_t i2 = *(int64_t*)item2;
	//printf("i1: %lld, i2: %lld, ans: ", i1, i2);
	if (i1 > i2) {
		//printf("1\n");
		return 1;
	} else if (i1 < i2) {
		//printf("-1\n");
		return -1;
	}
	//printf("0\n");
	return 0;
}