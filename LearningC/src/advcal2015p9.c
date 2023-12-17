#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "namedmultinodeconnector.h"

adv2015p9() {
//main() {
	FILE* input;
	__int32 buffer = 50;
	char firstCity[50];
	char secondCity[50];
	__int32 travel = 0;
	__int32 pathLength = 0;
	__int32 tempPathLength = 0;
	__int32 numCities = 0;
	__int32 curCity = -1;
	struct NamedMultiNode* head = NULL;

	errno_t input_error;

	input_error = fopen_s(&input, "input2015p9.txt", "r");
	//input_error = fopen_s(&input, "testing_input.txt", "r");

	if (!input_error) {
		while (fscanf_s(input, "%s to %s = %d", firstCity, buffer, secondCity, buffer, &travel) != EOF) {
			numCities++;
			if (head == NULL) {
				buildHead(&head, firstCity, secondCity, buffer, travel);
				attachToHeadBothDirections(head, firstCity, secondCity, buffer, travel);
			} else {
				if (strcmp(firstCity, head->name) == 0) {
					attachToHeadBothDirections(head, firstCity, secondCity, buffer, travel);
				} else { // later city add it together (coud do both here first and second city just reverse)
					createPath(head->next[getIndex(head, firstCity)]->next,
						head->next[getIndex(head, secondCity)]->next, travel);
					createPath(head->next[getIndex(head, secondCity)]->next,
						head->next[getIndex(head, firstCity)]->next, travel);
				}
			}
		}
		if (head != NULL) {
			while (curCity < head->numConnections) {
				if (curCity == -1) {
					pathLength = findLowestWeightPathHead(head);
				}
				else {
					tempPathLength = findLowestWeightPathHead(head->next[curCity]->next);
					if (tempPathLength < pathLength) {
						pathLength = tempPathLength;
					}
				}
				curCity++;
			}
		}

		printf("The shortest path is: %d", pathLength);
		fclose(input);
	}
}
