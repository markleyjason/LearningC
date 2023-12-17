#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAXGRIDSIZE 140

typedef enum pipe_type {
	NorthSouth,
	EastWest,
	NorthEast,
	NorthWest,
	SouthWest,
	SouthEast,
	Start,
	Ground
}pipe_type;

typedef struct LoopProperties {
	uint16_t firstmIndex;
	uint16_t secondmIndex;
	uint16_t firstsIndex;
	uint16_t secondsIndex;
	uint32_t length;
}LoopProperties;

typedef struct PolygonVertice {
	int32_t x;
	int32_t y;
}PolygonVertice;

static pipe_type connectionDirection(const char piece);
static LoopProperties checkLoop(const uint16_t startm, const uint16_t starts, uint16_t nextm, uint16_t nexts, const uint16_t size);

pipe_type input_grid[MAXGRIDSIZE][MAXGRIDSIZE] = { 0 };

pipe_type pipe_grid[MAXGRIDSIZE][MAXGRIDSIZE] = { 0 };

PolygonVertice boundingBox[14000];

adv2023p10(){
//main() {
	FILE* fptr;
	errno_t error;
	uint16_t mindex = 0;
	uint16_t sindex = 0;
	uint16_t startmIndex = 0;
	uint16_t startsIndex = 0;
	uint16_t size = 0;
	uint32_t index = 0;
	int64_t area = 0;
	char temp = '\0';
	LoopProperties lp = { .firstmIndex = 0, .firstsIndex = 0, .secondmIndex = 0, .secondsIndex = 0, .length = 0 };

	error = fopen_s(&fptr, "input2023p10.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		temp = fgetc(fptr);
		while (temp != EOF) {
			if (temp != '\n') {
				input_grid[mindex][sindex] = connectionDirection(temp);
				if (temp == 'S') {
					startmIndex = mindex;
					startsIndex = sindex;
				}
				sindex++;
			} else {
				mindex++;
				sindex = 0;
			}
			size = mindex;
			temp = fgetc(fptr);
		}
		fclose(fptr);

		boundingBox[0].x = startmIndex;
		boundingBox[0].y = startsIndex;

		mindex = startmIndex + 1;
		sindex = startsIndex;
		temp = 0;
		while (lp.length == 0 && temp < 4) {
			lp = checkLoop(startmIndex, startsIndex, mindex, sindex, size);
			switch (temp) {
			case 0:
				mindex--;
				sindex++;
				temp = 1;
				break;
			case 1:
				mindex--;
				sindex--;
				temp = 2;
				break;
			case 2:
				mindex++;
				sindex--;
				temp = 3;
				break;
			}
		}

		for (index = 0; index <= lp.length; index++) {
			area += boundingBox[index].x * boundingBox[index + 1].y - boundingBox[index + 1].x * boundingBox[index].y;
		}
		
		printf("Length is: %d\n", lp.length / 2 + 1);
		printf("Bounding area: %lld\n", (area / 2) - (lp.length / 2));
	} else {
		printf("Couldn't open file\n");
		return -1;
	}
	return 0;
}

static pipe_type connectionDirection(const char piece) {
	switch (piece) {
	case '|':
		return NorthSouth;
	case '-':
		return EastWest;
	case 'L':
		return NorthEast;
	case 'J':
		return NorthWest;
	case '7':
		return SouthWest;
	case 'F':
		return SouthEast;
		break;
	case 'S':
		return Start;
	case '.':
		return Ground;
	default:
		return -1;
	}
}

static LoopProperties checkLoop(const uint16_t startm, const uint16_t starts, uint16_t nextm, uint16_t nexts, const uint16_t size) {
	LoopProperties lp = { .firstmIndex = startm, .firstsIndex = starts, .secondmIndex = startm, .secondsIndex = starts, .length = 0 };
	uint16_t temp;
	char found = 0;

	//find the directions it connects (will give the start and the end
	while (found == 0 && nextm >= 0 && nextm <= size && nexts >= 0 && nexts <= size) {
		//find next
		switch (input_grid[nextm][nexts]) {
		case NorthSouth:
			//printf("Next Step is: NorthSouth, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			temp = nextm;
			nextm += (lp.secondmIndex < nextm) ? 1 : -1;
			lp.secondmIndex = temp;
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case EastWest:
			//printf("Next Step is: EastWest, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			temp = nexts;
			nexts += (lp.secondsIndex < nexts) ? 1 : -1;
			lp.secondsIndex = temp;
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case NorthEast:
			//printf("Next Step is: NorthEast, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			if (lp.secondmIndex < nextm) {
				lp.secondmIndex++;
				nexts++;
			} else {
				lp.secondsIndex--;
				nextm--;
			}
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case NorthWest:
			//printf("Next Step is: NorthWest, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			if (lp.secondmIndex < nextm) {
				lp.secondmIndex++;
				nexts--;
			} else {
				lp.secondsIndex++;
				nextm--;
			}
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case SouthWest:
			//printf("Next Step is: SouthWest, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			if (lp.secondmIndex == nextm) {
				lp.secondsIndex++;
				nextm++;
			} else {
				lp.secondmIndex--;
				nexts--;
			}
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case SouthEast:
			//printf("Next Step is: SouthEast, previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			if (lp.secondmIndex == nextm) {
				lp.secondsIndex--;
				nextm++;
			} else {
				lp.secondmIndex--;
				nexts++;
			}
			lp.length++;
			boundingBox[lp.length].x = lp.secondmIndex;
			boundingBox[lp.length].y = lp.secondsIndex;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case Start:
			found = 1;
			boundingBox[lp.length + 1].x = nextm;
			boundingBox[lp.length + 1].y = nexts;
			//printf("Steps became------------->previous (%d, %d) current (%d, %d) length: %d\n", lp.secondmIndex, lp.secondsIndex, nextm, nexts, lp.length);
			break;
		case '.':
			lp.length = 0;
			return lp;
		}
	}
	
	return lp;
}