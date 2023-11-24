#include <stdlib.h>
#include <string.h>
#include "namedmultinodeconnector.h"

void buildHead(struct NamedMultiNode** head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	*head = (struct NamedMultiNode*)malloc(sizeof(struct NamedMultiNode));
	if ((*head) != NULL) {
		strcpy_s((*head)->name, buffer, firstCity);
		(*head)->pathId = -1;
		(*head)->numConnections = 0;
	}
}

void attachToHeadBothDirections(struct NamedMultiNode* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	__int32 index = head->numConnections;
	struct NamedMultiNode* newCity = (struct NamedMultiNode*)malloc(sizeof(struct NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
		createPath(newCity, head, travel);
	}
}

void attachToHeadSingleDirection(struct NamedMultiNode* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	__int32 index = head->numConnections;
	struct NamedMultiNode* newCity = (struct NamedMultiNode*)malloc(sizeof(struct NamedMultiNode));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
	}
}

void createPath(struct NamedMultiNode* first, struct NamedMultiNode* second, __int32 travel) {
	first->next[first->numConnections] = (struct NamedMultiNodeConnector*)malloc(sizeof(struct NamedMultiNodeConnector));
	if (first->next[first->numConnections] != NULL) {
		first->next[first->numConnections]->next = second;
		first->next[first->numConnections]->connecterWeight = travel;
		first->numConnections++;
	}

}

__int32 getIndex(struct NamedMultiNode* head, char* city) {
	__int32 index = 0;
	__int32 count = head->numConnections;
	while (index < count && strcmp(head->next[index]->next->name, city) != 0) {
		index++;
	}
	return index;
}

__int32 findLowestWeightPathHead(struct NamedMultiNode* head) {
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

__int32 findLowestWeightPath(struct NamedMultiNode* head, __int32 pathId) {
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

__int32 findHighestWeightPathHead(struct NamedMultiNode* head) {
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

__int32 findHighestWeightPath(struct NamedMultiNode* head, __int32 pathId) {
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

__int32 findLowestWeightPathHeadCircle(struct NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 pathLength = INT_MAX;
	__int32 tempWeight;


	while (index < head->numConnections) {
		head->pathId = index;
		tempWeight = findLowestWeightPath(head->next[index]->next, index, head->name) + head->next[index]->connecterWeight;
		if (tempWeight < pathLength) {
			pathLength = tempWeight;
		}
		index++;
	}
	return pathLength;
}

circle_return_value findLowestWeightPathCircle(struct NamedMultiNode* head, __int32 pathId, char headName[50]) {
	__int32 index = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MAX };
	__int32 tempWeight = 0;
	char foundChild = 0;


	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			tempWeight = findLowestWeightPathCircle(head->next[index]->next, pathId, headName[50]).weight + head->next[index]->connecterWeight;
			if (tempWeight < pathAnswer.weight) {
				pathAnswer.weight = tempWeight;
			}
		}
		index++;
	}
	head->pathId = -1;
	if (foundChild == 0) {
		strcpy_s(pathAnswer.name, 50, head->name);
		pathAnswer.weight = head->next[getIndex(head, headName)]->connecterWeight;
	}
	return pathAnswer;
}

//need store findLowest into a temp so I can grab both the weight and name and use that to calculate everything
__int32 findHighestWeightPathHeadCircle(struct NamedMultiNode* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 weight = INT_MIN;
	__int32 tempWeight;

	while (index < head->numConnections) {
		head->pathId = index;
		tempWeight = findLowestWeightPathCircle(head->next[index]->next, index, head->name).weight + head->next[index]->connecterWeight;
		if (tempWeight > weight) {
			weight = tempWeight;
		}
		index++;
	}
	return weight;
}

circle_return_value findHighestWeightPathCircle(struct NamedMultiNode* head, __int32 pathId, char headName[50]) {
	__int32 index = 0;
	circle_return_value pathAnswer = { .name = '\0', .weight = INT_MIN };
	__int32 tempWeight = 0;
	char foundChild = 0;


	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			foundChild = 1;
			tempWeight = findHighestWeightPathCircle(head->next[index]->next, pathId, headName[50]).weight + head->next[index]->connecterWeight;
			if (tempWeight > pathAnswer.weight) {
				pathAnswer.weight = tempWeight;
			}
		}
		index++;
	}
	head->pathId = -1;

	if (foundChild == 0) {
		strcpy_s(pathAnswer.name, 50, head->name);
		pathAnswer.weight = head->next[getIndex(head, headName)]->connecterWeight;
	}
	return pathAnswer;
}