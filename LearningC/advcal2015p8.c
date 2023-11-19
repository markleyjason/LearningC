#include <stdio.h>
#include "helper.h"

enum escapedState {
	NOT,
	ESCAPED,
	HEX
};

adv2015p8() {
	FILE* input;
	errno_t file_error;
	char workingChar;
	char hexPart = 0;
	unsigned __int32 newChars = 0;
	enum escapedState state = NOT;

	file_error = fopen_s(&input, "input2015p8.txt", "r");
	//file_error = fopen_s(&input, "testing_input.txt", "r");

	if (!file_error) {
		workingChar = fgetc(input);
		while (workingChar != EOF) {
			if (workingChar != '\n') {
				switch (state) {
				case ESCAPED:
					if (workingChar == 'x') {
						state = HEX;
					} else {
						state = NOT;
						newChars++;
					}
					break;
				case HEX:
					if (hexPart < 1) {
						hexPart = 1;
					} else {
						hexPart = 0;
						state = NOT;
					}
					break;
				case NOT:
					if (workingChar == '\\') {
						newChars++;
						state = ESCAPED;
					} else if (workingChar == '\"') {
						newChars += 2;
					}
					break;
				}
			}
			workingChar = fgetc(input);
		}
		printf("New characters: %d\n", newChars);

		fclose(input);
	}
}