#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#define STRINGBUFFER 175
#define MAXPULLS 20
#define MAXRED 12
#define MAXGREEN 13
#define MAXBLUE 14

advcal2023p2(){
//main() {
	FILE* fptr;
	errno_t error;
	unsigned __int32 gameId = 0;
	unsigned __int32 pullNum = 0;
	unsigned __int32 index = 0;
	unsigned __int32 tempRed = 0;
	unsigned __int32 tempBlue = 0;
	unsigned __int32 tempGreen = 0;
	unsigned __int32 highRed = 0;
	unsigned __int32 highBlue = 0;
	unsigned __int32 highGreen = 0;
	unsigned __int32 buildNum = 0;
	char possibleGame = 1;
	unsigned __int32 gameIdSum = 0;
	unsigned __int32 powerSetSum = 0;
	char line[STRINGBUFFER] = { '\0' };

	error = fopen_s(&fptr, "input2023p2.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, STRINGBUFFER - 1, fptr) != NULL) {
			index = 5;//start at the game id then find :
			while (line[index] != ':') {
				index++;
			}
			index += 2;
			while (index < STRINGBUFFER - 1 && line[index] != '\0') {
				if (line[index] == ' ') {
					//do nothing
				} else if (line[index] == ';' || line[index] == '\n' || line[index] == EOF) {
					if (pullNum == MAXPULLS) {
						printf("Error OVER MAX PULLS, gameid: %d\n", gameId + 1);
						exit(-1);
					}
					printf("GameId: %d, pull: %d, reds: %d, greens: %d, blues: %d\n", gameId + 1, pullNum, tempRed, tempGreen, tempBlue);
					pullNum++;
					if (tempRed > MAXRED || tempGreen > MAXGREEN || tempBlue > MAXBLUE) {
						possibleGame = 0;
					}
					if (highRed < tempRed) {
						highRed = tempRed;
					}
					if (highGreen < tempGreen) {
						highGreen = tempGreen;
					}
					if (highBlue < tempBlue) {
						highBlue = tempBlue;
					}
					tempRed = 0;
					tempGreen = 0;
					tempBlue = 0;
					buildNum = 0;
				} else if (line[index] == 'r') {
					tempRed = buildNum;
					buildNum = 0;
					index += 2;
				} else if (line[index] == 'g') {
					tempGreen = buildNum;
					buildNum = 0;
					index += 4;
				}else if(line[index] == 'b'){
					tempBlue = buildNum;
					buildNum = 0;
					index += 3;
				} else if (isDigit(line[index])) {
					buildNum = ctoai(line[index]) + buildNum * 10;
				}
				index++;
			}
			printf("GameId: %d power set: %d, r: %d, g: %d, b: %d\n", gameId + 1, highRed * highBlue * highGreen, highRed, highGreen, highBlue);
			powerSetSum += highRed * highBlue * highGreen;
			highRed = 0;
			highBlue = 0;
			highGreen = 0;
			if (possibleGame == 1) {
				gameIdSum += gameId + 1;
			}
			possibleGame = 1;
			gameId++;
			pullNum = 0;
		}
	}
	printf("Number of possible games: %d\n", gameIdSum);
	printf("Power set sum: %d\n", powerSetSum);
}