#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

#define NUMBERS 25
#define WINNINGNUMBERS 10
#define INPUTBUFFER 117

adv2023p4(){
//main() {
	FILE* fptr;
	errno_t error;
	char line[INPUTBUFFER] = { '\0' };
	unsigned __int32 sum = 0;
	unsigned __int32 gameScore = 0;
	unsigned __int32 index = 0;
	unsigned __int32 winInd = 0;
	unsigned __int32 winTop = 0;
	unsigned __int32 temp = 0;
	unsigned __int32 cardCount = 0;
	unsigned __int32 winningNums[WINNINGNUMBERS] = { 0 };
	int cardLoop[200] = {1};
	unsigned __int32 cardIndex = 0;
	unsigned __int32 winCount = 0;

	for (index = 0; index < 200; index++) {
		cardLoop[index] = 1;
	}
	index = 0;

	error = fopen_s(&fptr, "input2023p4.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");
	
	if (!error) {
		while (fgets(line, INPUTBUFFER, fptr) != NULL) {
			if (strlen(line) == 0) {
				break;
			} else if (strlen(line) != 1) {
				while (line[index] != ':') {
					index++;
				}
				index += 2;
				while (line[index] != '\0') {
					if (isDigit(line[index])) {
						temp = temp * 10 + ctoai(line[index]);
					} else if (line[index] == ' ' || line[index] == '\n') {
						if (temp > 0) {
							if (winTop == 0) {
								winningNums[winInd] = temp;
								winInd++;
								temp = 0;
							} else {
								for (winInd = 0; winInd < winTop; winInd++) {
									if (winningNums[winInd] == temp) {
										winCount++;
										if (gameScore == 0) {
											gameScore = 1;
										} else {
											gameScore *= 2;
										}
									}
								}
							}
							temp = 0;
						}
					} else	if (line[index] == '|') {
						winTop = winInd;
						temp = 0;
					}
					index++;
				}
				if (temp != 0) {
					for (winInd = 0; winInd < winTop; winInd++) {
						if (winningNums[winInd] == temp) {
							winCount++;
							if (gameScore == 0) {
								gameScore = 1;
							} else {
								gameScore *= 2;
							}
						}
					}
				}
				for (index = cardIndex + 1; index < cardIndex + 1 + winCount; index++) {
					cardLoop[index] += cardLoop[cardIndex];
				}
				sum += gameScore;
				gameScore = 0;
				winTop = 0;
				winInd = 0;
				index = 0;
				temp = 0;
				winCount = 0;
				cardCount += cardLoop[cardIndex];
				cardIndex++;
			}
		}
		fclose(fptr);
		printf("Game score: %d\n", sum);
		printf("Total cards: %d\n", cardCount);
	}
}