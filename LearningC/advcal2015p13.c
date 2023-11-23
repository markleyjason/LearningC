#include <stdio.h>
#include <string.h>


typedef struct SeatingHappiness {
	char mainPerson[10];
	__int32 happinessChange;
	char seatedNextTo[10];
}SeatingHappiness;

main() {
	FILE* fptr;
	errno_t error;
	SeatingHappiness happinessGrid[8][7];
	unsigned __int32 nameBuffer = 10;
	SeatingHappiness tempPerson = { .mainPerson = { '\0' }, .happinessChange = 0, .seatedNextTo = { '\0' } };
	unsigned __int32 index = 0;
	char gOrL[5] = { '\0' };
	unsigned __int32 mainIndex = 0;
	unsigned __int32 subIndex = 0;


	error = fopen_s(&fptr, "input2015p13.txt", "r");

	if (!error) {
		//read input
		while (fscanf_s(fptr, "%9s would %4s %d happiness units by sitting next to %9s.", tempPerson.mainPerson, nameBuffer, gOrL, 5, &tempPerson.happinessChange, tempPerson.seatedNextTo, nameBuffer) != EOF) {
			if (gOrL[0] == 'l') {
				tempPerson.happinessChange *= -1;
			}
			tempPerson.seatedNextTo[strlen(tempPerson.seatedNextTo) - 1] = '\0';
			printf("Temp person is: %s, Temp happiness change is: %d, seated next to: %s\n", tempPerson.mainPerson, tempPerson.happinessChange, tempPerson.seatedNextTo);
			//happinessGrid[0][0].mainPerson[0] = tempPerson.seatedNextTo[0];
			strcpy_s(happinessGrid[mainIndex][subIndex].mainPerson, nameBuffer, tempPerson.mainPerson);
			printf("Testing: %s\n", happinessGrid[mainIndex][subIndex].mainPerson);
			subIndex++;
			if (subIndex > 6) {
				subIndex = 0;
				mainIndex++;
			}
		}
		//finding seating happiness
	}
}