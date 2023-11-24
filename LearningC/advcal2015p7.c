#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ops{
	AND,
	NOT,
	OR,
	LSHIFT,
	RSHIFT,
	DIRECT
};

struct WireFrame {
	char input1[6];
	char input2[6];
	char name[3];
	enum ops operator;
};

struct Wire {
	char name[3];
	unsigned __int16 output;
	struct Wire* input1;
	struct Wire* input2;
	unsigned __int32 stable_input;
	enum ops operation;
};

struct NamedMultiNode {
	struct WireFrame frame;
	struct NamedMultiNode* next;
};

struct WireFrame breakUpT1(__int32 size, char* line);

__int32 insertNode(struct Wire* head, struct WireFrame frame, struct WireFrame* list_head);

//void set_stable_input(struct Wire* the_wire, struct WireFrame frame);

__int32 replace_head(struct Wire* head, struct WireFrame new_head, char input);

int adv2015p7t1() {
	__int32 numWires = 0;
	__int32 index = 0;
	errno_t error;
	FILE* fptr;
	char line[30];
	__int32 line_buffer = 30;
	struct Wire* head = NULL;
	struct Wire* list_head = NULL;
	struct WireFrame temp_frame;

	error = fopen_s(&fptr, "input2015p7.txt", "r");

	if (!error) {
		while (fgets(line, line_buffer, fptr) != NULL) {
			if (line[0] != '\n') {
				//break it apart and create the wire frame
				temp_frame = breakUpT1((__int32)strlen(line), line);
				numWires++;
			}
		}
		//then loop through the wire frame finding a then build the circuit from there as a directed graph with a as the root


		printf("Number of wires: %d\n", numWires);
	}
	
	return error;
}

struct WireFrame breakUpT1(__int32 size, char* line) {

	struct WireFrame breakdown = { .input1 = { '\0' }, .input2 = { '\0' }, .name = { '\0' }, .operator = DIRECT};
	__int32 char_pos = 0;
	char part = 0;
	char string_pos = 0;

	while (char_pos < size) {
		if (line[char_pos] >= 'A' && line[char_pos] <= 'Z') {
			if (breakdown.operator == DIRECT) {
				switch (line[char_pos]) {
					case 'A':
						breakdown.operator = AND;
						break;
					case 'R':
						breakdown.operator = RSHIFT;
						break;
					case 'L':
						breakdown.operator = LSHIFT;
						break;
					case 'O':
						breakdown.operator = OR;
						break;
					case 'N':
						breakdown.operator = NOT;
						break;
				}
			}
		} else if (line[char_pos] == ' ') {
			if (part == 0) {
				part = 1;
				breakdown.input1[string_pos] = '\0';
				string_pos = 0;
			}
		} else if (line[char_pos] == '-') {
			part = 2;
			breakdown.input2[string_pos] = '\0';
			string_pos = 0;
		} else if (line[char_pos] != '\n') {
			switch (part) {
				case 0:
					breakdown.input1[string_pos] = line[char_pos];
					break;
				case 1:
					breakdown.input2[string_pos] = line[char_pos];
					break;
				case 2:
					breakdown.name[string_pos] = line[char_pos];
					break;
			}
		}
		char_pos++;
	}

	breakdown.name[2] = '\0';
	return breakdown;
}

__int32 insertNode(struct Wire* head, struct WireFrame frame, struct WireFrame* list_head) {
	__int32 success = 0;
	struct Wire* tempNode = NULL;
	struct Wire* working_node;
	if (head == NULL) {
		success = replace_head(head, frame, 0);
	} else {
		//if head is an input to wireframe node set it as new head and attach it, if yes set success = 1
		if (strcmp(head->name, frame.input1)) {
			success = replace_head(head, frame, 1);
		} else if (strcmp(head->name, frame.input2)) {
			success = replace_head(head, frame, 2);
		}
		
		//if head is not then depth first search to see if any of the other nodes are an input to it or if it is an input to any of the other nodes, best to check both at the same time, if yes set success = 1
		if (success == 0) {
			working_node = head;
			while (success == 0 && working_node->input1 != NULL) {
				if (strcmp(working_node->name, frame.input1)) {
					success = replace_head(working_node, frame, 1);
				} else if (strcmp(working_node->name, frame.input2)) {
					success = replace_head(working_node, frame, 2);
				}
				working_node = working_node->input1;
			}
		}
	}
	//check if there is a stable input for the wire
	if (success == 1) {
		//set_stable_input(tempNode, frame);
	}
	//if a success try to see if any of the list wireframes are an input to the new node, if yes add them to the graph, once all are checked need to then check if any in the list are an input to any added to the list.
	//this is will continue till no new nodes are added
	//do this recusively? max 400 nodes right now so it may be possible.
	return success;
}

//void set_stable_input(struct Wire* the_wire, struct WireFrame frame) {
//	if (isDigit(frame.input2[0])) {
//		the_wire->stable_input = ctoai(frame.input2);
//	} else if (isDigit(frame.input1[0])) {
//		the_wire->stable_input = ctoa(frame.input2);
//	}
//}

__int32 replace_head(struct Wire* head, struct WireFrame new_head, char input) {
	struct Wire* tempNode = malloc(sizeof(struct Wire));
	__int32 success = 0;
	if(tempNode != NULL){
		if (input = 0) {
			tempNode->input1 = NULL;
			strcpy_s(tempNode->name, 3, new_head.name);
			tempNode->input2 = NULL;
			head = tempNode;
		} else if (input == 1) {
			tempNode->input2 = NULL;
			strcpy_s(tempNode->name, 3, new_head.name);
			tempNode->input1 = head;
			tempNode->operation = new_head.operator;
			head = tempNode;
			success = 1;
		} else {
			tempNode->input1 = NULL;
			strcpy_s(tempNode->name, 3, new_head.name);
			tempNode->input2 = head;
			tempNode->operation = new_head.operator;
			head = tempNode;
			success = 1;
		}
	}
	return success;
}