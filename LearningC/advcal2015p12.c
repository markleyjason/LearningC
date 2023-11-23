#include "helper.h"
#include <stdio.h>

main() {
	__int32 sum = 0;
	unsigned __int32 index = 0;
	char buildingNum = 0;
	char currChar;
	char numbers[5];
	__int8 sign = 1;
	errno_t error;
	FILE* fptr;

	error = fopen_s(&fptr, "input2015p12.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		currChar = getc(fptr);
		while (currChar != EOF) {
			if (currChar == '-') {
				sign *= -1;
			} else if (isDigit(currChar)) {
				if (buildingNum == 0) {
					buildingNum = 1;
					index = 0;
					numbers[index] = currChar;
					index++;
				} else {
					numbers[index] = currChar;
					index++;
				}
			} else {
				if (buildingNum == 1) {
					numbers[index] = '\0';
					sum += sign * stoai(numbers);
					buildingNum = 0;
					sign = 1;
					index = 0;
				}
			}
			currChar = getc(fptr);
		}
		printf("Sum is: %d\n", sum);
	}
}