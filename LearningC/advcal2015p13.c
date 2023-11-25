#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "namedmultinodeconnector.h"

//advcal2015p13() {
main() {
	FILE* fptr;
	errno_t error;
	char firstPerson[50] = { '\0' };
	char secondPerson[50] = { '\0' };
	char gOrL[5] = { '\0' };
	unsigned __int32 nameBuffer = 10;
	__int32 index = -1;
	__int32 happinessAmount = INT_MIN;
	__int32 tempHappinessAmount = 0;
	unsigned __int32 numPeople = 0;
	NamedMultiNode* head = NULL;


	error = fopen_s(&fptr, "input2015p13.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		//read input
		while (fscanf_s(fptr, "%9s would %4s %d happiness units by sitting next to %9s.", firstPerson,  nameBuffer, gOrL, 5, &tempHappinessAmount, secondPerson, nameBuffer) != EOF) {
			numPeople++;
			secondPerson[strlen(secondPerson) - 1] = '\0';
			if (gOrL[0] == 'l') {
				tempHappinessAmount *= -1;
			}
			if (head == NULL) {
				buildHead(&head, firstPerson, secondPerson, nameBuffer, tempHappinessAmount);
				attachToHeadSingleDirection(head, firstPerson, secondPerson, nameBuffer, tempHappinessAmount);
			}  else { 
				if (strcmp(firstPerson, head->name) == 0) {
					attachToHeadSingleDirection(head, firstPerson, secondPerson, nameBuffer, tempHappinessAmount);
				} else if (strcmp(head->name, secondPerson) == 0) {
					createPath(head->next[getIndex(head, firstPerson)]->next, head, tempHappinessAmount);
				} else {
					createPath(head->next[getIndex(head, firstPerson)]->next,
						head->next[getIndex(head, secondPerson)]->next, tempHappinessAmount);
				}
			}
		}
		index = -1;
		if (head != NULL) {
			while (index < head->numConnections) {
				if (index == -1) {
					happinessAmount = findHighestWeightPathHeadCircle(head);
				}
				else {
					tempHappinessAmount = findHighestWeightPathHeadCircle(head->next[index]->next);
					if (tempHappinessAmount > happinessAmount) {
						happinessAmount = tempHappinessAmount;
					}
				}
				index++;
			}
		}
		printf("Maximum happiness is: %d\n", happinessAmount);
	}
}
