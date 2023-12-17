#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "collections.h"

#define BUFFER 40

typedef struct HotSpring {
	IntegerArray runs;
	IntegerArray fixedLengthRuns;
	IntegerArray possibleLengthRuns[BUFFER];
	uint16_t possibleRuns;
}HotSpring;

static void findPossibleRuns(const char* line, HotSpring* answer);

main() {
	FILE* fptr;
	errno_t error;
	char line[BUFFER] = { '\0' };
	uint32_t index = 0;
	char* token1 = NULL;
	char* token2 = NULL;
	char* cont = NULL;
	HotSpring tempInformation;

	error = fopen_s(&fptr, "input2023p12.txt", "r");

	if (!error) {
		while (fgets(line, BUFFER, fptr) != NULL) {

			cont = NULL;
			token1 = strtok_s(line, " ", &cont);
			token2 = strtok_s(NULL, " \n", &cont);
			//need to break down the runs into possible combinations


		}
		close(fptr);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}

static void findPossibleRuns(const char* line, HotSpring* answer) {
	uint16_t index = 0;
	uint16_t size = 0;
	uint16_t count = 0;
	//move through the line till we come to a ? or # if #
	do {
		while (line[index] == '.') {
			index++;
		}
		if (line[index] != '?' && line[index] != '#') {
			
		}
	} while (line[index] == '.');
}