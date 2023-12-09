#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "helper.h"

#define LINEBUFFER 40
#define MAXNUMRACES 4


static int adv2023p6() {
//int main() {
	FILE* fptr;
	errno_t error;
	char line[LINEBUFFER] = { '\0' };
	char* token = NULL;
	char* nextToken = NULL;
	int16_t raceTimes[MAXNUMRACES] = {0};
	int16_t raceDistances[MAXNUMRACES] = {0};
	int16_t index = 0;
	int8_t raceNumbers = 0;
	int64_t waysToWin = 1;
	int64_t counter = 0;
	int64_t sIndex = 0;
	int64_t realRaceTime = 0;
	int64_t realRaceDistance = 0;

	error = fopen_s(&fptr, "input2023p6.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		if (fgets(line, LINEBUFFER, fptr) != NULL) {
			token = strtok_s(line, " \n", &nextToken);
			while (token != NULL) {
				if (isDigit(token[0])) {
					raceTimes[index] = stoai(token);
					for (counter = 0; counter < strlen(token); counter++) {
						realRaceTime = realRaceTime * 10;
					}
					realRaceTime = realRaceTime + raceTimes[index];
					index++;
				}
				token = strtok_s(NULL, " \n", &nextToken);
			}
		}
		raceNumbers = index;
		index = 0;
		if (fgets(line, LINEBUFFER, fptr) != NULL) {
			token = strtok_s(line, " \n", &nextToken);
			while (token != NULL) {
				if (isDigit(token[0])) {
					raceDistances[index] = stoai(token);
					for (counter = 0; counter < strlen(token); counter++) {
						realRaceDistance = realRaceDistance * 10;
					}
					realRaceDistance = realRaceDistance + raceDistances[index];
					index++;
				}
				token = strtok_s(NULL, " \n", &nextToken);
			}
		}

		for (index = 0; index < raceNumbers; index++) {
			for (sIndex = 1; sIndex < raceTimes[index]; sIndex++) {
				if ((sIndex * (raceTimes[index] - sIndex)) > raceDistances[index]) {
					counter++;
				}
			}
			waysToWin = waysToWin * counter;
			counter = 0;
		}
		printf("Part 1 answer: %lld\n", waysToWin);
		for (sIndex = 1; sIndex < realRaceTime; sIndex++) {
			//printf("%d\n", sIndex);
			if ((sIndex * (realRaceTime - sIndex)) > realRaceDistance) {
				counter++;
			}
		}
		printf("Part 2 answer: %lld\n", counter);
	} else {
		printf("Failed to open file");
		return -1;
	}
	return 1;
}