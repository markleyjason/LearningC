#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "helper.h"

#define LINEBUFFER 150

static int32_t nextNumber(int32_t lineNumbers[], int16_t nums);
static int32_t prevNumber(int32_t lineNumbers[], int16_t nums);

adv2023p9(){
//main() {
	FILE* fptr;
	errno_t error;
	int32_t lineNumbers[21] = { 0 };
	int16_t index = 0;
	int32_t sum = 0;
	int32_t sum2 = 0;
	char line[LINEBUFFER] = { '\0' };
	char* token = NULL;
	char* nextTok = NULL;

	error = fopen_s(&fptr, "input2023p9.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while(fgets(line, LINEBUFFER, fptr) != NULL) {
			index = 0;
			token = strtok_s(line, " \n", &nextTok);
			while (token != NULL) {
				lineNumbers[index] = stoai(token);
				index++;
				token = strtok_s(NULL, " \n", &nextTok);
			}
			sum += nextNumber(lineNumbers, index);
			sum2 += prevNumber(lineNumbers, index);
		}
		
		fclose(fptr);
		printf("The part 1 sum is: %d\n", sum);
		printf("The part 2 sum is: %d\n", sum2);
	} else {
		printf("Can open file\n");
	}
	return 0;
}

static int32_t nextNumber(int32_t lineNumbers[], int16_t nums) {
	int32_t newLines[21][21] = { 0 };
	int32_t extras[21] = { 0 };
	int16_t index = 0;
	int16_t sindex = 0;
	int16_t numZeroes = 0;
	nums--;

	//first pass use the passed in array
	for (index = 0; index < nums; index++) {
		newLines[sindex][index] = lineNumbers[index + 1] - lineNumbers[index];
		if (newLines[sindex][index] == 0) {
			numZeroes++;
		}
	}
	while (numZeroes != nums) {
		numZeroes = 0;
		nums--;
		sindex++;
		for (index = 0; index < nums; index++) {
			newLines[sindex][index] = newLines[sindex - 1][index + 1] - newLines[sindex - 1][index];
			if (newLines[sindex][index] == 0) {
				numZeroes++;
			}
		}
	}
	for (; sindex > 0; sindex--) {
		extras[sindex] = extras[sindex + 1] + newLines[sindex - 1][nums];
		nums++;
	}
	extras[0] = lineNumbers[nums] + extras[1];
	return extras[0];
}

static int32_t prevNumber(int32_t lineNumbers[], int16_t nums) {
	int32_t newLines[21][21] = { 0 };
	int32_t extras[21] = { 0 };
	int16_t index = 0;
	int16_t sindex = 0;
	int16_t numZeroes = 0;
	nums--;

	//first pass use the passed in array
	for (index = 0; index < nums; index++) {
		newLines[sindex][index] = lineNumbers[index + 1] - lineNumbers[index];
		if (newLines[sindex][index] == 0) {
			numZeroes++;
		}
	}
	while (numZeroes != nums) {
		numZeroes = 0;
		nums--;
		sindex++;
		for (index = 0; index < nums; index++) {
			newLines[sindex][index] = newLines[sindex - 1][index + 1] - newLines[sindex - 1][index];
			if (newLines[sindex][index] == 0) {
				numZeroes++;
			}
		}
	}
	for (; sindex > 0; sindex--) {
		extras[sindex] = newLines[sindex - 1][0] - extras[sindex + 1];
	}
	extras[0] = lineNumbers[0] - extras[1];
	return extras[0];
}
