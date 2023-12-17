#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "helper.h"
#include "collections.h"

#define LINEBUFFER 210
#define RANGEINDEX 2
#define SOURCEINDEX 1
#define DESTINDEX 0

static uint32_t ranges[50][3] = { {0} };
static uint16_t numRanges = 0;

static IntegerArray* part2Array;

static void transform(const int32_t numSeeds, uint32_t* seeds);
static void transformPart2();

static int adv2023p6(){
//int main() {
	FILE* fptr;
	errno_t error;
	uint32_t seeds[20] = { 0 };
	uint32_t index = 0;
	uint16_t numSeeds = 0;
	uint32_t rmIndex = 0;
	uint16_t rsIndex = 0;
	int32_t max;
	char line[LINEBUFFER] = { '\0' };
	char* token = NULL;
	char* cont = NULL;
	char* returnVal;

	part2Array = setupIntegerArray(200);

	error = fopen_s(&fptr, "input2023p5.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		
		if (fgets(line, LINEBUFFER, fptr) != NULL) {
			printf(line);
			printf("\n");
			token = strtok_s(line, " ", &cont);
			while ((token = strtok_s(NULL, " \n", &cont)) != NULL) {
				seeds[numSeeds] = stoaui(token);
				appendIntegerArray(part2Array, stoai(token));
				numSeeds++;
			}
			cont = NULL;
			token = NULL;
			fgets(line, LINEBUFFER, fptr);
			while (fgets(line, LINEBUFFER, fptr) != NULL) {
				token = NULL;
				cont = NULL;
				numRanges = 0;
				rsIndex = 0;
				returnVal = fgets(line, LINEBUFFER, fptr);
				while (returnVal != NULL && line[0] != '\n') {
					token = strtok_s(line, " ", &cont);
					do {
						ranges[numRanges][rsIndex] = stoaui(token);
						rsIndex++;
					} while ((token = strtok_s(NULL, " \n", &cont)) != NULL);
					rsIndex = 0;
					numRanges++;
					returnVal = fgets(line, LINEBUFFER, fptr);
				}
				/*printf("Transformations:\n");
				for (index = 0; index < numRanges; index++) {
					printf("%lu %lu %lu\n", ranges[index][DESTINDEX], ranges[index][SOURCEINDEX], ranges[index][RANGEINDEX]);
				}*/
				transform(numSeeds, seeds);
				transformPart2();
				/*printf("Seeds transformed part 1:\n");
				for (index = 0; index < numSeeds; index++) {
					printf("%lu\n", seeds[index]);
				}
				printf("Seeds transformed part 2:\n");
				for (index = 0; index < part2Array->logicalSize; index++) {
					printf("%ld\n", part2Array->data[index]);
				}*/
			}
			rmIndex = UINT32_MAX;
			for (index = 0; index < numSeeds; index++) {
				if (rmIndex > seeds[index]) {
					rmIndex = seeds[index];
				}
			}
			printf("Next seed: %d\n", rmIndex);
			max = INT32_MAX;
			for (index = 0; index < part2Array->logicalSize; index+=2) {
				if (max > part2Array->data[index]) {
					max = part2Array->data[index];
				}
			}
			printf("Next seed part 2: %d\n", max);
		} else {
			printf("Failed to get the first line\n");
			return -1;
		}

		fclose(fptr);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}

static void transform(const int32_t numSeeds, uint32_t* seeds) {
	int32_t index = 0;
	int32_t rmIndex = 0;
	char switched = 0;

	for (index = 0; index < numSeeds; index++) {
		while (switched == 0 && rmIndex < numRanges) {
			if (seeds[index] >= ranges[rmIndex][SOURCEINDEX] && seeds[index] < ranges[rmIndex][SOURCEINDEX] + ranges[rmIndex][RANGEINDEX]) {
				seeds[index] = ranges[rmIndex][DESTINDEX] + ranges[rmIndex][RANGEINDEX] - (ranges[rmIndex][SOURCEINDEX] + ranges[rmIndex][RANGEINDEX] - seeds[index]);
				switched = 1;
			}
			rmIndex++;
		}
		switched = 0;
		rmIndex = 0;
	}
}

static void transformPart2() {
	size_t index = 0;
	int16_t rmIndex = 0;
	char switched = 0;
	int32_t startNumber = 0;
	int32_t newRange = 0;

	for (index = 0; index < part2Array->logicalSize; index += 2) {
		for (rmIndex = 0; rmIndex < numRanges; rmIndex++) {
			if (ranges[rmIndex][SOURCEINDEX] < part2Array->data[index] && part2Array->data[index] < (ranges[rmIndex][SOURCEINDEX] + ranges[rmIndex][RANGEINDEX])) {
				if (part2Array->data[index] + part2Array->data[index + 1] > (part2Array->data[index] + ranges[rmIndex][RANGEINDEX])) {
					newRange = part2Array->data[index] + part2Array->data[index + 1] - ranges[rmIndex][SOURCEINDEX] - ranges[rmIndex][RANGEINDEX];
					startNumber = part2Array->data[index] + part2Array->data[index + 1] - ranges[rmIndex][RANGEINDEX] - 1;
					part2Array->data[index + 1] = part2Array->data[index + 1] - newRange;
					insertIntegerArray(part2Array, startNumber, index + 2);
					insertIntegerArray(part2Array, newRange, index + 3);
				}
			} else if (ranges[rmIndex][SOURCEINDEX] > part2Array->data[index] && (part2Array->data[index] + part2Array->data[index + 1]) > ranges[rmIndex][SOURCEINDEX]) {
				newRange = part2Array->data[index] + part2Array->data[index + 1] - ranges[rmIndex][SOURCEINDEX];
				startNumber = ranges[rmIndex][SOURCEINDEX];
				part2Array->data[index + 1] = part2Array->data[index + 1] - newRange;
				insertIntegerArray(part2Array, startNumber, index + 2);
				insertIntegerArray(part2Array, newRange, index + 3);
			}
		}
	}
	for (index = 0; index < part2Array->logicalSize; index+=2) {
		switched = 0;
		rmIndex = 0;
		while (switched == 0 && rmIndex < numRanges) {
			if (part2Array->data[index] >= ranges[rmIndex][SOURCEINDEX] && part2Array->data[index] < ranges[rmIndex][SOURCEINDEX] + ranges[rmIndex][RANGEINDEX]) {
				part2Array->data[index] = ranges[rmIndex][DESTINDEX] + ranges[rmIndex][RANGEINDEX] - (ranges[rmIndex][SOURCEINDEX] + ranges[rmIndex][RANGEINDEX] - part2Array->data[index]);
				switched = 1;
			}
			rmIndex++;
		}
	}
}