#include "helper.h"
#include <stdio.h>

__int32 calBlock(FILE* fptr);
__int32 calArray(FILE* fptr);

ad2015p12() {
	__int32 sum = 0;
	unsigned __int32 index = 0;
	char buildingNum = 0;
	char currChar;
	char numbers[5] = { '\0' };
	errno_t error;
	FILE* fptr;

	error = fopen_s(&fptr, "input2015p12.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		currChar = getc(fptr);
		while (currChar != EOF) {
			if (currChar == '{') {
				sum += calBlock(fptr);
			}else if(currChar == '['){
				sum += calArray(fptr);
			}
			currChar = getc(fptr);
		}
		printf("Sum is: %d\n", sum);
		fclose(fptr);
	}
}

__int32 calBlock(FILE* fptr) {
	char containsRed = 0;
	char buildingNum = 0;
	char currChar;
	char numbers[5] = { '\0' };
	unsigned __int8 redCount = 0;
	__int32 index = 0;
	__int32 sum = 0;

	currChar = getc(fptr);
	while (currChar != '}') {
		if (redCount == 0 && (currChar == 'r' || currChar == 'R')) {
			redCount = 1;
		} else if (redCount == 1 && (currChar == 'e' || currChar == 'E')) {
			redCount = 2;
		} else if (redCount == 2 && (currChar == 'd' || currChar == 'D')) {
			containsRed = 1;
		} else {
			redCount = 0;
			if (currChar == '{') {
				sum += calBlock(fptr);
			} else if (currChar == '[') {
				sum += calArray(fptr);
			} else if (isDigit(currChar) || currChar == '-') {
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
					sum += stoai(numbers);
					buildingNum = 0;
					index = 0;
				}
			}
		}
		currChar = getc(fptr);
	}


	if (containsRed == 1) {
		sum = 0;
	} else if (buildingNum == 1) {
		numbers[index] = '\0';
		sum += stoai(numbers);
		buildingNum = 0;
		index = 0;
	}
	return sum;
}

__int32 calArray(FILE* fptr) {
	__int32 sum = 0;
	char currChar;
	unsigned __int32 index = 0;
	__int32 buildingNum = 0;
	char numbers[5] = { '\0' };

	currChar = getc(fptr);
	while (currChar != ']') {
		if (currChar == '{') {
			sum += calBlock(fptr);
		}else if (currChar == '[') {
			sum += calArray(fptr);
		} else if (isDigit(currChar) || currChar == '-') {
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
				sum += stoai(numbers);
				buildingNum = 0;
				index = 0;
			}
		}
		currChar = getc(fptr);
	}
	if (buildingNum == 1) {
		numbers[index] = '\0';
		sum += stoai(numbers);
		buildingNum = 0;
		index = 0;
	}
	return sum;
}