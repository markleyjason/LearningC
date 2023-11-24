#pragma once

typedef struct NamedMultiNodeConnector {
	struct NamedMultiNode* next;
	__int32 connecterWeight;
}Connector;

typedef struct NamedMultiNode {
	struct NamedMultiNodeConnector* next[7];
	char name[50];
	__int32 numConnections;
	__int32 pathId;
}NamedMultiNode;

typedef struct circle_return_value {
	char name[50];
	__int32 weight;
}circle_return_value;

void buildHead(struct NamedMultiNode** head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void attachToHeadBothDirections(struct NamedMultiNode* head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void attachToHeadSingleDirection(struct NamedMultiNode* head, char* firstName, char* secondName, __int32 buffer, __int32 weight);
void createPath(struct NamedMultiNode* first, struct NamedMultiNode* second, __int32 weight);
__int32 getIndex(struct NamedMultiNode* head, char* name);
__int32 findLowestWeightPathHead(struct NamedMultiNode* head);
__int32 findLowestWeightPath(struct NamedMultiNode* head, __int32 pathId);
__int32 findHighestWeightPathHead(struct NamedMultiNode* head);
__int32 findHighestWeightPath(struct NamedMultiNode* head, __int32 pathId);

__int32 findLowestWeightPathHeadCircle(struct NamedMultiNode* head);
circle_return_value findLowestWeightPathCircle(struct NamedMultiNode* head, __int32 pathId, char headName[50]);
__int32 findHighestWeightPathHeadCircle(struct NamedMultiNode* head);
circle_return_value findHighestWeightPathCircle(struct NamedMultiNode* head, __int32 pathId, char headName[50]);