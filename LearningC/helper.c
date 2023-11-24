#include "helper.h"
#include <stdlib.h>

char isDigit(char input) {
	__int32 ret = 0;
	if (input - '0' >= 0 && input - '0' <= 9) {
		ret = 1;
	}
	return ret;
}

__int32 stoai(char* input) {
	__int32 factor = 10;
	__int32 sign = 1;
	__int32 index = 0;
	__int32 num = 0;
	if (input[0] == '-') {
		sign = -1;
		index++;
	}
	while (input[index] != '\0') {
		num = num * factor + ctoai(input[index]);
		index++;
	}
	return num * sign;
}

//Assumes all integers in the array are only a single digit (0-9)
char* uint32arraytostring(unsigned __int32 size, unsigned __int32* start) {
	char* array = malloc(sizeof(__int32) * size + 1);
	unsigned __int32 index = 0;
	if (array != NULL) {
		while (index < size) {
			array[index] = start[index] + '0';
			index++;
		}
		array[index] = '\0';
	}
	
	
	return array;
}

__int32 ctoai(char input) {
	return (__int32)input - '0';
}

__int32 findMin(__int32* array, __int32 length) {
	int i = 0;
	int min = INT_MAX;

	for (i = 0; i < length; i++) {
		if (array[i] < min) {
			min = array[i];
		}
	}
	return min;
}

__int32 findVolume(__int32 length, __int32 width, __int32 height) {
	return length * width * height;
}
__int32 findVolumeA(__int32* input) {
	return findVolume(input[0], input[1], input[2]);
}
