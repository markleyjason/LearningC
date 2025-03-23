#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helper.h"
#define MAX_LEN 10
#define MAX_PRESENTS 40

struct grouping_1524 {
	int16_t group1[MAX_PRESENTS];
	int16_t group2[MAX_PRESENTS];
	int16_t group3[MAX_PRESENTS];
	int16_t g1s;
	int16_t g2s;
	int16_t g3s;
	int64_t g1ge;
};

int16_t weights[MAX_PRESENTS];
int16_t goal_weight = 0;

struct grouping_1524 best_ans = { .g1ge = INT16_MAX, .g1s = INT16_MAX, .g2s = 0, .g3s = 0, .group1 = 0, .group2 = 0, .group3 = 0 };

int64_t sqe_1524(const int16_t* arr, const size_t size);

void fill_option_rec(int16_t* arr, size_t len, int16_t goal, size_t start, int16_t* test, size_t test_logic, int groups);

char confirm_option_rec(int16_t* arr, size_t len, int16_t* first_arr, size_t size, int groups_left);

char contains_rec(int16_t value, int16_t* arr, size_t size);

int mainp2015p14() {
	FILE* fptr;
	errno_t error;
	char line[MAX_LEN] = "\0";
	int16_t index = 0;
	int16_t len = 0;
	int16_t copy_i = 0;
	int16_t steps = 0;
	int16_t test[MAX_PRESENTS] = { 0 };

	error = fopen_s(&fptr, "input15p24.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");
	if (error) {
		printf("Failed to open file\n");
		return -1;
	}

	while (fgets(line, MAX_LEN, fptr) != NULL) {
		weights[len] = stoai(line);
		goal_weight += weights[len];
		len++;
	}
	fclose(fptr);
	goal_weight /= 3;
	
	fill_option_rec(weights, len, goal_weight, len - 1, test, 0, 3);	
	printf("Part 1: %llu\n", sqe_1524(&best_ans.group1, best_ans.g1s));

	goal_weight *= 3;
	goal_weight /= 4;

	fill_option_rec(weights, len, goal_weight, len - 1, test, 0, 4);
	printf("Part 1: %llu\n", sqe_1524(&best_ans.group1, best_ans.g1s));

	return 0;
}

int64_t sqe_1524(const int16_t* arr, const size_t size) {
	int64_t ans = 1;
	int16_t index = 0;

	for (index = 0; index < size; index++) {
		ans *= arr[index];
	}

	return ans;
}

void fill_option_rec(int16_t* arr, size_t len, int16_t goal, size_t start, int16_t* test, size_t test_logic, int groups) {
	int16_t index;
	int16_t copy;

	if (start == 0) {
		if (arr[start] == goal) {
			test[test_logic] = arr[start];
			test_logic++;
			if (best_ans.g1s > test_logic || (best_ans.g1s == test_logic && best_ans.g1ge > sqe_1524(test, test_logic))) {
				if (confirm_option_rec(arr, len, test, test_logic, groups - 1) != 0) {
					return;
				}
				for (copy = 0; copy < test_logic; copy++) {
					best_ans.group1[copy] = test[copy];
				}
				best_ans.g1s = test_logic;
				best_ans.g1ge = sqe_1524(best_ans.group1, best_ans.g1s);
			}
		}
	} else {
		for (index = start; index >= 0; index--) {
			if (arr[index] == goal) {
				test[test_logic] = arr[index];
				test_logic++;
				
				if (best_ans.g1s > test_logic || (best_ans.g1s == test_logic && best_ans.g1ge > sqe_1524(test, test_logic))) {
					if (confirm_option_rec(arr, len, test, test_logic, groups - 1) != 0) {
						continue;
					}
					for (copy = 0; copy < test_logic; copy++) {
						best_ans.group1[copy] = test[copy];
					}
					best_ans.g1s = test_logic;
					best_ans.g1ge = sqe_1524(best_ans.group1, best_ans.g1s);
				}
				test_logic--;
			}
			if (arr[index] < goal) {
				test[test_logic] = arr[index];
				fill_option_rec(arr, len, goal - arr[index], index - 1, test, test_logic + 1, groups);
			}
		}
	}
}

char confirm_option_rec(int16_t* arr, size_t len, int16_t* first_arr, size_t size, int group_left) {
	int16_t index = 0;
	int16_t curr = 0;
	int16_t subset[MAX_PRESENTS];
	int16_t copy[MAX_PRESENTS];
	int16_t copy_len = 0;
	int16_t sum = 0;

	for (index = 0; index < len; index++) {
		if (contains_rec(arr[index], first_arr, size) == 0) {
			subset[curr] = arr[index];
			curr++;
			sum += arr[index];
		}
	}

	if (sum != goal_weight * group_left) {
		return 1;
	} else {
		return 0;
	}
	return index;
}

char contains_rec(int16_t value, int16_t* arr, size_t size) {
	int16_t index;

	for (index = 0; index < size; index++) {
		if (arr[index] == value) {
			return 1;
		}
	}
	return 0;
}