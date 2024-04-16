#include <stdio.h>

__int32 north_east[1000][1000] = { 0 };
__int32 north_west[1000][1000] = { 0 };
__int32 south_east[1000][1000] = { 0 };
__int32 south_west[1000][1000] = { 0 };

static __int32 insert(__int32, __int32);

enum {
	NORTH = '^',
	SOUTH = 'v',
	EAST = '>',
	WEST = '<'
};

adv2015p3() {
	__int32 x_pos_santa = 0;
	__int32 y_pos_santa = 0;
	__int32 x_pos_robot = 0;
	__int32 y_pos_robot = 0;
	__int32 moving = 1;
	__int32 error = 0;
	__int32 visited_houses = 1;
	char input_char;
	__int32 dup = 0;
	FILE* fptr;

	//need to add one to the starting position
	++north_east[x_pos_santa][y_pos_santa];

	error = fopen_s(&fptr, "input2015p3.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");
	if (!error) {
		input_char = (char)fgetc(fptr);
		while (input_char != EOF) {
			if (moving) {
				switch (input_char) {
				case NORTH:
					y_pos_santa++;
					break;
				case SOUTH:
					y_pos_santa--;
					break;
				case EAST:
					x_pos_santa++;
					break;
				case WEST:
					x_pos_santa--;
					break;
				}
				dup = insert(x_pos_santa, y_pos_santa);
				moving = 0;
			} else {
				switch (input_char) {
				case NORTH:
					y_pos_robot++;
					break;
				case SOUTH:
					y_pos_robot--;
					break;
				case EAST:
					x_pos_robot++;
					break;
				case WEST:
					x_pos_robot--;
					break;
				}
				dup = insert(x_pos_robot, y_pos_robot);
				moving = 1;
			}
			

			//now need to check if it is a duplicate house
			if (dup == 1) {
				visited_houses++;
			}
			printf("House visited so far: %d\n", visited_houses);
			input_char = (char)fgetc(fptr);
		}
	}

	printf("House visited: %d\n", visited_houses);
}

static __int32 insert(__int32 x_pos, __int32 y_pos) {
	__int32 array_pos_count;

	printf("Coord is (%d, %d)\n", x_pos, y_pos);
	if (x_pos >= 0) {
		if (y_pos >= 0) {
			array_pos_count = ++north_east[x_pos][y_pos];
		} else {
			array_pos_count = ++south_east[x_pos][-1 * y_pos];
		}
	} else {
		if (y_pos >= 0) {
			array_pos_count = ++north_west[-1 * x_pos][y_pos];
		}
		else {
			array_pos_count = ++south_west[-1 * x_pos][-1 * y_pos];
		}
	}
	printf("Times visited: %d\n", array_pos_count);
	return array_pos_count;
}