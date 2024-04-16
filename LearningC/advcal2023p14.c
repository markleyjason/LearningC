#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hashtable.h>

#define GRID_SIZE 102

typedef struct advp14grid {
	char theGrid[GRID_SIZE][GRID_SIZE];
	uint16_t rows;
	uint16_t width;
}advp14grid;

int32_t gridHash(const void* data, const void* context);
int32_t gridComp(const void* item1, const void* item2, const void* context);
static void rotateNorth(uint16_t rows);
static void rotateWest(uint16_t rows, uint16_t width);
static void rotateEast(uint16_t rows, uint16_t width);
static void rotateSouth(uint16_t rows);

static char grid[GRID_SIZE][GRID_SIZE] = { '\0' };
static char line[GRID_SIZE] = { '\0' };

static advp14grid tempGrid = { .rows = 0, .width = 0, .theGrid = {'\0' } };
static advp14grid tempGridMain = { .rows = 0, .width = 0, .theGrid = {'\0' } };

static hashtable theTable;

static int adv2023p14() {
//int main() {
	FILE* fptr;
	errno_t error;
	uint16_t index = 0;
	uint16_t sindex = 0;
	uint16_t movingPosition = 0;
	uint16_t rows = 0;
	uint16_t width = 0;
	
	uint32_t totalLoad = 0;
	uint32_t steps = 0;
	int cmp = 0;
	
	


	setUpHashTable(&theTable, 3000, sizeof(advp14grid));
	error = fopen_s(&fptr, "input2023p14.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");

	if (!error) {
		while (fgets(line, GRID_SIZE, fptr) != NULL && index < GRID_SIZE) {
			strcpy_s(grid[index], GRID_SIZE, line);
			index++;
		}
		fclose(fptr);
		rows = index;
		width = (uint16_t)strlen(grid[0]) - 1;
		tempGrid.rows = rows;
		tempGrid.width = width;
		tempGridMain.rows = rows;
		tempGridMain.width = width;
		for (index = 0; index < rows; index++) {
			strcpy_s(tempGrid.theGrid[index], GRID_SIZE, grid[index]);
		}
		insertHashTable(&theTable, &tempGrid, NULL, &gridHash);
		//tilt
		movingPosition = 0;
		index = 0;
		while (grid[index][sindex] != '\0' && grid[index][sindex] != '\n') {
			while (index < rows && (grid[index][sindex] == 'O' || grid[index][sindex] == '#')) {
				if (grid[index][sindex] == 'O') {
					totalLoad += rows - index;
				}
				index++;
			}
			movingPosition = index;
			while (index < rows) {
				if (grid[index][sindex] == '#') {
					movingPosition = index + 1;
				} else if (grid[index][sindex] == 'O') {
					if (index != movingPosition) {
						grid[index][sindex] = '.';
						grid[movingPosition][sindex] = 'O';
						
					}
					totalLoad += rows - movingPosition;
					movingPosition++;
				}
				index++;
			}
			movingPosition = 0;
			sindex++;
			index = 0;
		}
		totalLoad = 0;
		for (index = 0; index < rows; index++) {
			for (sindex = 0; sindex < width; sindex++) {
				if (grid[index][sindex] == 'O') {
					totalLoad += rows - index;
				}
			}
		}
		printf("Total load is: %d\n", totalLoad);
		rotateWest(rows, width);
		rotateSouth(rows);
		rotateEast(rows, width);
		steps++;
		tempGrid.rows = rows;
		tempGrid.width = width;
		for (index = 0; index < rows; index++) {
			strcpy_s(tempGrid.theGrid[index], GRID_SIZE, grid[index]);
		}
		insertHashTable(&theTable, &tempGrid, NULL, &gridHash);
		while (steps < 1000000000) {
			
			rotateNorth(rows);
			rotateWest(rows, width);
			rotateSouth(rows);
			rotateEast(rows, width);
			steps++;
			index = 0;
			for (index = 0; index < rows; index++) {
				strcpy_s(tempGridMain.theGrid[index], GRID_SIZE, grid[index]);
			}
			if (containsItem(&theTable, &tempGridMain, NULL, &gridHash, NULL, &gridComp) != NULL) {
				break;
			} else {
				for (index = 0; index < rows; index++) {
					strcpy_s(tempGrid.theGrid[index], GRID_SIZE, grid[index]);
				}
				insertHashTable(&theTable, &tempGrid, NULL, &gridHash);
			}
			
		}
		cmp = -1;
		totalLoad = steps;
		while (cmp != 0 && steps < 1000000000) {
			rotateNorth(rows);
			rotateWest(rows, width);
			rotateSouth(rows);
			rotateEast(rows, width);
			steps++;
			for (index = 0; index < rows; index++) {
				strcpy_s(tempGrid.theGrid[index], GRID_SIZE, grid[index]);
			}
			if (gridComp(&tempGrid, &tempGridMain, NULL) == 0) {
				totalLoad = steps - totalLoad;
				break;
			}
		}
		while (steps + totalLoad < 1000000000) {
			steps += totalLoad;
		}
		while (steps < 1000000000) {
			rotateNorth(rows);
			rotateWest(rows, width);
			rotateSouth(rows);
			rotateEast(rows, width);
			steps++;
		}
		totalLoad = 0;
		for (index = 0; index < rows; index++) {
			for (sindex = 0; sindex < width; sindex++) {
				if (grid[index][sindex] == 'O') {
					totalLoad += rows - index;
				}
			}
		}
		printf("Total load is: %d\n", totalLoad);
	} else {
		printf("Error opening file\n");
		return -1;
	}
	return 0;
}

static void rotateNorth(uint16_t rows) {
	uint16_t index = 0;
	uint16_t sindex = 0;
	uint16_t movingPosition = 0;
	while (grid[index][sindex] != '\0' && grid[index][sindex] != '\n') {
		while (index < rows && (grid[index][sindex] == 'O' || grid[index][sindex] == '#')) {
			index++;
		}
		movingPosition = index;
		while (index < rows) {
			if (grid[index][sindex] == '#') {
				movingPosition = index + 1;
			} else if (grid[index][sindex] == 'O') {
				if (index != movingPosition) {
					grid[index][sindex] = '.';
					grid[movingPosition][sindex] = 'O';

				}
				movingPosition++;
			}
			index++;
		}
		movingPosition = 0;
		sindex++;
		index = 0;
	}
}
static void rotateWest(uint16_t rows, uint16_t width) {
	uint16_t index = 0;
	uint16_t sindex = 0;
	uint16_t movingPosition = 0;
	while (grid[index][sindex] != '\0' && grid[index][sindex] != '\n') {
		while (sindex < width && (grid[index][sindex] == 'O' || grid[index][sindex] == '#')) {
			sindex++;
		}
		movingPosition = sindex;
		while (sindex < width) {
			if (grid[index][sindex] == '#') {
				movingPosition = sindex + 1;
			} else if (grid[index][sindex] == 'O') {
				if (sindex != movingPosition) {
					grid[index][sindex] = '.';
					grid[index][movingPosition] = 'O';

				}
				movingPosition++;
			}
			sindex++;
		}
		movingPosition = 0;
		sindex = 0;
		index++;
	}
}

static void rotateEast(uint16_t rows, uint16_t width) {
	uint16_t index = 0;
	uint16_t sindex = width - 1;
	uint16_t movingPosition = 0;
	while (grid[index][sindex] != '\0' && grid[index][sindex] != '\n') {
		while (sindex < width && (grid[index][sindex] == 'O' || grid[index][sindex] == '#')) {
			sindex--;
		}
		movingPosition = sindex;
		while (sindex < width) {
			if (grid[index][sindex] == '#') {
				movingPosition = sindex - 1;
			} else if (grid[index][sindex] == 'O') {
				if (sindex != movingPosition) {
					grid[index][sindex] = '.';
					grid[index][movingPosition] = 'O';

				}
				movingPosition--;
			}
			sindex--;
		}
		movingPosition = width - 1;
		sindex = width - 1;
		index++;
	}
}
static void rotateSouth(uint16_t rows) {
	uint16_t index = rows - 1;
	uint16_t sindex = 0;
	uint16_t movingPosition = rows - 1;
	while (grid[index][sindex] != '\0' && grid[index][sindex] != '\n') {
		while (index < rows && index >= 0 && (grid[index][sindex] == 'O' || grid[index][sindex] == '#')) {
			index--;
		}
		movingPosition = index;
		while (index < rows && index >= 0) {
			if (grid[index][sindex] == '#') {
				movingPosition = index - 1;
			} else if (grid[index][sindex] == 'O') {
				if (index != movingPosition) {
					grid[index][sindex] = '.';
					grid[movingPosition][sindex] = 'O';

				}
				movingPosition--;
			}
			index--;
		}
		movingPosition = rows - 1;
		sindex++;
		index = rows - 1;
	}
}

static int32_t gridHash(const void* data, const void* context) {
	advp14grid* theData = (advp14grid*)data;
	int32_t hash = 0;
	uint32_t index = 0;
	while (index < theData->rows) {
		hash += theData->theGrid[index][0] * index;
		index++;
	}
	return hash;
}

int32_t gridComp(const void* item1, const void* item2, const void* context) {
	advp14grid* first = (advp14grid*)item1;
	advp14grid* second = (advp14grid*)item2;
	int32_t cmp = 0;
	uint16_t index = 0;
	if (first->rows == second->rows && first->width == second->width) {
		while (cmp == 0 && index < first->rows) {
			cmp = strcmp(first->theGrid[index], second->theGrid[index]);
			index++;
		}
	}
	return cmp;
}