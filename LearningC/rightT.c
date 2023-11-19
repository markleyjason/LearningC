#include <stdio.h>
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
