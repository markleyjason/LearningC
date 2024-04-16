#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_COUNT 648
#define LINE_SIZE 20
#define COLOR_LENGTH 8

static enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

static struct Tunnel_Edge {
	enum direction dir;
	int64_t count;
	char color[COLOR_LENGTH];
};

static struct coord {
	int64_t x;
	int64_t y;
};

static struct Tunnel_Edge inputs[MAX_COUNT];
static uint16_t input_size = 0;
static struct coord coords[MAX_COUNT + 1];
static uint16_t coords_size = 0;
static struct Tunnel_Edge inputs_p2[MAX_COUNT];
static struct coord coords_p2[MAX_COUNT + 1];

static int parse_line(const uint16_t index, const char line[LINE_SIZE], int64_t* area);
static int parse_line_part_2(const uint16_t index, const char line[LINE_SIZE], int64_t* area);

static int advent2023p18(){
//int main() {
	FILE* fptr;
	errno_t error;
	char line[LINE_SIZE] = { '\0' };
	uint16_t index = 0;
	int errors = 0;
	int64_t area = 0;
	int64_t per = 0;
	int64_t area_p2 = 0;
	int64_t per_p2 = 0;


	error = fopen_s(&fptr, "input2023p18.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (!error) {
		coords[0].x = 0;
		coords[0].y = 0;
		while (fgets(line, LINE_SIZE, fptr) != NULL) {
			parse_line(index, line, &area);
			parse_line_part_2(index, line, &area_p2);
			index++;
		}
		fclose(fptr);
		input_size = index;
		coords_size = index + 1;

		area = area / 2;
		if (area < 0) {
			area *= -1;
		}
		for (index = 0; index < input_size; index++) {
			per += inputs[index].count;
		}
		area = area + (per + 2) / 2;
		printf("Part 1: Area: %lld\n", area);
		/*for (area = 0; area < index + 1; area++) {
			printf("( %d, %d)\n", coords[area].x, coords[area].y);
		}*/
		area_p2 = area_p2 / 2;
		if (area_p2 < 0) {
			area_p2 *= -1;
		}
		for (index = 0; index < input_size; index++) {
			per_p2 += inputs_p2[index].count;
		}
		area_p2 = area_p2 + (per_p2 + 2) / 2;
		printf("Part 2: Area: %lld\n", area_p2);
	} else {
		printf("Error opening input file\n");
		return error;
	}
	return 0;
}

int parse_line(const uint16_t index, const char line[LINE_SIZE], int64_t* area) {
	uint16_t place = 0;
	uint16_t sPlace = 0;

	switch (line[place]) {
	case 'U':
		inputs[index].dir = UP;
		break;
	case 'D':
		inputs[index].dir = DOWN;
		break;
	case 'L':
		inputs[index].dir = LEFT;
		break;
	case 'R':
		inputs[index].dir = RIGHT;
		break;
	default:
		printf("Error parsing line %ud, %c not a known direction\n", index, line[place]);
		return -1;
	}
	place = 2;
	if (isDigit(line[place])) {
		inputs[index].count = ctoai(line[place]);
		place++;
		if (isDigit(line[place])) {
			inputs[index].count = inputs[index].count * 10 + ctoai(line[place]);
			place++;
		}
	} else {
		printf("Expected a digit at line %ud, got %c\n", index, line[place]);
		return -2;
	}

	place++;
	place++;
	//should be a # next
	if (line[place] == '#') {
		inputs[index].color[sPlace] = '#';
		place++;
		sPlace++;
		while (sPlace < COLOR_LENGTH) {
			inputs[index].color[sPlace] = line[place];
			sPlace++;
			place++;
		}
		inputs[index].color[sPlace - 1] = '\0';
	} else {
		printf("Expected # got %c for line %ud\n", line[place], index);
		return -3;
	}
	switch (inputs[index].dir) {
	case UP:
		coords[index + 1].y = coords[index].y + inputs[index].count;
		coords[index + 1].x = coords[index].x;
		break;
	case DOWN:
		coords[index + 1].y = coords[index].y - inputs[index].count;
		coords[index + 1].x = coords[index].x;
		break;
	case LEFT:
		coords[index + 1].x = coords[index].x  - inputs[index].count;
		coords[index + 1].y = coords[index].y;
		break;
	case RIGHT:
		coords[index + 1].x = coords[index].x  + inputs[index].count;
		coords[index + 1].y = coords[index].y;
		break;
	default:
		printf("Error finding the next coord\n");
	}
	(*area) += (coords[index].x * coords[index + 1].y - coords[index].y * coords[index + 1].x);
	return 0;
}

static int parse_line_part_2(const uint16_t index, const char line[LINE_SIZE], int64_t* area) {
	int place = 6;
	int i = 0;

	//printf("%c\n", line[place]);
	if (line[place] == '#') {
		place++;
	}
	//parse hex
	for (i = 0; i < 5; i++) {
		inputs_p2[index].count = inputs_p2[index].count * 16 + hctoai(line[place]);
		place++;
	}

	switch (line[place]) {
	case '0':
		inputs_p2[index].dir = RIGHT;
		break;
	case '1':
		inputs_p2[index].dir = DOWN;
		break;
	case '2':
		inputs_p2[index].dir = LEFT;
		break;
	case '3':
		inputs_p2[index].dir = UP;
		break;
	}

	switch (inputs_p2[index].dir) {
	case UP:
		coords_p2[index + 1].y = coords_p2[index].y + inputs_p2[index].count;
		coords_p2[index + 1].x = coords_p2[index].x;
		break;
	case DOWN:
		coords_p2[index + 1].y = coords_p2[index].y - inputs_p2[index].count;
		coords_p2[index + 1].x = coords_p2[index].x;
		break;
	case LEFT:
		coords_p2[index + 1].x = coords_p2[index].x - inputs_p2[index].count;
		coords_p2[index + 1].y = coords_p2[index].y;
		break;
	case RIGHT:
		coords_p2[index + 1].x = coords_p2[index].x + inputs_p2[index].count;
		coords_p2[index + 1].y = coords_p2[index].y;
		break;
	default:
		printf("Error finding the next coord\n");
	}
	(*area) += (coords_p2[index].x * coords_p2[index + 1].y - coords_p2[index].y * coords_p2[index + 1].x);

	return 0;
}