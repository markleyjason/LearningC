#include <stdlib.h>
#include <string.h>
#include <stdio.h>

__int32 checkForGoodPassword(char password[9]);
__int32 containsTripleIncreasing(char password[9]);
__int32 doesntIncludeBannedWords(char password[9]);
__int32 containsDouble(char password[9]);
void increment(char* password);

adv2015p11() {
	//char password[9] = "vzbxkghb";
	char password[9] = "vzbxxyzz";
	increment(password);
	while (checkForGoodPassword(password) != 1) {
		increment(password);
	}
	printf("The new password is: %s\n", password);
	return 0;
}

__int32 checkForGoodPassword(char password[9]) {
	__int32 returnVal = 0;
	if (containsTripleIncreasing(password) == 1) {
		if (doesntIncludeBannedWords(password) == 1) {
			if (containsDouble(password) == 1) {
				returnVal = 1;
			}
		}
	}
	return returnVal;
}

__int32 containsTripleIncreasing(char password[9]) {
	__int32 rowCount = 0;
	__int32 index = 1;
	
	while (rowCount != 2 && index < 8) {
		if (password[index - 1] + 1 == password[index]) {
			rowCount++;
		} else {
			rowCount = 0;
		}
		index++;
	}
	if (rowCount == 2) {
		return 1;
	}
	return 0;
}

__int32 doesntIncludeBannedWords(char password[9]) {
	__int32 hasBad = 1;
	__int32 index = 0;
	__int32 counter = 0;
	char badChars[3] = { 'i', '0', 'l' };

	while (hasBad == 1 && index < 8) {
		counter = 0;
		while (hasBad == 1 && counter < 3) {
			if (password[index] == badChars[counter]) {
				hasBad = 0;
			}
			counter++;
		}
		index++;
	}
	return hasBad;
}

__int32 containsDouble(char password[9]) {
	__int32 index = 1;
	__int32 hasDouble = 0;
	while (hasDouble < 2 && index < 8) {
		if (password[index - 1] == password[index]) {
			hasDouble++;
			index++;
		}
		index++;
	}
	if (hasDouble == 2) {
		hasDouble = 1;
	} else {
		hasDouble = 0;
	}
	return hasDouble;
}

void increment(char* password) {
	__int32 index = 7;

	password[index]++;
	while (password[index] > 'z' && index >= 0) {
		password[index] = 'a';
		index--;
		password[index]++;
	}
}
