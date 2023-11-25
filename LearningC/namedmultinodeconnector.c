#include <stdlib.h>
#include <string.h>
#include "namedmultinodeconnector.h"

void buildHead(NamedMultiNode** head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	*head = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if ((*head) != NULL) {
		strcpy_s((*head)->name, buffer, firstCity);
		(*head)->pathId = -1;
		(*head)->numConnections = 0;
	}
}

void attachToHeadBothDirections(NamedMultiNode* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	__int32 index = head->numConnections;
	NamedMultiNode* newCity = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
		createPath(newCity, head, travel);
	}
}

void attachToHeadSingleDirection(NamedMultiNode* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	__int32 index = head->numConnections;
	NamedMultiNode* newCity = (NamedMultiNode*)malloc(sizeof(NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
	}
}

void createPath(NamedMultiNode* first, NamedMultiNode* second, __int32 travel) {
	first->next[first->numConnections] = (NamedMultiNodeConnector*)malloc(sizeof(NamedMultiNodeConnector));
	if (first->next[first->numConnections] != NULL) {
		first->next[first->numConnections]->next = second;
		first->next[first->numConnections]->connecterWeight = travel;
		first->numConnections++;
	}

}

__int32 getIndex(NamedMultiNode* head, char* city) {
	__int32 index = 0;
	__int32 count = head->numConnections;
	while (index < count && strcmp(head->next[index]->next->name, city) != 0) {
		index++;
	}
	return index;
}

__int32 findLowestWeightPathHead(NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 pathWeight = INT_MAX;
	__int32 tempWeight;


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

__int32 findLowestWeightPath(NamedMultiNode* head, __int32 pathId) {
	__int32 index = 0;
	__int32 pathWeight = INT_MAX;
	__int32 tempWeight = 0;
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

__int32 findHighestWeightPathHead(NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 weight = INT_MIN;
	__int32 tempWeight;

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

__int32 findHighestWeightPath(NamedMultiNode* head, __int32 pathId) {
	__int32 index = 0;
	__int32 pathWeight = INT_MIN;
	__int32 tempWeight = 0;
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

__int32 findLowestWeightPathHeadCircle(NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MAX };
	__int32 pathLength = INT_MAX;

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

circle_return_value findLowestWeightPathCircle(NamedMultiNode* head, __int32 pathId, char callerName[NAME_LENGTH], char headName[NAME_LENGTH]) {
	__int32 index = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MAX };
	__int32 lowestWeight = INT_MAX;
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

__int32 findHighestWeightPathHeadCircle(NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 weight = INT_MIN;
	circle_return_value pathAnswer = { .name = '\0', .weight = 0 };

	while (index < head->numConnections) {
		printf("%s", head->name);
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

circle_return_value findHighestWeightPathCircle(NamedMultiNode* head, __int32 pathId, char callerName[NAME_LENGTH], char headName[NAME_LENGTH]) {
	__int32 index = 0;
	struct circle_return_value pathAnswer = { .name = '\0', .weight = 0 };
	__int32 highestWeight = INT_MIN;
	char foundChild = 0;

	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			printf(", %s", head->name);
			foundChild = 1;
			pathAnswer = findHighestWeightPathCircle(head->next[index]->next, pathId, head->name, headName);
			pathAnswer.weight += head->next[getIndex(head, callerName)]->connecterWeight + head->next[index]->connecterWeight;
			if (pathAnswer.weight > highestWeight) {
				highestWeight = pathAnswer.weight;
			}
		}
		index++;
	}
	head->pathId = -1;
	pathAnswer.weight = highestWeight;
	if (foundChild == 0) {
		strcpy_s(pathAnswer.name, NAME_LENGTH, head->name);
		index = getIndex(head, headName);
		pathAnswer.weight = head->next[index]->connecterWeight;
		index = getIndex(head, callerName);
		pathAnswer.weight += head->next[index]->connecterWeight;
		printf(", %s\n", head->name);
	}
	return pathAnswer;
}