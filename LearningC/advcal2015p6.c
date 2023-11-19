#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

void turnOn(__int32* grid, const __int32, __int32*, __int32*);
void turnOff(__int32* grid, const __int32, __int32*, __int32*);
void toggle(__int32* grid, const __int32, __int32*, __int32*);
__int32 count(__int32* grid, const __int32);

enum {
	ON = 0,
	OFF = 1,
	TOGGLE = 2
};

__int32 grid[1000][1000] = { 0 };

adv2015p6() {
	FILE* fptr;
	char line[34];
	char decision = 0;
	__int32 start_coord[2];
	__int32 end_coord[2];
	__int32 buffer_length = 34;
	__int32 error;
	__int32 line_pos = 0;
	__int32 coord_part = 0;
	__int32 factor = 10;
	__int32 answer;
	const __int32 GRID_SIZE = 1000;
	const __int32 DECISION_POINT = 6;
	

	error = fopen_s(&fptr, "input2015p6.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, buffer_length, fptr) != NULL) {
			printf("The line is: %s\n", line);
			if (line[0] == '\n') {
				printf("WFT");
			}
			start_coord[0] = 0;
			start_coord[1] = 0;
			end_coord[0] = 0;
			end_coord[1] = 0;
			line_pos = 0;
			//read option, may be two words or one (turn off/on, toggle)
			while (!isDigit(line[line_pos]) && line_pos < buffer_length) {
				if (line_pos == DECISION_POINT) {
					if (line[line_pos] == ' ') {
						decision = TOGGLE;
					}
					else if (line[line_pos] == 'f') {
						decision = OFF;
					}
					else if (line[line_pos] == 'n') {
						decision = ON;
					}
				}
				line_pos++;
			}
			printf("The instruction is: %d\n", decision);
			//read first coord
			while (line[line_pos] != ' ') {
				if (line[line_pos] == ',') {
					coord_part = 1;
				}
				else if (isDigit(line[line_pos])) {
					start_coord[coord_part] = start_coord[coord_part] * factor + ctoai(line[line_pos]);
				}
				line_pos++;
			}
			printf("Start coord is: (%d,%d)\n", start_coord[0], start_coord[1]);
			coord_part = 0;
			//find second coord start
			while (!isDigit(line[line_pos])) {
				line_pos++;
			}

			//read second coord
			while (line[line_pos] != '\0' && line[line_pos] != '\n' &&
				line_pos < buffer_length) {
				if (line[line_pos] == ',') {
					coord_part = 1;
				}
				else {
					end_coord[coord_part] = end_coord[coord_part] * factor + ctoai(line[line_pos]);
				}
				line_pos++;
			}
			coord_part = 0;
			printf("End coord is: (%d,%d)\n", end_coord[0], end_coord[1]);

			//do instruction
			switch (decision) {
			case ON:
				turnOn(&grid[0][0], GRID_SIZE, start_coord, end_coord);
				break;
			case OFF:
				turnOff(&grid[0][0], GRID_SIZE, start_coord, end_coord);
				break;
			case TOGGLE:
				toggle(&grid[0][0], GRID_SIZE, start_coord, end_coord);
				break;
			}
		}
		answer = count(&grid[0][0], GRID_SIZE);

		printf("Number of lights on is: %d\n", answer);
		fclose(fptr);
	}
}

void turnOn(__int32* grid, const __int32 grid_size, __int32* start, __int32* end) {
	__int32 i, j;
	__int32 x, y;
	__int32* row_start;
	i = start[0];
	j = start[1];
	x = end[0];
	y = end[1];

	while (i <= x && i < grid_size) {
		row_start = &grid[i * grid_size];
		while (j <= y && j < grid_size) {
			row_start[j] += 1;
			j++;
		}
		j = start[1];
		i++;
	}
}
void turnOff(__int32* grid, const __int32 grid_size, __int32* start, __int32* end) {
	__int32 i, j;
	__int32 x = 0, y = 0;
	__int32* row_start;
	i = start[0];
	j = start[1];
	x = end[0];
	y = end[1];

	while (i <= x && i < grid_size) {
		row_start = &grid[i * grid_size];
		while (j <= y && j < grid_size) {
			if (row_start[j] > 0) {
				row_start[j]--;
			}
			j++;
		}
		j = start[1];
		i++;
	}
}
void toggle(__int32* grid, const __int32 grid_size, __int32* start, __int32* end) {
	__int32 i, j;
	__int32 x = 0, y = 0;
	__int32* row_start;
	
	i = start[0];
	j = start[1];
	x = end[0];
	y = end[1];

	while (i <= x && i < grid_size) {
		row_start = &grid[i * grid_size];
		while (j <= y && j < grid_size) {
			row_start[j] += 2;
			j++;
		}
		j = start[1];
		i++;
	}
}
__int32 count(__int32* grid, const __int32 grid_size) {
	__int32 ans = 0;
	__int32 i, j;
	__int32* row_start;

	for (i = 0; i < grid_size; i++) {
		row_start = &grid[i * grid_size];
		for (j = 0; j < grid_size; j++) {
			ans += row_start[j];
		}
	}

	return ans;
}