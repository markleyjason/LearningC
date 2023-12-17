#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helper.h"
#include <time.h>

#define BUFFER 100

static int advcal2023p1() {
//int main() {
	clock_t start, end;
	start = clock();
	double dif;
	FILE* fptr;
	errno_t error;
	int16_t firstNumber = -1;
	int16_t secondNumber = -1;
	uint16_t sum = 0;
	char tempChar;
	char line[100] = { '\0' };
	uint16_t index = 0;
	int16_t tempNum = -1;

	error = fopen_s(&fptr, "input2023p1.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, BUFFER, fptr) != NULL) {
			index = 0;
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
				sum += 10 * firstNumber + secondNumber;
			} else {
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
	end = clock();

	dif = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
	printf("Time spent: %f", dif);
	return 0;
}