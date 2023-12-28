#pragma once
#include <stdint.h>
#define NAME_LENGTH 50

typedef struct NamedMultiNodeConnector {
	struct NamedMultiNode* next;
	int32_t connecterWeight;
}NamedMultiNodeConnector;

typedef struct NamedMultiNode {
	NamedMultiNodeConnector* next[8];
	char name[NAME_LENGTH];
	int32_t numConnections;
	int32_t pathId;
}NamedMultiNode;

typedef struct circle_return_value {
	char name[NAME_LENGTH];
	int32_t weight;
}circle_return_value;

void buildHead(NamedMultiNode** head, char* firstName, char* secondName, int32_t buffer, int32_t weight);
void attachToHeadBothDirections(NamedMultiNode* head, char* firstName, char* secondName, int32_t buffer, int32_t weight);
void attachToHeadSingleDirection(NamedMultiNode* head, char* firstName, char* secondName, int32_t buffer, int32_t weight);
void createPath(NamedMultiNode* first, NamedMultiNode* second, int32_t weight);
int32_t getIndex(const NamedMultiNode* head, const char* name);
int32_t findLowestWeightPathHead(NamedMultiNode* head);
int32_t findLowestWeightPath(NamedMultiNode* head, int32_t pathId);
int32_t findHighestWeightPathHead(NamedMultiNode* head);
int32_t findHighestWeightPath(NamedMultiNode* head, int32_t pathId);

int32_t findLowestWeightPathHeadCircle(NamedMultiNode* head);
circle_return_value findLowestWeightPathCircle(NamedMultiNode* head, int32_t pathId, char callerName[NAME_LENGTH], char headName[NAME_LENGTH]);
int32_t findHighestWeightPathHeadCircle(NamedMultiNode* head);
circle_return_value findHighestWeightPathCircle(NamedMultiNode* head, const int32_t pathId, const char callerName[NAME_LENGTH], const char headName[NAME_LENGTH]);