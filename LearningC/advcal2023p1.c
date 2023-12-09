#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

int advcal2023p1() {
//int main() {
	FILE* fptr;
	errno_t error;
	__int32 firstNumber = -1;
	_int32 secondNumber = -1;
	unsigned __int32 sum = 0;
	char tempChar;
	char line[100] = { '\0' };
	__int32 buffer = 100;
	unsigned __int32 index = 0;
	__int32 tempNum = -1;

	error = fopen_s(&fptr, "input2023p1.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, buffer, fptr) != NULL) {
			index = 0;
			printf("%s\n", line);
			while (line[index] != '\0' && line[index] != '\n' && line[index] != EOF) {
				tempChar = line[index];
				tempNum = stringIsDigit(line, index);
				if (tempNum > -1) {						
					if (firstNumber == -1) {
						firstNumber = tempNum;
					} else {
						secondNumber = tempNum;
					}
				} else if (isDigit(tempChar)) {
					if (firstNumber == -1) {
						firstNumber = ctoai(tempChar);
					} else {
						secondNumber = ctoai(tempChar);
					}
				}
				index++;
			}
			if (secondNumber != -1) {
				printf("First number: %d Second number: %d\n Combined %d\n", firstNumber, secondNumber, firstNumber * 10 + secondNumber);
				sum += 10 * firstNumber + secondNumber;
			} else {
				printf("First number: %d Second number: %d\n Combined %d\n", firstNumber, firstNumber, firstNumber * 10 + firstNumber);
				sum += 10 * firstNumber + firstNumber;
			}
			firstNumber = -1;
			secondNumber = -1;
		}
		fclose(fptr);

		printf("Sum is: %d\n", sum);
	} else {
		printf("Make the file.");
		return -1;
	}
	return 0;
}