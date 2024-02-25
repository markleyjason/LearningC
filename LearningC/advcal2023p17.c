#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helper.h"
#include "binary_heap.h"
#include <time.h>

#define GRID_SIZE 141

typedef enum direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
}AdvDirection;

typedef struct AdvPathWeight {
	uint8_t steppingWeight;
	uint32_t weightToGetHere[20];
	char visited[20];
}AdvPathWeight;

typedef struct AdvSelectionPart {
	uint16_t index;
	uint16_t sindex;
	uint32_t weight;
	uint8_t dirCount;
	AdvDirection direction;
}AdvSelectionPart;



static AdvPathWeight grid[GRID_SIZE][GRID_SIZE];
static uint16_t height = 0;
static uint16_t width = 0;

static BinaryHeap heap = { .data = NULL, .dataSize = 0, .logicalSize = 0, .memSize = 0 };

static void startPath(int16_t index, int16_t sindex);
static void calcPaths(int16_t index, int16_t sindex, uint8_t dirCount);
static void startPath2(int16_t index, int16_t sindex);
static void calcPaths2(int16_t index, int16_t sindex, uint8_t dirCount, AdvDirection direction);
static int compareFunction(const void* item1, const void* item2, const void* context);

static int adv2023p17() {
//int main() {
	clock_t start, end;
	start = clock();
	double dif;
	FILE* fptr;
	errno_t error;
	uint32_t heatLost = 0;
	int16_t index = 0;
	int16_t sindex = 0;
	char temp = '\0';


	setupHeap(&heap, sizeof(AdvSelectionPart));
	error = fopen_s(&fptr, "input2023p17.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");

	if (!error) {
		temp = fgetc(fptr);
		while (temp != EOF) {
			if (temp != '\n') {
				grid[index][sindex].steppingWeight = ctoai(temp);
				grid[index][sindex].weightToGetHere[0] = UINT32_MAX;
				grid[index][sindex].weightToGetHere[1] = UINT32_MAX;
				grid[index][sindex].weightToGetHere[2] = UINT32_MAX;
				grid[index][sindex].weightToGetHere[3] = UINT32_MAX;
				grid[index][sindex].weightToGetHere[4] = UINT32_MAX;
				grid[index][sindex].weightToGetHere[5] = UINT32_MAX;
				grid[index][sindex].visited[0] = 0;
				grid[index][sindex].visited[1] = 0;
				grid[index][sindex].visited[2] = 0;
				grid[index][sindex].visited[3] = 0;
				grid[index][sindex].visited[4] = 0;
				grid[index][sindex].visited[5] = 0;
				sindex++;
			} else {
				index++;
				sindex = 0;
			}
			temp = fgetc(fptr);
		}
		fclose(fptr);
		height = index + 1;
		width = sindex;
		index = 0;
		sindex = 0;
		startPath(0, 0);
		if (height > 0 && width > 0) {
			heatLost = grid[height - 1][width - 1].weightToGetHere[0];
			for (index = 1; index < 6; index++) {
				if (heatLost > grid[height - 1][width - 1].weightToGetHere[index]) {
					heatLost = grid[height - 1][width - 1].weightToGetHere[index];
				}
			}
		}
		printf("Heat lost: %lu\n", heatLost);
		end = clock();
		dif = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
		printf("Time spent: %f\n", dif);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	//part 2 :(
	deleteHeap(&heap);
	setupHeap(&heap, sizeof(AdvSelectionPart));
	error = fopen_s(&fptr, "input2023p17.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	index = 0;
	sindex = 0;
	if (!error) {
		temp = fgetc(fptr);
		while (temp != EOF) {
			if (temp != '\n') {
				grid[index][sindex].steppingWeight = ctoai(temp);
				for (heatLost = 0; heatLost < 20; heatLost++) {
					grid[index][sindex].weightToGetHere[heatLost] = UINT32_MAX;
					grid[index][sindex].visited[heatLost] = 0;
				}
				sindex++;
			} else {
				index++;
				sindex = 0;
			}
			temp = fgetc(fptr);
		}
		fclose(fptr);
		height = index + 1;
		width = sindex;
		index = 0;
		sindex = 0;
		startPath2(0, 0);
		if (height > 0 && width > 0) {
			heatLost = grid[height - 1][width - 1].weightToGetHere[0];
			for (index = 1; index < 20; index++) {
				if (heatLost > grid[height - 1][width - 1].weightToGetHere[index]) {
					heatLost = grid[height - 1][width - 1].weightToGetHere[index];
				}
			}
		}
		printf("Heat lost: %lu\n", heatLost);
		end = clock();
		dif = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
		printf("Time spent: %f\n", dif);
	} else {
		printf("Failed to open file second time\n");
		return -1;
	}
	return 0;
}

static void startPath(int16_t index, int16_t sindex) {
	uint32_t currentWeight = grid[index][sindex].steppingWeight;
	uint32_t pathWeight = 0;
	uint8_t dirCount = 0;
	AdvSelectionPart tempPart = { .index = 0, .sindex = 0, .weight = 0 };
	errno_t error;
	grid[index][sindex].visited[0] = 1;
	grid[index][sindex].weightToGetHere[0] = 0;
	grid[index][sindex].weightToGetHere[1] = 0;
	grid[index][sindex].weightToGetHere[2] = 0;
	grid[index][sindex].visited[1] = 1;
	grid[index][sindex].weightToGetHere[3] = 0;
	grid[index][sindex].weightToGetHere[4] = 0;
	grid[index][sindex].weightToGetHere[5] = 0;

	//this will be the start, easier to get the direction to be correct with second function
	grid[index + 1][sindex].weightToGetHere[0] = grid[index + 1][sindex].steppingWeight;
	tempPart.index = index + 1;
	tempPart.sindex = sindex;
	tempPart.weight = grid[index + 1][sindex].weightToGetHere[0];
	tempPart.dirCount = 0;
	error = insert(&heap, &tempPart, NULL, compareFunction);
	if (error) {
		printf("Heap error inserting \n");
		exit(-2);
	}
	grid[index][sindex + 1].weightToGetHere[3] = grid[index][sindex + 1].steppingWeight;
	tempPart.index = index;
	tempPart.sindex = sindex + 1;
	tempPart.weight = grid[index][sindex + 1].weightToGetHere[3];
	tempPart.dirCount = 3;
	error = insert(&heap, &tempPart, NULL, compareFunction);
	if (error) {
		printf("Heap error inserting\n");
		exit(-2);
	}
	while (grid[height - 1][width - 1].visited[0] == 0 && grid[height - 1][width - 1].visited[1] == 0 && grid[height - 1][width - 1].visited[2] == 0 && grid[height - 1][width - 1].visited[3] == 0 && grid[height - 1][width - 1].visited[4] == 0 && grid[height - 1][width - 1].visited[5] == 0) {
		error = removeSmallest(&heap, NULL, compareFunction, &tempPart);
		if (error) {
			printf("Heap error removing\n");
			exit(-3);
		}
		if (grid[tempPart.index][tempPart.sindex].visited[tempPart.dirCount] == 0) {
			calcPaths(tempPart.index, tempPart.sindex, tempPart.dirCount);
		}
	}
}

static void calcPaths(int16_t index, int16_t sindex, uint8_t dirCount) {
	uint32_t tempVal = 0;
	uint8_t updateIndex = 0;
	AdvSelectionPart tempPart = { .index = 0, .sindex = 0, .weight = 0 };
	BinaryHeapReturnCodes error;

	grid[index][sindex].visited[dirCount] = 1;
	if (index + 1 == height && sindex + 1 == width) {
		return;
	}
	if (dirCount < 2) {
		updateIndex = dirCount + 1;
	} else {
		updateIndex = 0;
	}
	if (index - 1 > -1 && grid[index - 1][sindex].visited[updateIndex] == 0 && (dirCount > 2 || dirCount < 2)) {
		tempVal = grid[index][sindex].weightToGetHere[dirCount] + grid[index - 1][sindex].steppingWeight;
		if (tempVal < grid[index - 1][sindex].weightToGetHere[updateIndex]) {
			grid[index - 1][sindex].weightToGetHere[updateIndex] = tempVal;
			tempPart.index = index - 1;
			tempPart.sindex = sindex;
			tempPart.weight = tempVal;
			tempPart.dirCount = updateIndex;
			error = insert(&heap, &tempPart, NULL, compareFunction);
			if (error) {
				printf("Heap error inserting\n");
				exit(-2);
			}
		}
	}

	if (index + 1 < height && grid[index + 1][sindex].visited[updateIndex] == 0 && (dirCount > 2 || dirCount < 2)) {
		tempVal = grid[index][sindex].weightToGetHere[dirCount] + grid[index + 1][sindex].steppingWeight;
		if (tempVal < grid[index + 1][sindex].weightToGetHere[updateIndex]) {
			grid[index + 1][sindex].weightToGetHere[updateIndex] = tempVal;
			tempPart.index = index + 1;
			tempPart.sindex = sindex;
			tempPart.weight = tempVal;
			tempPart.dirCount = updateIndex;
			error = insert(&heap, &tempPart, NULL, compareFunction);
			if (error) {
				printf("Heap error inserting\n");
				exit(-2);
			}
		}
	}

	if (dirCount > 2) {
		updateIndex = dirCount + 1;
	} else {
		updateIndex = 3;
	}

	if (sindex - 1 > -1 && grid[index][sindex - 1].visited[updateIndex] == 0 && dirCount < 5) {
		tempVal = grid[index][sindex].weightToGetHere[dirCount] + grid[index][sindex - 1].steppingWeight;
		if (tempVal < grid[index][sindex - 1].weightToGetHere[updateIndex]) {
			grid[index][sindex - 1].weightToGetHere[updateIndex] = tempVal;
			tempPart.index = index;
			tempPart.sindex = sindex - 1;
			tempPart.weight = tempVal;
			tempPart.dirCount = updateIndex;
			error = insert(&heap, &tempPart, NULL, compareFunction);
			if (error) {
				printf("Heap error inserting\n");
				exit(-2);
			}
		}
	}

	if (sindex + 1 < width && grid[index][sindex + 1].visited[updateIndex] == 0 && dirCount < 5) {
		tempVal = grid[index][sindex].weightToGetHere[dirCount] + grid[index][sindex + 1].steppingWeight;
		if (tempVal < grid[index][sindex + 1].weightToGetHere[updateIndex]) {
			grid[index][sindex + 1].weightToGetHere[updateIndex] = tempVal;
			tempPart.index = index;
			tempPart.sindex = sindex + 1;
			tempPart.weight = tempVal;
			tempPart.dirCount = updateIndex;
			error = insert(&heap, &tempPart, NULL, compareFunction);
			if (error) {
				printf("Heap error inserting\n");
				exit(-2);
			}
		}
	}
}


/*************************PART 2************************************/
static void startPath2(int16_t index, int16_t sindex) {
	char comp = 0;
	uint8_t dirCount = 0;
	AdvSelectionPart tempPart = { .index = 0, .sindex = 0, .weight = 0 };
	errno_t error;

	for (dirCount = 0; dirCount < 20; dirCount++) {
		grid[index][sindex].visited[dirCount] = 1;
		grid[index][sindex].weightToGetHere[dirCount] = 0;
	}

	grid[index + 1][sindex].weightToGetHere[0] = grid[index + 1][sindex].steppingWeight;
	grid[index + 2][sindex].weightToGetHere[1] = grid[index + 1][sindex].weightToGetHere[0] + grid[index + 2][sindex].steppingWeight;
	grid[index + 3][sindex].weightToGetHere[2] = grid[index + 2][sindex].weightToGetHere[1] + grid[index + 3][sindex].steppingWeight;
	grid[index + 4][sindex].weightToGetHere[3] = grid[index + 3][sindex].weightToGetHere[2] + grid[index + 4][sindex].steppingWeight;
	tempPart.index = index + 4;
	tempPart.sindex = sindex;
	tempPart.weight = grid[index + 4][sindex].weightToGetHere[3];
	tempPart.dirCount = 3;
	tempPart.direction = SOUTH;
	error = insert(&heap, &tempPart, NULL, compareFunction);
	if (error) {
		printf("Heap error inserting \n");
		exit(-2);
	}
	grid[index][sindex + 1].weightToGetHere[10] = grid[index][sindex + 1].steppingWeight;
	grid[index][sindex + 2].weightToGetHere[11] = grid[index][sindex + 1].weightToGetHere[10] + grid[index][sindex + 2].steppingWeight;
	grid[index][sindex + 3].weightToGetHere[12] = grid[index][sindex + 2].weightToGetHere[11] + grid[index][sindex + 3].steppingWeight;
	grid[index][sindex + 4].weightToGetHere[13] = grid[index][sindex + 3].weightToGetHere[12] + grid[index][sindex + 4].steppingWeight;
	tempPart.index = index;
	tempPart.sindex = sindex + 4;
	tempPart.weight = grid[index][sindex + 4].weightToGetHere[13];
	tempPart.dirCount = 13;
	tempPart.direction = EAST;
	error = insert(&heap, &tempPart, NULL, compareFunction);
	if (error) {
		printf("Heap error inserting\n");
		exit(-2);
	}
	while (comp == 0) {
		error = removeSmallest(&heap, NULL, compareFunction, &tempPart);
		if (error) {
			printf("Heap error removing\n");
			exit(-3);
		}
		if (grid[tempPart.index][tempPart.sindex].visited[tempPart.dirCount] == 0) {
			calcPaths2(tempPart.index, tempPart.sindex, tempPart.dirCount, tempPart.direction);
		}
		for (dirCount = 0; dirCount < 20; dirCount++) {
			if (grid[height - 1][width - 1].visited[dirCount] == 1) {
				comp = 1;
				break;
			}
		}
	}
}

static void calcPaths2(int16_t index, int16_t sindex, uint8_t dirCount, AdvDirection direction) {
	int8_t dir = 0;
	uint8_t updateIndex = 0;
	AdvSelectionPart tempPart = { .index = 0, .sindex = 0, .weight = 0 };
	BinaryHeapReturnCodes error;

	grid[index][sindex].visited[dirCount] = 1;
	if (dirCount > 9) {
		dir = 1;
	}
	
	if (dir == 0) {
		updateIndex = dirCount + 1;
		if (index + 1 < height && grid[index + 1][sindex].visited[updateIndex] == 0 && dirCount < 9 && direction == SOUTH) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount] + grid[index + 1][sindex].steppingWeight;
			if (tempPart.weight < grid[index + 1][sindex].weightToGetHere[updateIndex]) {
				grid[index + 1][sindex].weightToGetHere[updateIndex] = tempPart.weight;
				tempPart.index = index + 1;
				tempPart.sindex = sindex;
				tempPart.dirCount = updateIndex;
				tempPart.direction = SOUTH;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
		if (index - 1 > -1 && grid[index - 1][sindex].visited[updateIndex] == 0 && dirCount < 9 && direction == NORTH) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount] + grid[index - 1][sindex].steppingWeight;
			if (tempPart.weight < grid[index - 1][sindex].weightToGetHere[updateIndex]) {
				grid[index - 1][sindex].weightToGetHere[updateIndex] = tempPart.weight;
				tempPart.index = index - 1;
				tempPart.sindex = sindex;
				tempPart.dirCount = updateIndex;
				tempPart.direction = NORTH;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}

		if (sindex + 4 < width && grid[index][sindex + 4].visited[13] == 0) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount];
			for (updateIndex = 1; updateIndex < 5; updateIndex++) {
				tempPart.weight += grid[index][sindex + updateIndex].steppingWeight;
			}
			if (tempPart.weight < grid[index][sindex + 4].weightToGetHere[13]) {
				grid[index][sindex + 4].weightToGetHere[13] = tempPart.weight;
				tempPart.index = index;
				tempPart.sindex = sindex + 4;
				tempPart.dirCount = 13;
				tempPart.direction = EAST;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
		if (sindex - 4 > -1 && grid[index][sindex - 4].visited[13] == 0) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount];
			for (updateIndex = 1; updateIndex < 5; updateIndex++) {
				tempPart.weight += grid[index][sindex - updateIndex].steppingWeight;
			}
			if (tempPart.weight < grid[index][sindex - 4].weightToGetHere[13]) {
				grid[index][sindex - 4].weightToGetHere[13] = tempPart.weight;
				tempPart.index = index;
				tempPart.sindex = sindex - 4;
				tempPart.dirCount = 13;
				tempPart.direction = WEST;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
	} else {
		updateIndex = dirCount + 1;
		if (sindex + 1 < width && dirCount < 19 && grid[index][sindex + 1].visited[updateIndex] == 0 && direction == EAST) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount] + grid[index][sindex + 1].steppingWeight;
			if (tempPart.weight < grid[index][sindex + 1].weightToGetHere[updateIndex]) {
				grid[index][sindex + 1].weightToGetHere[updateIndex] = tempPart.weight;
				tempPart.index = index;
				tempPart.sindex = sindex + 1;
				tempPart.dirCount = updateIndex;
				tempPart.direction = EAST;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
		if (sindex - 1 > -1 && dirCount < 19 && grid[index][sindex - 1].visited[updateIndex] == 0 && direction == WEST) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount] + grid[index][sindex - 1].steppingWeight;
			if (tempPart.weight < grid[index][sindex - 1].weightToGetHere[updateIndex]) {
				grid[index][sindex - 1].weightToGetHere[updateIndex] = tempPart.weight;
				tempPart.index = index;
				tempPart.sindex = sindex - 1;
				tempPart.dirCount = updateIndex;
				tempPart.direction = WEST;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}

		if (index + 4 < height && grid[index + 4][sindex].visited[3] == 0) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount];
			for (updateIndex = 1; updateIndex < 5; updateIndex++) {
				tempPart.weight += grid[index + updateIndex][sindex].steppingWeight;
			}
			if (tempPart.weight < grid[index + 4][sindex].weightToGetHere[3]) {
				grid[index + 4][sindex].weightToGetHere[3] = tempPart.weight;
				tempPart.index = index + 4;
				tempPart.sindex = sindex;
				tempPart.dirCount = 3;
				tempPart.direction = SOUTH;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
		if (index - 4 > -1 && grid[index - 4][sindex].visited[3] == 0) {
			tempPart.weight = grid[index][sindex].weightToGetHere[dirCount];
			for (updateIndex = 1; updateIndex < 5; updateIndex++) {
				tempPart.weight += grid[index - updateIndex][sindex].steppingWeight;
			}
			if (tempPart.weight < grid[index - 4][sindex].weightToGetHere[3]) {
				grid[index - 4][sindex].weightToGetHere[3] = tempPart.weight;
				tempPart.index = index - 4;
				tempPart.sindex = sindex;
				tempPart.dirCount = 3;
				tempPart.direction = NORTH;
				error = insert(&heap, &tempPart, NULL, compareFunction);
				if (error) {
					printf("Heap error inserting\n");
					exit(-2);
				}
			}
		}
	}
}

static int compareFunction(const void* item1, const void* item2, const void* context) {
	AdvSelectionPart i1 = *(AdvSelectionPart*)item1;
	AdvSelectionPart i2 = *(AdvSelectionPart*)item2;
	return (i1.weight > i2.weight) - (i1.weight < i2.weight);
}