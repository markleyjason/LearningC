#pragma once
#define NAME_LENGTH 50

typedef struct NamedMultiNodeConnector {
	struct NamedMultiNode* next;
	__int32 connecterWeight;
}NamedMultiNodeConnector;

typedef struct NamedMultiNode {
	NamedMultiNodeConnector* next[8];
	char name[NAME_LENGTH];
	__int32 numConnections;
	__int32 pathId;
}NamedMultiNode;

typedef struct circle_return_value {
	char name[NAME_LENGTH];
	__int32 weight;
}circle_return_value;

void buildHead(NamedMultiNode** head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void attachToHeadBothDirections(NamedMultiNode* head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void attachToHeadSingleDirection(NamedMultiNode* head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void createPath(NamedMultiNode* first, NamedMultiNode* second, __int32 weight);
__int32 getIndex(const NamedMultiNode* head, const char* name);
__int32 findLowestWeightPathHead(NamedMultiNode* head);
__int32 findLowestWeightPath(NamedMultiNode* head, __int32 pathId);
__int32 findHighestWeightPathHead(NamedMultiNode* head);
__int32 findHighestWeightPath(NamedMultiNode* head, __int32 pathId);

__int32 findLowestWeightPathHeadCircle(NamedMultiNode* head);
circle_return_value findLowestWeightPathCircle(NamedMultiNode* head, __int32 pathId, char callerName[NAME_LENGTH], char headName[NAME_LENGTH]);
__int32 findHighestWeightPathHeadCircle(NamedMultiNode* head);
circle_return_value findHighestWeightPathCircle(NamedMultiNode* head, const __int32 pathId, const char callerName[NAME_LENGTH], const char headName[NAME_LENGTH]);