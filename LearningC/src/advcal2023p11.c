#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAXGRID 140
#define MAXEXPANDEDGRID 280
#define BUFFER 142

typedef struct TWODPoint{
	int64_t x;
	int64_t y;
}TWODPoint;

static char galaxyGrid[MAXGRID][MAXGRID] = { 0 };
static TWODPoint galaxies[433];

static int adv2023p11(){
//main() {
	FILE* fptr;
	errno_t error;
	uint64_t sum = 0;
	uint16_t mindex = 0;
	uint16_t sindex = 0;
	char line[BUFFER] = { '\0' };
	uint16_t width = 0;
	uint16_t height = 0;
	uint64_t count = 0;
	int64_t tempSum = 0;
	uint32_t galaxyCount = 0;
	uint64_t xIncrease[MAXGRID] = { 0 };
	uint64_t yIncrease[MAXGRID] = { 0 };

	error = fopen_s(&fptr, "input2023p11.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, BUFFER, fptr) != NULL) {
			sindex = 0;
			count = 0;
			while (line[sindex] != '\n' && line[sindex] != EOF && line[sindex] != '\0') {
				galaxyGrid[mindex][sindex] = line[sindex];
				if (line[sindex] == '.') {
					count++;
				}
				sindex++;
			}
			mindex++;
			width = sindex;
			if (count == sindex) {
				yIncrease[mindex] = 999999;
			}
		}
		height = mindex;
		for (sindex = 0; sindex < width; sindex++) {
			count = 0;
			for (mindex = 0; mindex < height; mindex++) {
				if (galaxyGrid[mindex][sindex] == '.') {
					count++;
				} else {
					break;
				}
			}
			if (count == height) {
				xIncrease[sindex] = 999999;
			}
		}
		fclose(fptr);
		tempSum = -1;
		for (mindex = 0; mindex < height; mindex++) {
			tempSum += yIncrease[mindex] + 1;
			count = -1;
			for (sindex = 0; sindex < width; sindex++) {
				count += xIncrease[sindex] + 1;
				if (galaxyGrid[mindex][sindex] == '#') {
					galaxies[galaxyCount].x = count;
					galaxies[galaxyCount].y = tempSum;
					galaxyCount++;
				}
			}
		}

		tempSum = 0;
		for (mindex = 0; mindex < galaxyCount - 1; mindex++) {
			for (sindex = mindex + 1; sindex < galaxyCount; sindex++) {
				tempSum = galaxies[mindex].x - galaxies[sindex].x;
				if (tempSum < 0) {
					tempSum = tempSum * -1;
				}
				sum += tempSum;
				tempSum = galaxies[mindex].y - galaxies[sindex].y;
				if (tempSum < 0) {
					tempSum = tempSum * -1;
				}
				sum += tempSum;
			}
		}

		printf("Sum of the lengths: %llu\n", sum);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}