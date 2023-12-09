#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "helper.h"

#define LINEBUFFER 210
#define RANGEINDEX 2
#define SOURCEINDEX 1
#define DESTINDEX 0

uint32_t ranges[50][3] = { {0} };

static void transform(const int32_t numRanges, const int32_t range[20][3],const int32_t numSeeds, int32_t* seeds);


int main() {
	FILE* fptr;
	errno_t error;
	uint32_t seeds[20] = { 0 };
	uint32_t index = 0;
	uint16_t numSeeds = 0;
	uint16_t numRanges = 0;
	uint32_t rmIndex = 0;
	uint16_t rsIndex = 0;
	char line[LINEBUFFER] = { '\0' };
	char* token = NULL;
	char* cont = NULL;
	char* returnVal;


	error = fopen_s(&fptr, "input2023p5.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		
		if (fgets(line, LINEBUFFER, fptr) != NULL) {
			printf(line);
			printf("\n");
			token = strtok_s(line, " ", &cont);
			while ((token = strtok_s(NULL, " \n", &cont)) != NULL) {
				seeds[numSeeds] = stoaui(token);
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
				printf("Transformations:\n");
				for (index = 0; index < numRanges; index++) {
					printf("%lu %lu %lu\n", ranges[index][DESTINDEX], ranges[index][SOURCEINDEX], ranges[index][RANGEINDEX]);
				}
				transform(numRanges, ranges, numSeeds, seeds);
				printf("Seeds transformed:\n");
				for (index = 0; index < numSeeds; index++) {
					printf("%lu\n", seeds[index]);
				}
			}
			rmIndex = INT_MAX;
			for (index = 0; index < numSeeds; index++) {
				if (rmIndex > seeds[index]) {
					rmIndex = seeds[index];
				}
			}
			printf("Next seed: %d", rmIndex);
		} else {
			printf("Failed to get the first line\n");
			return -1;
		}

		fclose(fptr);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 1;
}

static void transform(const int32_t numRanges, const int32_t range[20][3], const int32_t numSeeds, int32_t* seeds) {
	int32_t index = 0;
	int32_t rmIndex = 0;
	char switched = 0;

	for (index = 0; index < numSeeds; index++) {
		while (switched == 0 && rmIndex < numRanges) {
			if (seeds[index] >= range[rmIndex][SOURCEINDEX] && seeds[index] < range[rmIndex][SOURCEINDEX] + range[rmIndex][RANGEINDEX]) {
				seeds[index] = range[rmIndex][DESTINDEX] + range[rmIndex][RANGEINDEX] - (range[rmIndex][SOURCEINDEX] + range[rmIndex][RANGEINDEX] - seeds[index]);
				switched = 1;
			}
			rmIndex++;
		}
		switched = 0;
		rmIndex = 0;
	}
}