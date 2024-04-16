#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define GRID_SIZE 110

typedef enum energyDirection {
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
	
}AdvEnergyDirection;

typedef struct position {
	char holding;
	char energized;
	AdvEnergyDirection directionCame[4];
}AdvMirrorType;

static AdvMirrorType grid[GRID_SIZE][GRID_SIZE];
static uint16_t height = 0;
static uint16_t width = 0;

static void startBeam(AdvEnergyDirection direction, uint16_t index, uint16_t sindex);
static void sendBeam(AdvEnergyDirection direction, uint16_t index, uint16_t sindex);

static int adv2023p16(){
//int main() {
	FILE* fptr;
	errno_t error;
	char temp = '\0';
	uint16_t index = 0;
	uint16_t sindex = 0;
	uint16_t startx = 0;
	uint16_t starty = 0;
	uint64_t energized = 0;
	uint64_t maxEnergized = 0;

	error = fopen_s(&fptr, "input2023p16.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");

	if (!error) {
		temp = fgetc(fptr);
		while (temp != EOF) {
			if (temp == '\n') {
				index++;
				sindex = 0;
			} else {
				grid[index][sindex].energized = 0;
				grid[index][sindex].holding = temp;
				grid[index][sindex].directionCame[0] = NONE;
				sindex++;
			}
			temp = fgetc(fptr);
		}
		fclose(fptr);
		width = sindex;
		height = index + 1;
		sindex = 0;
		index = 0;
		grid[index][sindex].energized = 1;
		grid[index][sindex].directionCame[0] = EAST;
		switch (grid[index][sindex].holding) {
		case '\\':
			sendBeam(SOUTH, index, sindex);
			break;
		case '|':
			sendBeam(SOUTH, index, sindex);
			break;
		case '-':
		case '.':
			sendBeam(EAST, index, sindex);
			break;
		}

		for (index = 0; index < height; index++) {
			for (sindex = 0; sindex < width; sindex++) {
				energized += grid[index][sindex].energized;
				grid[index][sindex].energized = 0;
				grid[index][sindex].directionCame[0] = NONE;
				grid[index][sindex].directionCame[1] = NONE;
				grid[index][sindex].directionCame[2] = NONE;
				grid[index][sindex].directionCame[3] = NONE;
			}
		}

		printf("Total Energize: %llu\n", energized);
		maxEnergized = energized;
		energized = 0;
		for (startx = 1; startx < height; startx++) {
			startBeam(EAST, startx, starty);
			for (index = 0; index < height; index++) {
				for (sindex = 0; sindex < width; sindex++) {
					energized += grid[index][sindex].energized;
					grid[index][sindex].energized = 0;
					grid[index][sindex].directionCame[0] = NONE;
					grid[index][sindex].directionCame[1] = NONE;
					grid[index][sindex].directionCame[2] = NONE;
					grid[index][sindex].directionCame[3] = NONE;
				}
			}
			if (maxEnergized < energized) {
				maxEnergized = energized;
			}
			energized = 0;
		}
		startx--;
		for (starty = 0; starty < width; starty++) {
			startBeam(NORTH, startx, starty);
			for (index = 0; index < height; index++) {
				for (sindex = 0; sindex < width; sindex++) {
					energized += grid[index][sindex].energized;
					grid[index][sindex].energized = 0;
					grid[index][sindex].directionCame[0] = NONE;
					grid[index][sindex].directionCame[1] = NONE;
					grid[index][sindex].directionCame[2] = NONE;
					grid[index][sindex].directionCame[3] = NONE;
				}
			}
			if (maxEnergized < energized) {
				maxEnergized = energized;
			}
			energized = 0;
		}
		starty--;
		while(startx < height) {
			startBeam(WEST, startx, starty);
			for (index = 0; index < height; index++) {
				for (sindex = 0; sindex < width; sindex++) {
					energized += grid[index][sindex].energized;
					grid[index][sindex].energized = 0;
					grid[index][sindex].directionCame[0] = NONE;
					grid[index][sindex].directionCame[1] = NONE;
					grid[index][sindex].directionCame[2] = NONE;
					grid[index][sindex].directionCame[3] = NONE;
				}
			}
			if (maxEnergized < energized) {
				maxEnergized = energized;
			}
			energized = 0;
			startx--;
		}
		startx = 0;
		while (starty < width) {
			startBeam(SOUTH, startx, starty);
			for (index = 0; index < height; index++) {
				for (sindex = 0; sindex < width; sindex++) {
					energized += grid[index][sindex].energized;
					grid[index][sindex].energized = 0;
					grid[index][sindex].directionCame[0] = NONE;
					grid[index][sindex].directionCame[1] = NONE;
					grid[index][sindex].directionCame[2] = NONE;
					grid[index][sindex].directionCame[3] = NONE;
				}
			}
			if (maxEnergized < energized) {
				maxEnergized = energized;
			}
			energized = 0;
			starty--;
		}
		printf("Max energized: %llu\n", maxEnergized);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}

static void startBeam(AdvEnergyDirection direction, uint16_t index, uint16_t sindex) {
	if (index >= 0 && index < height && sindex >= 0 && sindex < width) {
		grid[index][sindex].energized = 1;
		grid[index][sindex].directionCame[0] = direction;
		switch (grid[index][sindex].holding) {
		case '\\':
			switch (direction) {
			case NORTH:
				sendBeam(WEST, index, sindex);
				break;
			case SOUTH:
				sendBeam(EAST, index, sindex);
				break;
			case EAST:
				sendBeam(SOUTH, index, sindex);
				break;
			case WEST:
				sendBeam(NORTH, index, sindex);
				break;
			}
			break;
		case '/':
			switch (direction) {
			case NORTH:
				sendBeam(EAST, index, sindex);
				break;
			case SOUTH:
				sendBeam(WEST, index, sindex);
				break;
			case EAST:
				sendBeam(NORTH, index, sindex);
				break;
			case WEST:
				sendBeam(SOUTH, index, sindex);
				break;
			}
			break;
		case '|':
			switch (direction) {
			case NORTH:
			case SOUTH:
				sendBeam(direction, index, sindex);
				break;
			case EAST:
			case WEST:
				sendBeam(NORTH, index, sindex);
				sendBeam(SOUTH, index, sindex);
				break;
			}
			break;
		case '-':
			switch (direction) {
			case NORTH:
			case SOUTH:
				sendBeam(EAST, index, sindex);
				sendBeam(WEST, index, sindex);
				break;
			case EAST:
			case WEST:
				sendBeam(direction, index, sindex);
				break;
			}
			break;
		case '.':
			sendBeam(direction, index, sindex);
			break;
		}
	}
}

static void sendBeam(AdvEnergyDirection direction, uint16_t index, uint16_t sindex) {
	uint8_t i = 0;
	switch (direction) {
	case NORTH:
		index--;
		break;
	case SOUTH:
		index++;
		break;
	case EAST:
		sindex++;
		break;
	case WEST:
		sindex--;
		break;
	}
	
	if (index >= 0 && index < height && sindex >= 0 && sindex < width) {
		grid[index][sindex].energized = 1;
		for (i = 0; i < 4; i++) {
			if (grid[index][sindex].directionCame[i] == NONE) {
				grid[index][sindex].directionCame[i] = direction;
				break;
			} else if (grid[index][sindex].directionCame[i] == direction) {
				return;
			}
		}
		switch (grid[index][sindex].holding) {
		case '\\':
			switch (direction) {
			case NORTH:
				sendBeam(WEST, index, sindex);
				break;
			case SOUTH:
				sendBeam(EAST, index, sindex);
				break;
			case EAST:
				sendBeam(SOUTH, index, sindex);
				break;
			case WEST:
				sendBeam(NORTH, index, sindex);
				break;
			}
			break;
		case '/':
			switch (direction) {
			case NORTH:
				sendBeam(EAST, index, sindex);
				break;
			case SOUTH:
				sendBeam(WEST, index, sindex);
				break;
			case EAST:
				sendBeam(NORTH, index, sindex);
				break;
			case WEST:
				sendBeam(SOUTH, index, sindex);
				break;
			}
			break;
		case '|':
			switch (direction) {
			case NORTH:
			case SOUTH:
				sendBeam(direction, index, sindex);
				break;
			case EAST:
			case WEST:
				sendBeam(NORTH, index, sindex);
				sendBeam(SOUTH, index, sindex);
				break;
			}
			break;
		case '-':
			switch (direction) {
			case NORTH:
			case SOUTH:
				sendBeam(EAST, index, sindex);
				sendBeam(WEST, index, sindex);
				break;
			case EAST:
			case WEST:
				sendBeam(direction, index, sindex);
				break;
			}
			break;
		case '.':
			sendBeam(direction, index, sindex);
			break;
		}
	}
}