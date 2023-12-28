#include <stdlib.h>
#include <string.h>
#include "namedmultinodeconnector.h"

void buildHead(NamedMultiNode** head, char* firstCity, char* secondCity, int32_t buffer, int32_t travel) {
	*head = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if ((*head) != NULL) {
		strcpy_s((*head)->name, buffer, firstCity);
		(*head)->pathId = -1;
		(*head)->numConnections = 0;
	}
}

void attachToHeadBothDirections(NamedMultiNode* head, char* firstCity, char* secondCity, int32_t buffer, int32_t travel) {
	int32_t index = head->numConnections;
	NamedMultiNode* newCity = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
		createPath(newCity, head, travel);
	}
}

void attachToHeadSingleDirection(NamedMultiNode* head, char* firstCity, char* secondCity, int32_t buffer, int32_t travel) {
	int32_t index = head->numConnections;
	NamedMultiNode* newCity = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
	}
}

void createPath(NamedMultiNode* first, NamedMultiNode* second, int32_t travel) {
	first->next[first->numConnections] = (NamedMultiNodeConnector*)malloc(sizeof(NamedMultiNodeConnector));
	if (first->next[first->numConnections] != NULL) {
		first->next[first->numConnections]->next = second;
		first->next[first->numConnections]->connecterWeight = travel;
		first->numConnections++;
	}

}

int32_t getIndex(const NamedMultiNode* head, const char* city) {
	int32_t index = 0;
	int32_t count = head->numConnections;
	while (index < count && strcmp(head->next[index]->next->name, city) != 0) {
		index++;
	}
	return index;
}

int32_t findLowestWeightPathHead(NamedMultiNode* head) {
	int32_t index = 0;
	int32_t curCity = 0;
	int32_t pathWeight = INT_MAX;
	int32_t tempWeight;


	while (index < head->numConnections) {
		head->pathId = index;
		tempWeight = findLowestWeightPath(head->next[index]->next, index) + head->next[index]->connecterWeight;
		if (tempWeight < pathWeight) {
			pathWeight = tempWeight;
		}
		index++;
	}
	return pathWeight;
}

int32_t findLowestWeightPath(NamedMultiNode* head, int32_t pathId) {
	int32_t index = 0;
	int32_t pathWeight = INT_MAX;
	int32_t tempWeight = 0;
	char foundChild = 0;


	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			tempWeight = findLowestWeightPath(head->next[index]->next, pathId) + head->next[index]->connecterWeight;
			if (tempWeight < pathWeight) {
				pathWeight = tempWeight;
			}
		}
		index++;
	}
	head->pathId = -1;
	if (foundChild == 0) {
		pathWeight = 0;
	}
	return pathWeight;
}

int32_t findHighestWeightPathHead(NamedMultiNode* head) {
	int32_t index = 0;
	int32_t curCity = 0;
	int32_t weight = INT_MIN;
	int32_t tempWeight;

	while (index < head->numConnections) {
		head->pathId = index;
		tempWeight = findLowestWeightPath(head->next[index]->next, index) + head->next[index]->connecterWeight;
		if (tempWeight > weight) {
			weight = tempWeight;
		}
		index++;
	}
	return weight;
}

int32_t findHighestWeightPath(NamedMultiNode* head, int32_t pathId) {
	int32_t index = 0;
	int32_t pathWeight = INT_MIN;
	int32_t tempWeight = 0;
	char foundChild = 0;


	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			tempWeight = findHighestWeightPath(head->next[index]->next, pathId) + head->next[index]->connecterWeight;
			if (tempWeight > pathWeight) {
				pathWeight = tempWeight;
			}
		}
		index++;
	}
	head->pathId = -1;
	if (foundChild == 0) {
		pathWeight = 0;
	}
	return pathWeight;
}

int32_t findLowestWeightPathHeadCircle(NamedMultiNode* head) {
	int32_t index = 0;
	int32_t curCity = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MAX };
	int32_t pathLength = INT_MAX;

	while (index < head->numConnections) {
		head->pathId = index;
		pathAnswer = findLowestWeightPathCircle(head->next[index]->next, index, head->name, head->name);
		pathAnswer.weight += head->next[index]->connecterWeight + head->next[getIndex(head, pathAnswer.name)]->connecterWeight;
		if (pathAnswer.weight < pathLength) {
			pathLength = pathAnswer.weight;
		}
		index++;
	}
	return pathLength;
}

circle_return_value findLowestWeightPathCircle(NamedMultiNode* head, int32_t pathId, char callerName[NAME_LENGTH], char headName[NAME_LENGTH]) {
	int32_t index = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MAX };
	int32_t lowestWeight = INT_MAX;
	char foundChild = 0;

	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			pathAnswer = findLowestWeightPathCircle(head->next[index]->next, pathId, head->name, headName);
			pathAnswer.weight += head->next[getIndex(head, callerName)]->connecterWeight + head->next[index]->connecterWeight;
			if (pathAnswer.weight < lowestWeight) {
				lowestWeight = pathAnswer.weight;
			}
		}
		index++;
	}
	head->pathId = -1;
	pathAnswer.weight = lowestWeight;
	if (foundChild == 0) {
		strcpy_s(pathAnswer.name, NAME_LENGTH, head->name);
		index = getIndex(head, headName);
		pathAnswer.weight = head->next[index]->connecterWeight;
		index = getIndex(head, callerName);
		pathAnswer.weight += head->next[index]->connecterWeight;
	}
	return pathAnswer;
}

int32_t findHighestWeightPathHeadCircle(NamedMultiNode* head) {
	int32_t index = 0;
	int32_t curCity = 0;
	int32_t weight = INT_MIN;
	circle_return_value pathAnswer;

	while (index < head->numConnections) {
		head->pathId = index;
		pathAnswer = findHighestWeightPathCircle(head->next[index]->next, index, head->name, head->name);
		pathAnswer.weight += head->next[index]->connecterWeight + head->next[getIndex(head, pathAnswer.name)]->connecterWeight;
		if (pathAnswer.weight > weight) {
			weight = pathAnswer.weight;
		}
		index++;
	}
	return weight;
}

circle_return_value findHighestWeightPathCircle(NamedMultiNode* head, const int32_t pathId, const char callerName[NAME_LENGTH],const char headName[NAME_LENGTH]) {
	int32_t index = 0;
	circle_return_value pathAnswer;
	circle_return_value bestAnswer = { .name = {'\0' }, .weight = INT_MIN };
	char foundChild = 0;

	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			pathAnswer = findHighestWeightPathCircle(head->next[index]->next, pathId, head->name, headName);
			pathAnswer.weight += head->next[getIndex(head, callerName)]->connecterWeight + head->next[index]->connecterWeight;
			if (pathAnswer.weight > bestAnswer.weight) {
				bestAnswer.weight = pathAnswer.weight;
				strcpy_s(bestAnswer.name, NAME_LENGTH, pathAnswer.name);
			}
		}
		index++;
	}
	head->pathId = -1;
	if (foundChild == 0) {
		strcpy_s(bestAnswer.name, NAME_LENGTH, head->name);
		index = getIndex(head, headName);
		bestAnswer.weight = head->next[index]->connecterWeight;
		index = getIndex(head, callerName);
		bestAnswer.weight += head->next[index]->connecterWeight;
	}
	return bestAnswer;
}