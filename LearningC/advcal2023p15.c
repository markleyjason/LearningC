#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hashtable.h"
#include "helper.h"

#define LETTER_SIZE 10

typedef struct adv2023p15{
	char letters[LETTER_SIZE];
	uint16_t lens;
} adv2023p15lens;

static hashtable boxes = { .dataSize = sizeof(adv2023p15lens), .lists = NULL, .numBuckets = 1 };

static int32_t hashFunction(void* item, void* context);
static int32_t compareFunctionLetters(void* item1, void* item2, void* context);

static int adb2023p15() {
//int main() {
	FILE* fptr;
	errno_t error;
	uint32_t hash = 0;
	uint64_t sum = 0;
	char temp = '\0';
	unsigned char* pointer = 0;
	uint16_t index = 0;
	uint16_t lIndex = 0;
	adv2023p15lens tempLens = { .lens = 0, .letters = { '\0' } };
	void* response = NULL;
	hashtableReturnCodes responseCode = SUCCESS;

	setUpHashTable(&boxes, 256, sizeof(adv2023p15lens));

	error = fopen_s(&fptr, "input2023p15.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	
	if (!error) {

		temp = fgetc(fptr);

		while (temp != '\n' && temp != EOF) {
			switch(temp) {
			case ',':
				sum += hash;
				hash = 0;
				break;
			case '=':
				hash += temp;
				hash *= 17;
				hash = hash % 256;
				temp = fgetc(fptr);
				hash += temp;
				hash *= 17;
				hash = hash % 256;
				tempLens.lens = ctoai(temp);
				tempLens.letters[index] = '\0';
				response = containsItem(&boxes, &tempLens, NULL, &hashFunction, NULL, &compareFunctionLetters);
				if (response != NULL) {
					error = memcpy_s(response, sizeof(adv2023p15lens), &tempLens, sizeof(adv2023p15lens));
					if (error) {
						printf("Replace error\n");
						return -2;
					}
				} else {
					responseCode = insertHashTable(&boxes, &tempLens, NULL, &hashFunction);
					if (responseCode != SUCCESS) {
						printf("Insert Error\n");
						return responseCode;
					}
				}
				index = 0;
				break;
			case '-':
				hash += temp;
				hash *= 17;
				hash = hash % 256;
				tempLens.letters[index] = '\0';
				responseCode = removeItem(&boxes, &tempLens, NULL, &hashFunction, NULL, &compareFunctionLetters);
				switch (responseCode) {
				case NO_ITEM:
				case SUCCESS:
					break;
				default:
					printf("Remove error\n");
					return responseCode;
					break;
				}
				index = 0;
				break;
			default:
				tempLens.letters[index] = temp;
				index++;
				hash += temp;
				hash *= 17;
				hash = hash % 256;
				break;
			}
			temp = fgetc(fptr);
		}
		fclose(fptr);

		sum += hash;
		printf("The hash: %llu\n", sum);
		sum = 0;
		for (index = 0; index < boxes.numBuckets; index++) {
			lIndex = 0;
			while (lIndex < boxes.lists[index].logicalSize) {
				tempLens = *(((adv2023p15lens*)boxes.lists[index].data) + lIndex);
				sum += ((uint64_t)tempLens.lens) * ((uint64_t)lIndex + 1) * ((uint64_t)index + 1);
				lIndex++;
			}
		}
		printf("focusing power: %llu\n", sum);
		
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}

static int32_t hashFunction(void* item, void* context) {
	adv2023p15lens theItem = *(adv2023p15lens*)item;
	int32_t hash = 0;
	uint16_t index = 0;

	while (index < LETTER_SIZE && theItem.letters[index] != '\0') {
		hash += theItem.letters[index];
		hash *= 17;
		hash = hash % 256;
		index++;
	}
	return hash;
}

static int32_t compareFunctionLetters(void* item1, void* item2, void* context) {
	adv2023p15lens theItem = *(adv2023p15lens*)item1;
	adv2023p15lens theItem2 = *(adv2023p15lens*)item2;
	return strcmp(theItem.letters, theItem2.letters);
}