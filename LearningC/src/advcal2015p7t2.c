#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

enum ops {
	AND = 0,
	NOT = 1,
	OR = 2,
	LSHIFT = 3,
	RSHIFT = 4,
	DIRECT = 5
};

struct WireFrame {
	char input1[6];
	char input2[6];
	char name[3];
	unsigned __int16 output;
	__int8 calculated;
	enum ops operator;
};

void addToList(__int32 size, char* line, __int32 position, struct WireFrame list[400]);

void calculate_wire(char* name, __int32 size, struct WireFrame list[400]);

__int32 findWireFrame(char* name, __int32 size, struct WireFrame list[400]);

void adv2015p7t2() {
	__int32 numWires = 0;
	__int32 index = 0;
	unsigned __int16 firstOutput;
	errno_t error;
	errno_t open_error;
	FILE* fptr;
	FILE* output;
	char line[30];
	__int32 line_buffer = 30;
	struct WireFrame wireFrameList[400];

	error = fopen_s(&fptr, "input2015p7.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");
	open_error = fopen_s(&output, "output.txt", "w");
	printf("File creation error: %d\n", open_error);
	if (!error) {
		while (fgets(line, line_buffer, fptr) != NULL) {
			if (line[0] != '\n') {
				//break it apart and create the wire frame
				addToList((__int32)strlen(line), line, numWires, wireFrameList);
				numWires++;
			}
		}
		//find each one and calculate down the list till we have calculated all giving value on A
		calculate_wire("a", numWires, wireFrameList);
		/*calculate_wire("x", numWires, wireFrameList);
		calculate_wire("y", numWires, wireFrameList);
		calculate_wire("d", numWires, wireFrameList);
		calculate_wire("e", numWires, wireFrameList);
		calculate_wire("f", numWires, wireFrameList);
		calculate_wire("g", numWires, wireFrameList);
		calculate_wire("h", numWires, wireFrameList);
		calculate_wire("i", numWires, wireFrameList);*/
		printf("Number of wires: %d\n", numWires);
		firstOutput = wireFrameList[findWireFrame("a", numWires, wireFrameList)].output;
		printf("Output of a first time is: %d\n", firstOutput);
		for (index = 0; index < numWires; index++) {
			wireFrameList[index].calculated = 0;
		}
		index = findWireFrame("b", numWires, wireFrameList);
		wireFrameList[index].calculated = 1;
		wireFrameList[index].output = firstOutput;
		calculate_wire("a", numWires, wireFrameList);
		firstOutput = wireFrameList[findWireFrame("a", numWires, wireFrameList)].output;
		printf("Output of a second time is: %d\n", firstOutput);
	}
}

void addToList(__int32 size, char* line, __int32 position, struct WireFrame list[400]) {
	list[position].input1[0] = '\0' ;
	list[position].input2[0] = '\0';
	list[position].name[0] = '\0';
	list[position].output = 0;
	list[position].calculated = 0;
	list[position].operator = DIRECT;
	__int32 char_pos = 0;
	char part = 0;
	char string_pos = 0;

	while (char_pos < size) {
		if (line[char_pos] >= 'A' && line[char_pos] <= 'Z') {
			if (list[position].operator == DIRECT) {
				switch (line[char_pos]) {
				case 'A':
					list[position].operator = AND;
					break;
				case 'R':
					list[position].operator = RSHIFT;
					break;
				case 'L':
					list[position].operator = LSHIFT;
					break;
				case 'O':
					list[position].operator = OR;
					break;
				case 'N':
					list[position].operator = NOT;
					break;
				}
			}
		} else if (line[char_pos] == ' ') {
			if (part == 0) {
				part = 1;
				list[position].input1[string_pos] = '\0';
				string_pos = 0;
			}
		} else if (line[char_pos] == '-' || line[char_pos] == '>') {
			if (part != 2) {
				part = 2;
				list[position].input2[string_pos] = '\0';
				string_pos = 0;
			}
		} else if (line[char_pos] != '\n') {
			switch (part) {
			case 0:
				list[position].input1[string_pos] = line[char_pos];
				break;
			case 1:
				list[position].input2[string_pos] = line[char_pos];
				break;
			case 2:
				list[position].name[string_pos] = line[char_pos];
				break;
			}
			string_pos++;
		}
		char_pos++;
	}

	list[position].name[string_pos] = '\0';
}

void calculate_wire(char* name, __int32 size, struct WireFrame list[400]) {
	unsigned __int16 firstInput = 0;
	unsigned __int16 secondInput = 0;
	__int32 index = findWireFrame(name, size, list);

	if (list[index].calculated == 0) {
		switch (list[index].operator) {
			case DIRECT:
				if (isDigit(list[index].input1[0])) {
					list[index].output = stoai(list[index].input1);
				} else {
					calculate_wire(list[index].input1, size, list);
					list[index].output = list[findWireFrame(list[index].input1, size, list)].output;
				}
				list[index].calculated = 1;
				break;
			case NOT:
				if (isDigit(list[index].input2[0])) {
					list[index].output = ~stoai(list[index].input2);
				} else {
					calculate_wire(list[index].input2, size, list);
					list[index].output = ~list[findWireFrame(list[index].input2, size, list)].output;
				}
				list[index].calculated = 1;
				break;
			case AND:
				if (isDigit(list[index].input1[0])) {
					firstInput = stoai(list[index].input1);
				}
				else {
					calculate_wire(list[index].input1, size, list);
					firstInput = list[findWireFrame(list[index].input1, size, list)].output;
				}
				if (isDigit(list[index].input2[0])) {
					secondInput = stoai(list[index].input2);
				}
				else {
					calculate_wire(list[index].input2, size, list);
					secondInput = list[findWireFrame(list[index].input2, size, list)].output;
				}
				calculate_wire(list[index].input2, size, list);
				list[index].output = firstInput & secondInput;
				list[index].calculated = 1;
				break;
			case OR:
				if (isDigit(list[index].input1[0])) {
					firstInput = stoai(list[index].input1);
				}
				else {
					calculate_wire(list[index].input1, size, list);
					firstInput = list[findWireFrame(list[index].input1, size, list)].output;
				}
				if (isDigit(list[index].input2[0])) {
					secondInput = stoai(list[index].input2);
				}
				else {
					calculate_wire(list[index].input2, size, list);
					secondInput = list[findWireFrame(list[index].input2, size, list)].output;
				}
				list[index].output = firstInput | secondInput;
				list[index].calculated = 1;
				break;
			case LSHIFT:
				calculate_wire(list[index].input1, size, list);
				if (isDigit(list[index].input2[0])) {
					list[index].output = list[findWireFrame(list[index].input1, size, list)].output << stoai(list[index].input2);
				} else {
					calculate_wire(list[index].input2, size, list);
					list[index].output = list[findWireFrame(list[index].input1, size, list)].output << list[findWireFrame(list[index].input2, size, list)].output;
				}
				list[index].calculated = 1;
				break;
			case RSHIFT:
				calculate_wire(list[index].input1, size, list);
				if (isDigit(list[index].input2[0])) {
					list[index].output = list[findWireFrame(list[index].input1, size, list)].output >> stoai(list[index].input2);
				} else {
					calculate_wire(list[index].input2, size, list);
					list[index].output = list[findWireFrame(list[index].input1, size, list)].output >> list[findWireFrame(list[index].input2, size, list)].output;
				}
				list[index].calculated = 1;
				break;
		}
	}
}

__int32 findWireFrame(char* name, __int32 size, struct WireFrame list[400]) {
	__int32 index = 0;

	while (index < size && strcmp(name, list[index].name) != 0) {
		index++;
	}
	return index;
}