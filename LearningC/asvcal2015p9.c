#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Connector {
	struct Node* next;
	__int32 distance;
};

struct Node {
	struct Connector* next[7];
	char name[50];
	__int32 numConnections;
	__int32 pathId;
};

void buildHead(struct Node** head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel);
void attachToHead(struct Node* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel);
void createPath(struct Node* first, struct Node* second, __int32 travel);
__int32 getIndex(struct Node* head, char* city);
__int32 findShortestPathHead(struct Node* head);
__int32 findShortestPath(struct Node* head, __int32 pathId);

adv2015p9() {
	FILE* input;
	__int32 buffer = 50;
	char firstCity[50];
	char secondCity[50];
	__int32 travel = 0;
	__int32 pathLength = 0;
	__int32 tempPathLength = 0;
	__int32 numCities = 0;
	__int32 curCity = -1;
	struct Node* head = NULL;

	errno_t input_error;

	input_error = fopen_s(&input, "input2015p9.txt", "r");
	//input_error = fopen_s(&input, "testing_input.txt", "r");

	if (!input_error) {
		while (fscanf_s(input, "%s to %s = %d", firstCity, buffer, secondCity, buffer, &travel) != EOF) {
			numCities++;
			if (head == NULL) {
				buildHead(&head, firstCity, secondCity, buffer, travel);
			} else {
				if (strcmp(firstCity, head->name) == 0) {
					attachToHead(head, firstCity, secondCity, buffer, travel);
				} else { // later city add it together (coud do both here first and second city just reverse)
					createPath(head->next[getIndex(head, firstCity)]->next,
						head->next[getIndex(head, secondCity)]->next, travel);
					createPath(head->next[getIndex(head, secondCity)]->next,
						head->next[getIndex(head, firstCity)]->next, travel);
				}
			}
		}
		while (curCity < head->numConnections) {
			if (curCity == -1) {
				pathLength = findShortestPathHead(head);
				printf("Path length found: %d\n", pathLength);
			}
			else {
				tempPathLength = findShortestPathHead(head->next[curCity]->next);
				printf("Path length found: %d\n", tempPathLength);
				if (tempPathLength > pathLength) {
					pathLength = tempPathLength;
				}
			}
			curCity++;
		}

		printf("The shortest path is: %d", pathLength);
		fclose(input);
	}
}

void buildHead(struct Node** head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	*head = (struct Node*)malloc(sizeof(struct Node));
	if ((*head) != NULL) {
		strcpy_s((*head)->name, buffer, firstCity);
		(*head)->pathId = -1;
		(*head)->numConnections = 0;
		attachToHead(*head, firstCity, secondCity, buffer, travel);
	}
}

void attachToHead(struct Node* head, char* firstCity, char* secondCity, __int32 buffer, __int32 travel) {
	__int32 index = head->numConnections;
	struct Node* newCity = (struct Node*)malloc(sizeof(struct Node));
	if (newCity != NULL) {
		newCity->pathId = -1;
		newCity->numConnections = 0;
		strcpy_s(newCity->name, buffer, secondCity);
		createPath(head, newCity, travel);
		createPath(newCity, head, travel);
	}
}

void createPath(struct Node* first, struct Node* second, __int32 travel) {
	first->next[first->numConnections] = (struct Connector*) malloc(sizeof(struct Connector));
	if (first->next[first->numConnections] != NULL) {
		first->next[first->numConnections]->next = second;
		first->next[first->numConnections]->distance = travel;
		first->numConnections++;
	}
	
}

__int32 getIndex(struct Node* head, char* city) {
	__int32 index = 0;
	__int32 count = head->numConnections;
	while (index < count && strcmp(head->next[index]->next->name, city) != 0) {
		index++;
	}
	return index;
}

__int32 findShortestPathHead(struct Node* head) {
	__int32 index = 0;
	__int32 curCity = 0;
	__int32 pathLength = INT_MIN;
	__int32 tempLength;

	
	while (index < head->numConnections) {
		head->pathId = index;
		printf("Path: %s + %d to ", head->name, head->next[index]->distance);
		tempLength = findShortestPath(head->next[index]->next, index) + head->next[index]->distance;
		if (tempLength > pathLength) {
			pathLength = tempLength;
		}
		index++;
	}
	return pathLength;
}

__int32 findShortestPath(struct Node* head, __int32 pathId) {
	__int32 index = 0;
	__int32 pathLength = INT_MIN;
	__int32 tempLength = 0;
	char foundChild = 0;

	
	while (index < head->numConnections) {
		head->pathId = pathId;
		if (head->next[index]->next->pathId != pathId) {
			printf("%s + %d ", head->name, head->next[index]->distance);
			foundChild = 1;
			tempLength = findShortestPath(head->next[index]->next, pathId) + head->next[index]->distance;
			if (tempLength > pathLength) {
				pathLength = tempLength;
			}
		}
		index++;
	}
	head->pathId = -1;
	if (foundChild == 0) {
		printf("\n");
		return 0;
	} else {
		return pathLength;
	}
}
