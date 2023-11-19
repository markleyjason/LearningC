#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char containsVowels(char* line);
char hasDoubleNoBad(char* line, __int32 len);
char part2(char* line, __int32 len);

adv2015p5() {
	__int32 nice_words = 0;
	__int32 tot = 0;
	char rules_passed = 0;
	char rules_needed = 2;
	char line[17];
	FILE* fptr;

	char error = fopen_s(&fptr, "input2015p5.txt", "r");
	//char error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, 17, fptr) != NULL) {
			tot++;
			printf("Line: %s\n", line);
			rules_passed = 0;
			//rules_passed += containsVowels(line, strlen(line));
			//rules_passed += hasDoubleNoBad(line, strlen(line));
			rules_passed = part2(line, strlen(line));
			if (rules_passed == rules_needed) {
				nice_words++;
			}
			printf("Nice words so far: %d\n", nice_words);
		}
		printf("Number of nice words: %d\n", nice_words);
		printf("Total words: %d\n", tot);
		fclose(fptr);
	}

}

char containsVowels(char* line, __int32 len) {
	__int32 count = 0;
	__int32 position = 0;
	char vowel = 0;
	char increased = 0;
	char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };

	while (count < 3 && position < len) {
		for (vowel = 0; vowel < 5 && !increased; vowel++) {
			if (line[position] == vowels[vowel]) {
				count++;
				increased = 1;
			}
		}
		increased = 0;
		position++;
	}
	if (count == 3) {
		return 1;
	} else {
		return 0;
	}
}

char part2(char* line, __int32 len) {
	__int32 position = 2;
	char previous = line[0];
	char hasDouble = 0;
	char hasPair = 0;
	char noBad = 1;
	__int32 bad_word_pos = 0;
	char pairs[17][2];
	__int32 pairs_size = 1;
	__int32 i;

	pairs[0][0] = line[0];
	pairs[0][1] = line[1];

	while (position < len) {
		if (previous == line[position]) {
			hasDouble = 1;
		}

		for (i = 0; i < pairs_size - 1 && !hasPair; i++) {
			if (pairs[i][0] == line[position - 1] && pairs[i][1] == line[position]) {
				hasPair = 1;
			}
		}
		pairs[pairs_size][0] = line[position - 1];
		pairs[pairs_size][1] = line[position];
		pairs_size++;
		previous = line[position - 1];
		position++;
	}
	return hasDouble + hasPair;
}

char hasDoubleNoBad(char* line, __int32 len) {
	__int32 position = 1;
	char previous = line[0];
	char hasDouble = 0;
	char noBad = 1;
	char bad_words[4][2] = { {'a', 'b'}, {'c', 'd'}, {'p', 'q'}, {'x','y'} };
	__int32 bad_word_pos = 0;

	while (position < len && noBad) {
		if (previous == line[position]) {
			hasDouble = 1;
		}
		
		for (bad_word_pos = 0; bad_word_pos < 4 && noBad; bad_word_pos++) {
			if (previous == bad_words[bad_word_pos][0] && line[position] == bad_words[bad_word_pos][1]) {
				noBad = 0;
			}
		}
		
		previous = line[position];
		position++;
	}
	if (noBad == 1) {
		hasDouble++;
	}
	return hasDouble;
}