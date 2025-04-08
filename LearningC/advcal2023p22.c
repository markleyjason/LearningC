#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helper.h"

#define LINE 17
#define MAX_BRICKS 1500
#define MAX_Z 400

struct brick_2322 {
	int32_t s_x;
	int32_t s_y;
	int32_t s_z;
	int32_t e_x;
	int32_t e_y;
	int32_t e_z;
	int16_t num_supporting;
	struct brick_2322* supporting[MAX_BRICKS];
	int16_t num_supporters;
	struct brick_2322* supporters[MAX_BRICKS];
	char safe;
};

struct brick_2322 bricks_2322[MAX_BRICKS];
int16_t bricks_2322_size = 0;
int16_t start_index[MAX_Z];

struct brick_2322 bricks_2322_p2[MAX_BRICKS];
int16_t bricks_2322_size_p2 = 0;
int16_t start_index_p2[MAX_Z];
int32_t fall_count = 0;

void sift_down();
void populate_support();
void sift_down_p2();
int16_t find_dis_count();
void find_fall_count();
char check_support(int16_t brick, int16_t start, int16_t end);
char check_overlap(struct brick_2322* brick1, struct brick_2322* brick2);
int16_t update_order(int16_t brick);
char check_support_2(int16_t brick, int16_t start, int16_t end);
int16_t update_order_2(int16_t brick);
int16_t find_nonnegative(char part, int16_t start);
int bricks_2322_comp(void* context, const void* item1, const void* item2);

int adv2023p22() {
//int main() {
	FILE* fptr;
	errno_t error;
	char line[LINE] = "\0";
	int32_t index = 0;
	int8_t num_ind = 0;
	char num[4] = "\0";

	error = fopen_s(&fptr, "input2023p22.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Error reading file\n");
		return -1;
	}

	while (fgets(line, LINE, fptr) != NULL) {
		//process
		index = 0;
		while (line[index] != '\n' && line[index] != '\0') {
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].s_x = stoai(num);
			index++;
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].s_y = stoai(num);
			index++;
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].s_z = stoai(num);
			index++;
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].e_x = stoai(num);
			index++;
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].e_y = stoai(num);
			index++;
			num_ind = 0;
			while (isDigit(line[index]) && num_ind < 3) {
				num[num_ind] = line[index];
				index++;
				num_ind++;
			}
			num[num_ind] = '\0';
			bricks_2322[bricks_2322_size].e_z = stoai(num);
			bricks_2322[bricks_2322_size].num_supporters = 0;
			bricks_2322[bricks_2322_size].num_supporting = 0;
			index++;
			bricks_2322_size++;
			num_ind = 0;
		}
	}
	fclose(fptr);

	for (index = 0; index < MAX_Z; index++) {
		start_index[index] = -1;
	}

	qsort_s(bricks_2322, bricks_2322_size, sizeof(struct brick_2322), bricks_2322_comp, NULL);

	for (index = 0; index < bricks_2322_size; index++) {
		if (start_index[bricks_2322[index].e_z - 1] == -1) {
			start_index[bricks_2322[index].e_z - 1] = index;
		}
	}

	sift_down();
	//qsort_s(bricks_2322, bricks_2322_size, sizeof(struct brick_2322), bricks_2322_comp, NULL);
	
	populate_support();

	printf("Part 1 count: %d\n", find_dis_count());

	find_fall_count();
	printf("Part 2 count: %lu\n", fall_count);

	return 0;
}


void sift_down() {
	int16_t index = 0;
	int16_t cur = 0;
	char supported = 0;
	for (index = 0; index < bricks_2322_size; index++) {
		if (bricks_2322[index].s_z <= 1) {
			continue;
		}
		cur = start_index[find_nonnegative(1, bricks_2322[index].s_z - 1)];
		if (cur == -1) {
			printf("Did something");
		}
		supported = check_support(index, start_index[bricks_2322[index].s_z - 2], cur);
		cur = index;
		while (supported == 0) {
			bricks_2322[cur].s_z--;
			bricks_2322[cur].e_z--;
			cur = update_order(cur);
			if (bricks_2322[cur].s_z <= 1) {
				supported = 1;
			} else {
				supported = check_support(cur, start_index[bricks_2322[cur].s_z - 2], start_index[find_nonnegative(1, bricks_2322[cur].s_z - 1)]);
			}
		}
	}
	for (index = 1; index < bricks_2322_size; index++) {
		if (bricks_2322[index - 1].e_z > bricks_2322[index].e_z) {
			printf("ERROR sift_down: ordering is off: index: %d\n", index);
		}

	}
}

void populate_support() {
	int16_t index = 0;
	int16_t index_i = 0;

	for (index = 0; index < bricks_2322_size; index++) {
		if (bricks_2322[index].s_z == 1) {
			continue;
		}
		for (index_i = 0; index_i < index; index_i++) {
			if (bricks_2322[index_i].e_z == bricks_2322[index].s_z - 1 && check_overlap(&bricks_2322[index_i], &bricks_2322[index]) == 1) {
				bricks_2322[index_i].supporting[bricks_2322[index_i].num_supporting] = &bricks_2322[index];
				bricks_2322[index_i].num_supporting++;
				bricks_2322[index].supporters[bricks_2322[index].num_supporters] = &bricks_2322[index_i];
				bricks_2322[index].num_supporters++;
			}
		}
	}
}

void sift_down_p2() {
	int16_t index = 0;
	int16_t cur = 0;
	char supported = 0;
	char dropped = 0;
	for (index = 0; index < bricks_2322_size_p2; index++) {
		dropped = 0;
		if (bricks_2322_p2[index].s_z <= 1) {
			continue;
		}
		cur = start_index_p2[find_nonnegative(2, bricks_2322_p2[index].s_z - 1)];
		if (cur == -1) {
			printf("Did something");
		}
		supported = check_support_2(index, start_index_p2[bricks_2322_p2[index].s_z - 2], cur);
		cur = index;
		while (supported == 0) {
			if (dropped == 0) {
				fall_count++;
				dropped = 1;
			}
			bricks_2322_p2[cur].s_z--;
			bricks_2322_p2[cur].e_z--;
			cur = update_order_2(cur);
			if (bricks_2322_p2[cur].s_z <= 1) {
				supported = 1;
			} else {
				supported = check_support_2(cur, start_index_p2[bricks_2322_p2[cur].s_z - 2], start_index_p2[find_nonnegative(2, bricks_2322_p2[cur].s_z - 1)]);
			}
		}
	}
	for (index = 1; index < bricks_2322_size_p2; index++) {
		if (bricks_2322_p2[index - 1].e_z > bricks_2322_p2[index].e_z) {
			printf("ERROR sift_down: ordering is off: index: %d\n", index);
		}

	}
}
int16_t find_dis_count() {
	int16_t count = 0;
	int16_t index = 0;
	int16_t index_i = 0;
	char good = 0;

	for (index = 0; index < bricks_2322_size; index++) {
		if (bricks_2322[index].supporting == 0) {
			count++;
			bricks_2322[index].safe = 1;
			continue;
		}
		good = 0;
		index_i = 0;
		while (good == 0 && index_i < bricks_2322[index].num_supporting) {
			if (bricks_2322[index].supporting[index_i]->num_supporters > 1) {
				good = 0;
			} else {
				good = 1;
			}
			index_i++;
		}
		if (good == 0) {
			count++;
			bricks_2322[index].safe = 1;
		} else {
			bricks_2322[index].safe = 0;
		}
	}
	return count;
}

void find_fall_count() {
	int16_t index = 0;
	int16_t index_i = 0;
	char sub = 0;
	bricks_2322_size_p2 = bricks_2322_size - 1;
	for (index = 0; index < bricks_2322_size; index++) {
		if (bricks_2322[index].num_supporting == 0 || bricks_2322[index].safe == 1) {
			continue;
		}
		sub = 0;
		for (index_i = 0; index_i < bricks_2322_size; index_i++) {
			
			if (index_i != index) {
				//copy!
				bricks_2322_p2[index_i - sub].s_x = bricks_2322[index_i].s_x;
				bricks_2322_p2[index_i - sub].s_y = bricks_2322[index_i].s_y;
				bricks_2322_p2[index_i - sub].s_z = bricks_2322[index_i].s_z;
				bricks_2322_p2[index_i - sub].e_x = bricks_2322[index_i].e_x;
				bricks_2322_p2[index_i - sub].e_y = bricks_2322[index_i].e_y;
				bricks_2322_p2[index_i - sub].e_z = bricks_2322[index_i].e_z;
				bricks_2322_p2[index_i - sub].num_supporters = 0;
				bricks_2322_p2[index_i - sub].num_supporting = 0;
			} else {
				sub = 1;
			}
		}
		for (index_i = 0; index_i < MAX_Z; index_i++) {
			start_index_p2[index_i] = -1;
		}
		//qsort_s(bricks_2322_p2, bricks_2322_size_p2, sizeof(struct brick_2322), bricks_2322_comp, NULL);

		for (index_i = 0; index_i < bricks_2322_size_p2; index_i++) {
			if (start_index_p2[bricks_2322_p2[index_i].e_z - 1] == -1) {
				start_index_p2[bricks_2322_p2[index_i].e_z - 1] = index_i;
			}
		}
		sift_down_p2();
	}
}

char check_support(int16_t brick, int16_t start, int16_t end) {
	int16_t index = 0;
	if (start == -1) {
		return 0;
	}
	if (bricks_2322[brick].s_z == 1) {
		return 1;
	}
	if (end == -1) {
		end = start + 1;
	}
	for (index = start; index < end; index++) {
		if (bricks_2322[index].e_z == bricks_2322[brick].s_z - 1) {
			if (check_overlap(&bricks_2322[index], &bricks_2322[brick]) == 1) {
				return 1;
			}
		} else {
			printf("Wrong block check\n");
		}
	}
	return 0;
}

//assume brick1 is below brick2 and brick1 e_z is 1 lower than brick1 s_x
char check_overlap(struct brick_2322* brick1, struct brick_2322* brick2) {
	if (brick1->e_z + 1 != brick2->s_z) {
		printf("Error: bricks aren't touching along z axis\n");
	}
	if (brick1->s_x <= brick2->e_x && brick1->e_x >= brick2->s_x && brick1->s_y <= brick2->e_y && brick1->e_y >= brick2->s_y) {
		return 1;
	}

	return 0;
}

int16_t update_order(int16_t brick) {
	int16_t index = brick - 1;
	int16_t index_b = brick;
	struct brick_2322 temp;
	if (index_b == start_index[bricks_2322[index_b].e_z]) {
		if (bricks_2322[index_b].e_z + 1 != bricks_2322[index_b + 1].e_z) {
			start_index[bricks_2322[index_b].e_z] = -1;
		} else {
			start_index[bricks_2322[index_b].e_z]++;
		}
		if (index_b >= 0 && start_index[bricks_2322[index_b].e_z - 1] == -1) {
			start_index[bricks_2322[index_b].e_z - 1] = index_b;
		}
		goto finish;
	}
	while (index >= 0 && bricks_2322[index_b].e_z < bricks_2322[index].e_z) {
		//swap
		temp.s_x = bricks_2322[index_b].s_x;
		temp.s_y = bricks_2322[index_b].s_y;
		temp.s_z = bricks_2322[index_b].s_z;
		temp.e_x = bricks_2322[index_b].e_x;
		temp.e_y = bricks_2322[index_b].e_y;
		temp.e_z = bricks_2322[index_b].e_z;
		//
		bricks_2322[index_b].s_x = bricks_2322[index].s_x;
		bricks_2322[index_b].s_y = bricks_2322[index].s_y;
		bricks_2322[index_b].s_z = bricks_2322[index].s_z;
		bricks_2322[index_b].e_x = bricks_2322[index].e_x;
		bricks_2322[index_b].e_y = bricks_2322[index].e_y;
		bricks_2322[index_b].e_z = bricks_2322[index].e_z;
		//
		bricks_2322[index].s_x = temp.s_x;
		bricks_2322[index].s_y = temp.s_y;
		bricks_2322[index].s_z = temp.s_z;
		bricks_2322[index].e_x = temp.e_x;
		bricks_2322[index].e_y = temp.e_y;
		bricks_2322[index].e_z = temp.e_z;
		index--;
		index_b--;
	}
	if (index_b >= 0 && start_index[bricks_2322[index_b].e_z - 1] == -1) {
		start_index[bricks_2322[index_b].e_z - 1] = index_b;
	}
	if (index_b > 0) {
		start_index[bricks_2322[index_b].e_z] = index_b + 1;
	} else if(index_b < 0) {
		printf("Update order index_b became negative somehow: start brick: %d\n", brick);
		exit(-2);
	}

finish:
	//temp.s_z = 0;
	//temp.s_x = 1;
	//while (temp.s_x < MAX_Z && start_index[temp.s_x] == -1) {
	//	temp.s_x++;
	//}
	//for (index = 0; index < bricks_2322_size; index++) {
	//	if (index == start_index[temp.s_x]) {
	//		temp.s_z = temp.s_x;
	//		temp.s_x++;
	//		while (temp.s_x < MAX_Z && start_index[temp.s_x] == -1) {
	//			temp.s_x++;
	//		}
	//		if (temp.s_x >= MAX_Z) {
	//			temp.s_x = MAX_Z - 1;
	//		}
	//	}
	//	if (bricks_2322[index].e_z - 1 != temp.s_z) {
	//		printf("Indexing error for brick index_b: %d\n", index_b);
	//	}
	//	
	//	if (index == 0) {
	//		continue;
	//	}
	//	if (bricks_2322[index - 1].e_z > bricks_2322[index].e_z) {
	//		printf("ERROR: ordering is off: index: %d\n", index);
	//	}
	//	
	//}
	
	return index_b;
}

char check_support_2(int16_t brick, int16_t start, int16_t end) {
	int16_t index = 0;
	if (start == -1) {
		return 0;
	}
	if (bricks_2322_p2[brick].s_z == 1) {
		return 1;
	}
	if (end == -1) {
		end = start + 1;
	}
	for (index = start; index < end; index++) {
		if (bricks_2322_p2[index].e_z == bricks_2322_p2[brick].s_z - 1) {
			if (check_overlap(&bricks_2322_p2[index], &bricks_2322_p2[brick]) == 1) {
				return 1;
			}
		} else {
			printf("Wrong block check support 2\n");
		}
	}
	return 0;
}

int16_t update_order_2(int16_t brick) {
	int16_t index = brick - 1;
	int16_t index_b = brick;
	struct brick_2322 temp;
	if (index_b == start_index_p2[bricks_2322_p2[index_b].e_z]) {
		if (bricks_2322_p2[index_b].e_z + 1 != bricks_2322_p2[index_b + 1].e_z) {
			start_index_p2[bricks_2322_p2[index_b].e_z] = -1;
		} else {
			start_index_p2[bricks_2322_p2[index_b].e_z]++;
		}
		if (index_b >= 0 && start_index_p2[bricks_2322_p2[index_b].e_z - 1] == -1) {
			start_index_p2[bricks_2322_p2[index_b].e_z - 1] = index_b;
		}
		return index_b;
	}
	while (index >= 0 && bricks_2322_p2[index_b].e_z < bricks_2322_p2[index].e_z) {
		//swap
		temp.s_x = bricks_2322_p2[index_b].s_x;
		temp.s_y = bricks_2322_p2[index_b].s_y;
		temp.s_z = bricks_2322_p2[index_b].s_z;
		temp.e_x = bricks_2322_p2[index_b].e_x;
		temp.e_y = bricks_2322_p2[index_b].e_y;
		temp.e_z = bricks_2322_p2[index_b].e_z;
		//
		bricks_2322_p2[index_b].s_x = bricks_2322_p2[index].s_x;
		bricks_2322_p2[index_b].s_y = bricks_2322_p2[index].s_y;
		bricks_2322_p2[index_b].s_z = bricks_2322_p2[index].s_z;
		bricks_2322_p2[index_b].e_x = bricks_2322_p2[index].e_x;
		bricks_2322_p2[index_b].e_y = bricks_2322_p2[index].e_y;
		bricks_2322_p2[index_b].e_z = bricks_2322_p2[index].e_z;
		//
		bricks_2322_p2[index].s_x = temp.s_x;
		bricks_2322_p2[index].s_y = temp.s_y;
		bricks_2322_p2[index].s_z = temp.s_z;
		bricks_2322_p2[index].e_x = temp.e_x;
		bricks_2322_p2[index].e_y = temp.e_y;
		bricks_2322_p2[index].e_z = temp.e_z;
		index--;
		index_b--;
	}
	if (index_b >= 0 && start_index_p2[bricks_2322_p2[index_b].e_z - 1] == -1) {
		start_index_p2[bricks_2322_p2[index_b].e_z - 1] = index_b;
	}
	if (index_b > 0) {
		start_index_p2[bricks_2322_p2[index_b].e_z] = index_b + 1;
	} else if (index_b < 0) {
		printf("Update order p2 index_b became negative somehow: start brick: %d\n", brick);
		exit(-2);
	}

	return index_b;
}

int16_t find_nonnegative(char part, int16_t start) {
	if (part == 1) {
		while (start < MAX_Z && start_index[start] == -1) {
			start++;
		}
		if (start == MAX_Z) {
			start = bricks_2322_size - 1;
		}
	} else {
		while (start >= 0 && start < MAX_Z && start_index_p2[start] == -1) {
			start++;
		}
		if (start == MAX_Z) {
			start = bricks_2322_size_p2 - 1;
		}
	}

	return start;
}

int bricks_2322_comp(void* context, const void* item1, const void* item2) {
	struct brick_2322* i1 = (struct brick_2322*)item1;
	struct brick_2322* i2 = (struct brick_2322*)item2;

	//z
	if (i1->e_z < i2->e_z) {
		return -1;
	}
	if (i1->e_z > i2->e_z) {
		return 1;
	}
	if (i1->s_z < i2->s_z) {
		return -1;
	}
	if (i1->s_z > i2->s_z) {
		return 1;
	}
	//x
	if (i1->e_x < i2->e_x) {
		return -1;
	}
	if (i1->e_x > i2->e_x) {
		return 1;
	}
	if (i1->s_x < i2->s_x) {
		return -1;
	}
	if (i1->s_x > i2->s_x) {
		return 1;
	}
	//y
	if (i1->e_y < i2->e_y) {
		return -1;
	}
	if (i1->e_y > i2->e_y) {
		return 1;
	}
	if (i1->s_y < i2->s_y) {
		return -1;
	}
	if (i1->s_z > i2->s_y) {
		return 1;
	}
	return 0;
}