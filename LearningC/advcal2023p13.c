#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

adv2023p13(){
//main() {
	FILE* fptr;
	errno_t error;
	char grid[20][20] = { '\0' };
	int32_t index = 0;
	int32_t sindex = 0;
	int32_t indexSize = 0;
	int32_t sindexSize = 0;
	int32_t dif = 0;
	char match = 0;
	uint64_t sum = 0;
	uint64_t sum2 = 0;
	int32_t cindex = 0;
	int32_t csindex = 0;
	int32_t indexs = -1;
	int32_t sindexs = -1;

	error = fopen_s(&fptr, "input2023p13.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");

	if (!error) {
		do {
			index = 0;
			indexSize = 0;
			sindex = 0;
			sindexSize = 0;
			match = 0;
			dif = 0;
			grid[0][0] = '\n';
			indexs = -1;
			sindexs = -1;
			do {
				fgets(grid[index], 20, fptr);
				index++;
			} while (grid[index - 1][0] != '\n');
			indexSize = index - 1;
			//printf("%d\n", indexSize);
			if (indexSize == 0) {
				break;
			}
			index = 0;
			while (sindex < 20 && grid[index][sindex] != '\n') {
				sindex++;
			}
			sindexSize = sindex;
			sindex = 0;
			//check rows first
			while (index - dif >= 0 && index + 1 + dif < indexSize) {
				if (strcmp(grid[index - dif], grid[index + 1 + dif]) == 0) {
					dif++;
					match = 1;
				} else {
					dif = 0;
					index++;
					match = 0;
				}
			}
			if (match == 1) {
				sum += (index + 1) * 100;
				indexs = index;
			} else {
				//check columns
				index = 0;
				dif = 0;
				while (sindex - dif >= 0 && sindex + 1 + dif < sindexSize) {
					while (index < indexSize && grid[index][sindex - dif] == grid[index][sindex + 1 + dif]) {
						index++;
					}
					if (index == indexSize) {
						dif++;
					} else {
						sindex++;
						dif = 0;
					}
					index = 0;
				}
				sum += sindex + 1;
				sindexs = sindex;
			}
			match = 0;
			cindex = 0;
			csindex = 0;
			while (match == 0) {
				switch (grid[cindex][csindex]) {
				case '.':
					grid[cindex][csindex] = '#';
					break;
				case '#':
					grid[cindex][csindex] = '.';
					break;
				}
				index = 0;
				if (index == indexs) {
					index++;
				}
				sindex = 0;
				dif = 0;
				while (index - dif >= 0 && index + 1 + dif < indexSize) {
					if (strcmp(grid[index - dif], grid[index + 1 + dif]) == 0) {
						dif++;
						match = 1;
					} else {
						dif = 0;
						index++;
						if (index == indexs) {
							index++;
						}
						match = 0;
					}
				}
				if (match == 1) {
					printf("digit: %d\n", index);
					sum2 += (index + 1) * 100;
				} else {
					//check columns
					index = 0;
					dif = 0;
					if (sindex == sindexs) {
						sindex++;
					}
					while (sindex - dif >= 0 && sindex + 1 + dif < sindexSize) {
						while (index < indexSize && grid[index][sindex - dif] == grid[index][sindex + 1 + dif]) {
							index++;
						}
						if (index == indexSize) {
							dif++;
							match = 1;
						} else {
							sindex++;
							if (sindex == sindexs) {
								sindex++;
							}
							dif = 0;
							match = 0;
						}
						index = 0;
					}
					if (match == 1) {
						sum2 += sindex + 1;
					}
				}
				switch (grid[cindex][csindex]) {
				case '.':
					grid[cindex][csindex] = '#';
					break;
				case '#':
					grid[cindex][csindex] = '.';
					break;
				}
				csindex++;
				if (csindex == sindexSize) {
					cindex++;
					csindex = 0;
				}
			}

		} while (1);
		printf("Part 1 sum: %llu\n", sum);
		printf("Part 2 sum: %llu\n", sum2);
		fclose(fptr);
	}
}