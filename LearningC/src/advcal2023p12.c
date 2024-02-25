#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "helper.h"
#include "hashtable.h"

#define BUFFER 300

typedef struct HotSpring {
	uint32_t lengths[50];
	uint32_t numberOfLengths;
}HotSpring;

typedef struct previousFindsParts {
	uint32_t numLengths;
	uint32_t numbers[50];
	uint64_t count;
	uint16_t seqSize;
	char sequence[BUFFER];
}previousFindsParts;

static hashtable previousFound = { .dataSize = sizeof(previousFindsParts), .lists = NULL, .numBuckets = 1 };
static size_t listSize;
static size_t memListSize;

static uint64_t findPossibleRunsOrder(char* line, const HotSpring numbers);
static char possibleMatch(char* line, uint16_t length, uint16_t start);
static void combineLinesAfter(char* lines[BUFFER], uint16_t num_lines, uint16_t spcIndex, uint16_t start, uint16_t end, char* ans);
static int8_t lineCheck(const char* line, const uint16_t start);
int32_t pfpHashFunc(const void* item, const void* context);
int32_t comparePFPAdv(const void* item1, const void* item2, const void* context);

static int advcal23p12(){
//main() {
	FILE* fptr;
	errno_t error;
	char line[BUFFER] = { '\0' };
	char linePart2[BUFFER] = { '\0' };
	char* token1 = NULL;
	char* token2 = NULL;
	char* context = NULL;
	HotSpring tempInformation = { .lengths = {0}, .numberOfLengths = 0 };
	HotSpring tempInformationPart2 = { .lengths = {0}, .numberOfLengths = 0 };
	uint32_t sum = 0;
	uint64_t sumPart2 = 0;
	uint32_t index = 0;
	uint32_t indexLen = 0;
	uint32_t counting = 0;
	hashtableReturnCodes returnValues = SUCCESS;
	clock_t start, end;
	double dif;
	

	listSize = 0;
	memListSize = 1000;
	returnValues = setUpHashTable(&previousFound, 2345, sizeof(previousFindsParts));
	if (returnValues != SUCCESS) {
		return returnValues;
	}

	error = fopen_s(&fptr, "input2023p12.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");

	if (!error) {
		while (fgets(line, BUFFER, fptr) != NULL) {
			start = clock();
			context = NULL;
			token1 = strtok_s(line, " \n", &context);
			token2 = strtok_s(NULL, ",\n", &context);
			while (token2 != NULL) {
				tempInformation.lengths[tempInformation.numberOfLengths] = stoai(token2);
				tempInformation.numberOfLengths++;
				token2 = strtok_s(NULL, ", \n", &context);
			}
			for (index = 0; index < 5; index++) {
				strcat_s(linePart2, BUFFER, token1);
				strcat_s(linePart2, BUFFER, "?");
				for (indexLen = 0; indexLen < tempInformation.numberOfLengths; indexLen++) {
					tempInformationPart2.lengths[tempInformationPart2.numberOfLengths] = tempInformation.lengths[indexLen];
					tempInformationPart2.numberOfLengths++;
				}
			}
			linePart2[strlen(linePart2) - 1] = '\0';
			sum += findPossibleRunsOrder(token1, tempInformation);
			sumPart2 += findPossibleRunsOrder(linePart2, tempInformationPart2);
			//printf("Answer: %llu\n", sumPart2);
			end = clock();
			dif = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
			//printf("Time spent: %f\n", dif);
			index = strlen(linePart2);
			for (indexLen = 0; indexLen < BUFFER; indexLen++) {
				linePart2[indexLen] = '\0';
			}
			tempInformation.numberOfLengths = 0;
			tempInformationPart2.numberOfLengths = 0;
		}
		fclose(fptr);
		printf("Sum of possible positions: %d\n", sum);
		printf("Sum of possible positions part 2: %llu\n", sumPart2);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}

static uint64_t findPossibleRunsOrder(char* line, const HotSpring answer) {
	uint32_t index = 0;
	uint32_t size = 0;
	uint32_t start = 0;
	int64_t count = 0;
	HotSpring newHotSpring = { .numberOfLengths = answer.numberOfLengths - 1, .lengths = {0} };
	char nextLine[BUFFER] = { '\0' };
	char* test = NULL;
	char* lines[BUFFER] = { '\0' };
	char* context = NULL;
	hashtableReturnCodes val = SUCCESS;
	previousFindsParts item = { .numLengths = answer.numberOfLengths, .numbers = answer.lengths, .seqSize = strlen(line), .sequence = "" };
	strcpy_s(item.sequence, BUFFER, line);
	
	for (index = 1; index < answer.numberOfLengths; index++) {
		newHotSpring.lengths[index - 1] = answer.lengths[index];
		item.numbers[index] = answer.lengths[index];
	}
	item.numbers[0] = answer.lengths[0];
	void* ans = containsItem(&previousFound, (void*) & item, NULL, &pfpHashFunc, NULL, &comparePFPAdv);
	if (ans != NULL) {
		//printf("%d, %s\n", ((previousFindsParts*)ans)->count, ((previousFindsParts*)ans)->sequence);
		return ((previousFindsParts*)ans)->count;
	}
	count = 0;

	if (answer.numberOfLengths == 0) {
		index = strlen(line);
		if (index == 0) {
			item.count = 1;
			insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
			return 1;
		}
		
		lines[0] = strtok_s(line, "#", &context);
		if (index == strlen(lines[0])) {
			item.count = 1;
			insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
			return 1;
		}
		item.count = 0;
		insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
		return 0;
	}

	

	lines[size] = strtok_s(line, ".", &context);
	while (lines[size] != NULL) {
		size++;
		lines[size] = strtok_s(NULL, ".", &context);
	}

	index = 0;
	while (index < size) {
		if (index > 0) {
			if (lineCheck(lines[index - 1], strlen(lines[index - 1])) == -1) {
				item.count = count;
				insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
				return count;
			}
		}
		if (strlen(lines[index]) == answer.lengths[0]) {
			combineLinesAfter(lines, size, index, 0, answer.lengths[0], nextLine);
			count += findPossibleRunsOrder(nextLine, newHotSpring);
			nextLine[0] = '\0';
		} else if (strlen(lines[index]) > answer.lengths[0]) {
			start = 0;
			while (start + answer.lengths[0] <= strlen(lines[index])) {
				if (lineCheck(lines[index], start) == -1) {
					item.count = count;
					insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
					return count;
				}
				if (possibleMatch(lines[index], answer.lengths[0], start) == 1) {
					combineLinesAfter(lines, size, index, start, start + answer.lengths[0], nextLine);
					count += findPossibleRunsOrder(nextLine, newHotSpring);
					nextLine[0] = '\0';
				}
				start++;
			}
		}
		index++;
	}
	item.count = count;
	insertHashTable(&previousFound, &item, NULL, &pfpHashFunc);
	return count;
}

static char possibleMatch(char* line, uint16_t length, uint16_t start) {
	char ans = -1;
	if (start != 0) {
		if (line[start - 1] != '#' && line[start + length] != '#') {
			ans = 1;
		}
	} else {
		if (line[start + length] != '#') {
			ans = 1;
		}
	}
	return ans;
}

static void combineLinesAfter(char* lines[BUFFER], uint16_t num_lines, uint16_t spcIndex, uint16_t start, uint16_t end, char* ans) {
	uint32_t index;
	uint32_t read = 0;
	uint32_t write = 0;

	for (index = spcIndex; index < num_lines; index++) {
		if (index == spcIndex) {
			if (end < strlen(lines[index])) {
				read = end + 1;
				while (read < strlen(lines[index])) {
					ans[write] = lines[index][read];
					write++;
					read++;
				}
				ans[write] = '.';
				ans[write + 1] = '\0';
			}
		} else {
			read = 0;
			write = strlen(ans);
			while (read < strlen(lines[index])) {
				ans[write] = lines[index][read];
				write++;
				read++;
			}
			ans[write] = '.';
			ans[write + 1] = '\0';
		}
	}
}

static void combineLines(char* lines[20], uint16_t num_lines, uint16_t spcIndex, uint16_t start, uint16_t end, char* ans) {
	uint16_t index = 0;
	uint16_t read = 0;
	uint16_t write = 0;
	for (index = 0; index < num_lines; index++) {
		if (index == spcIndex) {
			if (start != 0 || end < strlen(lines[index])) {
				read = 0;
				write = strlen(ans);
				while (read < start - 1) {
					ans[write] = lines[index][read];
					write++;
					read++;
				}
				read = end + 1;
				while (read < strlen(lines[index])) {
					ans[write] = lines[index][read];
					write++;
					read++;
				}
				ans[write] = '.';
				ans[write + 1] = '\0';
			}
		} else {
			read = 0;
			write = strlen(ans);
			while (read < strlen(lines[index])) {
				ans[write] = lines[index][read];
				write++;
				read++;
			}
			ans[write] = '.';
			ans[write + 1] = '\0';
		}
	}
}

static int8_t lineCheck(const char* line, const uint16_t start) {
	uint32_t index;
	for (index = 0; index < start; index++) {
		if (line[index] == '#') {
			return -1;
		}
	}
	return 1;
}

int32_t pfpHashFunc(const void* item, const void* context) {
	int32_t hash = 0;
	previousFindsParts theItem = *(previousFindsParts*)item;
	hash = ((theItem.numLengths * theItem.numbers[0] - theItem.seqSize)) * (theItem.seqSize + theItem.sequence[0]);
	return hash;
}

int32_t comparePFPAdv(const void* item1, const void* item2, const void* context) {
	previousFindsParts firstItem = *(previousFindsParts*)item1;
	previousFindsParts secondItem = *(previousFindsParts*)item2;
	int16_t index = 0;
	if (firstItem.numLengths == secondItem.numLengths) {
		if (firstItem.seqSize == secondItem.seqSize) {
			for (index = 0; index < firstItem.numLengths; index++) {
				if (firstItem.numbers[index] != secondItem.numbers[index]) {
					return 1;
				}
			}
			return strcmp(firstItem.sequence, secondItem.sequence);
		}
	}
	return -1;
}