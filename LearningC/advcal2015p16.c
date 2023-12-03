#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#define NUMBER_SUES 500

struct Sue {
	__int32 children;
	__int32 cats;
	__int32 samoyeds;
	__int32 pomeranians;
	__int32 akitas;
	__int32 vizslas;
	__int32 goldfish;
	__int32 trees;
	__int32 cars;
	__int32 perfumes;
};

void addInformation(const __int32 workingSue, const char cat[12], const char number[3]);
__int32 returnNumMatches(const __int32 theSue);

struct Sue sues[NUMBER_SUES];

adv2015p16() {
//main() {
	FILE* fptr;
	errno_t error;
	char line[100];
	char catagorie[12] = { '\0' };
	char number[4] = { '\0' };
	__int32 highestMatches = INT_MIN;
	__int32 correctIndex = 0;
	__int32 matches = 0;
	__int32 index = 0;
	__int32 subIndex = 0;
	__int32 curSue = 0;

	for (index = 0; index < NUMBER_SUES; index++) {
		sues[index].children = -1;
		sues[index].cats = -1;
		sues[index].samoyeds = -1;
		sues[index].pomeranians = -1;
		sues[index].akitas = -1;
		sues[index].vizslas = -1;
		sues[index].goldfish = -1;
		sues[index].trees = -1;
		sues[index].cars = -1;
		sues[index].perfumes = -1;
	}

	error = fopen_s(&fptr, "input2015p16.txt", "r");
	
	if (!error) {
		while (fgets(line, 100, fptr) != NULL) {
			//break the into pieces
			index = 0;
			subIndex = 0;
			while (index < 100 && line[index] != '\0') {
				if (line[index] == ' ') {
					catagorie[subIndex] = '\0';
					subIndex = 0;
				} else if (line[index] == ':') {
					if (strcmp(catagorie, "Sue") == 0) {
						number[subIndex] = '\0';
						subIndex = 0;
						curSue = stoai(number) - 1;
					}
				} else if (line[index] == ',' || line[index] == '\n') {
					//update catagorie for the correct sue method?
					number[subIndex] = '\0';
					addInformation(curSue, catagorie, number);
				} else {
					if (isDigit(line[index])) {
						number[subIndex] = line[index];
					} else {
						catagorie[subIndex] = line[index];
					}
					subIndex++;
				}
				index++;
			}
		}

		//compare
		for (index = 0; index < NUMBER_SUES; index++) {
			matches = returnNumMatches(index);
			if (matches > highestMatches) {
				highestMatches = matches;
				correctIndex = index;
			}
		}
		printf("The correct Sue is: %d\n", correctIndex + 1);
	} else {
		printf("No such file\n");
	}
}

void addInformation(const __int32 workingSue, const char cat[12], const char number[3]) {
	if (cat[0] == 'c') {
		if (cat[1] == 'a') {
			if (cat[2] == 't') {
				sues[workingSue].cats = stoai(number);
			} else {
				sues[workingSue].cars = stoai(number);
			}
		} else {
			sues[workingSue].children = stoai(number);
		}
	} else {
		switch (cat[0]) {
		case 's':
			sues[workingSue].samoyeds = stoai(number);
			break;
		case 'p':
			if (cat[1] == 'o') {
				sues[workingSue].pomeranians = stoai(number);
			} else {
				sues[workingSue].perfumes = stoai(number);
			}
			break;
		case 'a':
			sues[workingSue].akitas = stoai(number);
			break;
		case 'v':
			sues[workingSue].vizslas = stoai(number);
			break;
		case 'g':
			sues[workingSue].goldfish = stoai(number);
			break;
		case 't':
			sues[workingSue].trees = stoai(number);
			break;
		}
	}
}

__int32 returnNumMatches(const __int32 theSue) {
	__int32 matches = 0;
	if (sues[theSue].children != 3 && sues[theSue].children != -1) {
		return -1;
	} else if(sues[theSue].children == 3){
		matches++;
	}
	if (sues[theSue].cats != -1) {
		if (sues[theSue].cats > 7) {
			matches++;
		} else {
			return -1;
		}
	}
	if (sues[theSue].samoyeds != 2 && sues[theSue].samoyeds != -1) {
		return -1;
	} else if (sues[theSue].samoyeds == 2) {
		matches++;
	}
	if (sues[theSue].pomeranians != -1) {
		if (sues[theSue].pomeranians < 3) {
			matches++;
		} else {
			return -1;
		}
	}
	if (sues[theSue].akitas != 0 && sues[theSue].akitas != -1) {
		return -1;
	} else if (sues[theSue].akitas == 0) {
		matches++;
	}
	if (sues[theSue].vizslas != 0 && sues[theSue].vizslas != -1) {
		return -1;
	} else if (sues[theSue].vizslas == 0) {
		matches++;
	}
	if (sues[theSue].goldfish != 5 && sues[theSue].goldfish != -1) {
		if (sues[theSue].goldfish < 5) {
			matches++;
		} else {
			return -1;
		}
	}
	if (sues[theSue].trees != 3 && sues[theSue].trees != -1) {
		if (sues[theSue].trees > 3) {
			matches++;
		} else {
			return -1;
		}
	}
	if (sues[theSue].cars != 2 && sues[theSue].cars != -1) {
		return -1;
	} else if (sues[theSue].cars == 2) {
		matches++;
	}
	if (sues[theSue].perfumes != 1 && sues[theSue].perfumes != -1) {
		return -1;
	} else if (sues[theSue].perfumes == 1) {
		matches++;
	}

	return matches;
}