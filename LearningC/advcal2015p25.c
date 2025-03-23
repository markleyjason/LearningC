#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main201525() {
	int64_t start = 20151125;
	int64_t temp = 0;
	int64_t mult = 252533;
	int64_t div = 33554393; 
	int64_t row = 1;
	int64_t col = 1;

	while (!(row == 2981 && col == 3075)) {
		temp = start * mult;
		start = temp % div;
		if (row == 1) {
			row = col + 1;
			col = 1;
		} else {
			row--;
			col++;
		}
		printf("Testing: %llu, row: %llu, col: %llu\n", start, row, col);
	}
	return 0;
}