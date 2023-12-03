#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int string_right_index(char source_string[], char search_for);

//main() {
//	char line[MAXLINE];
//	char search_char;
//	int place;
//
//	fgets(line, MAXLINE, stdin);
//	search_char = getc(stdin);
//	place = string_right_index(line, search_char);
//
//	if (place >= 0) {
//		printf("Char '%c' was last found in the line at position: %d", search_char, place);
//	}
//	else {
//		printf("Char '%c' was NOT found in the given string", search_char);
//	}
//}

//main() {
//	char testingArray[20] = { "0123456789" };
//	char addition[20] = { "abcdefg" };
//	rsize_t sizing = 19;
//	strncpy_s(&(testingArray[5]), sizing, addition + 1, 4);
//	printf("testingArray: %s\nsize: %d\n", testingArray, strlen(testingArray));
//}

int string_right_index(char source_string[], char search_for) {
	int index = -1;
	int i = 0;
	printf("Inputed string is: %s\n", source_string);


	while (source_string[i] != '\0') {
		printf("%d\n", i);
		if (source_string[i] == search_for) {
			index = i;
		}
		i++;
	}

	return index;
}
