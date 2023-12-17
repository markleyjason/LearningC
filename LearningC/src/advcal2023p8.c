#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#define MAXNODES 718
#define LINEBUFFER 285
#define NODESTRINGSIZE 4

typedef struct MAPPING {
	char key[4];
	char left[4];
	char right[4];
}AdvMapping;

static AdvMapping nodes[MAXNODES];
int compareMappings(void* context, const void* elem1, const void* elem2);

static adv2023p8() {
//main() {
	clock_t start, end;
	double time_elapsed_ms;
	start = clock();
	FILE* fptr;
	errno_t error;
	char directions[LINEBUFFER] = { '\0' };
	int16_t index = 0;
	int16_t dIndex = 0;
	int16_t numNodes = 0;
	int32_t numSteps = 0;
	int16_t dirLen = 0;
	AdvMapping* currentPlace = NULL;
	AdvMapping* currentPlaceP2[10] = { NULL };
	uint32_t p2steps = 0;
	uint64_t firstReachZ[6] = { 0 };
	uint64_t firstNum = 0;
	uint64_t secondNum = 0;
	int16_t p2index = 0;
	int16_t p2count = 0;
	char p2found = 0;
	char p1found = 0;
	char tempChar = '\0';


	error = fopen_s(&fptr, "input2023p8.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		fgets(directions, LINEBUFFER, fptr);
		dirLen = strlen(directions) - 1;
		tempChar = fgetc(fptr);
		while (index < MAXNODES && fscanf_s(fptr, "%3s = (%3s, %3s)", nodes[index].key, NODESTRINGSIZE, nodes[index].left, NODESTRINGSIZE, nodes[index].right, NODESTRINGSIZE) != 0) {
			if (nodes[index].key[0] == '\0') {
				break;
			}
			index++;
		}
		fclose(fptr);
		numNodes = index;
		index = 0;
		qsort_s(nodes, numNodes, sizeof(AdvMapping), &compareMappings, NULL);

		while (p2count < 6 && p2index < numNodes) {
			if (nodes[p2index].key[2] == 'A') {
				currentPlaceP2[p2count] = &nodes[p2index];
				p2count++;
			}
			p2index++;
		}
		p2index = 0;
		dIndex = 0;

		currentPlace = nodes;
		while (p1found == 0 || p2found < p2count) {
			if (dIndex == dirLen) {
				dIndex = 0;
			}
			if (p1found == 0) {
				numSteps++;
				if (directions[dIndex] == 'R') {
					currentPlace = bsearch_s(currentPlace->right, nodes, numNodes, sizeof(AdvMapping), &compareMappings, NULL);
				} else {
					currentPlace = bsearch_s(currentPlace->left, nodes, numNodes, sizeof(AdvMapping), &compareMappings, NULL);
				}
				if (strcmp(currentPlace->key, "ZZZ") == 0) {
					p1found = 1;
				}
			}
			if (p2found < p2count) {
				p2steps++;
				for (p2index = 0; p2index < p2count; p2index++) {
					if (directions[dIndex] == 'R') {
						currentPlaceP2[p2index] = bsearch_s(currentPlaceP2[p2index]->right, nodes, numNodes, sizeof(AdvMapping), &compareMappings, NULL);
					} else {
						currentPlaceP2[p2index] = bsearch_s(currentPlaceP2[p2index]->left, nodes, numNodes, sizeof(AdvMapping), &compareMappings, NULL);
					}
					
					if (currentPlaceP2[p2index]->key[2] == 'Z') {
						if (firstReachZ[p2index] == 0) {
							firstReachZ[p2index] = p2steps;
						}
						p2found++;
					}
				}
			}
			dIndex++;
			index++;
		}
		printf("Number of steps: %d\n", numSteps);

		for (index = 1; index < p2count; index++) {
			firstNum = firstReachZ[0];
			secondNum = firstReachZ[index];
			numSteps = 0;
			while (firstNum != secondNum) {
				if (firstNum % 2 == 0) {
					if (secondNum % 2 == 0) {
						firstNum = firstNum >> 1;
						secondNum = secondNum >> 1;
						numSteps++;
					} else {
						firstNum = firstNum >> 1;
					}
				} else if (secondNum % 2 == 0) {
					secondNum = secondNum >> 1;
				} else {
					if (firstNum < secondNum) {
						firstNum = secondNum + firstNum;
						secondNum = firstNum - secondNum;
						firstNum = firstNum - secondNum;
					}
					firstNum = (firstNum - secondNum) / 2;
				}
			}
			while (numSteps > 0) {
				numSteps--;
				firstNum = firstNum << 1;
			}
			if (firstNum != 0) {
				firstReachZ[0] = (firstReachZ[0] * firstReachZ[index]) / firstNum;
			} else {
				firstReachZ[0] = (firstReachZ[0] * firstReachZ[index]) / secondNum;
			}
		}
		printf("Part 2 steps: %" PRIu64 "\n", firstReachZ[0]);
		
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	end = clock();
	time_elapsed_ms = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %f milliseconds\n", time_elapsed_ms);
	return 0;
}

int compareMappings(void* context, const void* elem1, const void* elem2) {
	return strcmp(((AdvMapping*)elem1)->key, ((AdvMapping*)elem2)->key);
}