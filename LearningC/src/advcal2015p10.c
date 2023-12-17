#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "collections.h"

adv2015p10() {
	unsigned __int32 counter = 0;
	unsigned __int32 index = 0;
	const unsigned __int32 steps = 50;
	unsigned __int32 numCount = 0;
	__int32 num = 0;
	char workingArray = 0;
	char* printingChar;
	IntegerArray* numbers1;
	IntegerArray* numbers2;
	numbers1 = setupIntegerArray(1000);
	numbers2 = setupIntegerArray(1000);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 3);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 2);
	appendIntegerArray(numbers1, 2);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 1);
	appendIntegerArray(numbers1, 3);
	printingChar = uint32arraytostring((unsigned __int32)numbers1->logicalSize, numbers1->data);
	printf("Step %d: %s\n", counter, printingChar);
	free(printingChar);

	while (counter < steps) {
		numCount = 0;
		num = 0;
		if (workingArray == 0) {
			numbers2->logicalSize = 0;
			num = numbers1->data[index];
			while (index < numbers1->logicalSize) {
				if (num != numbers1->data[index]) {
					appendIntegerArray(numbers2, numCount);
					appendIntegerArray(numbers2, num);
					num = numbers1->data[index];
					numCount = 1;
				} else {
					numCount++;
				}
				index++;
			}
			appendIntegerArray(numbers2, numCount);
			appendIntegerArray(numbers2, num);
			workingArray = 1;
			printingChar = uint32arraytostring((unsigned __int32)numbers2->logicalSize, numbers2->data);
			printf("Step %d: %s\n", counter + 1, printingChar);
			free(printingChar);
		} else {
			num = numbers2->data[index];
			numbers1->logicalSize = 0;
			while (index < numbers2->logicalSize) {
				if (num != numbers2->data[index]) {
					appendIntegerArray(numbers1, numCount);
					appendIntegerArray(numbers1, num);
					num = numbers2->data[index];
					numCount = 1;
				}
				else {
					numCount++;
				}
				index++;
			}
			appendIntegerArray(numbers1, numCount);
			appendIntegerArray(numbers1, num);
			printingChar = uint32arraytostring((unsigned __int32)numbers1->logicalSize, numbers1->data);
			printf("Step %d: %s\n", counter + 1, printingChar);
			free(printingChar);
			workingArray = 0;
		}
		index = 0;
		counter++;
	}

	if (workingArray == 0) {
		printingChar = uint32arraytostring((unsigned __int32)numbers1->logicalSize, numbers1->data);
		printf("Step %d: %s\n", counter + 1, printingChar);
		printf("Ending length is: %d\n", (__int32)numbers1->logicalSize);
		free(printingChar);
	} else {
		printingChar = uint32arraytostring((unsigned __int32)numbers2->logicalSize, numbers2->data);
		printf("Step %d: %s\n", counter, printingChar);
		printf("Ending length is: %d\n", (__int32)numbers2->logicalSize);
		free(printingChar);
	}
	return 0;
}