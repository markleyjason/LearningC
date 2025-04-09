#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include "helper.h"

#define BUFFER 75
#define MAX_SIZE 300
#define DEBUG 0

static struct point_3d {
	double x;
	double y;
	double z;
};

static struct point_slope {
	int64_t x;
	int64_t y;
	int64_t z;
	int64_t v_x;
	int64_t v_y;
	int64_t v_z;
};

static struct point_slope points[MAX_SIZE];
static int16_t num_points;

//static int matrix[6][6];
static int64_t answer[6];
static double t_ans[6];

static double testing[6][6];

static struct point_3d check_intersect_2d(int16_t first, int16_t second);
static char slope_3d(struct point_slope x, struct point_slope y);

static void find_inverse(int64_t** matrix, double m_minor[6][6]);
static int64_t find_minor(size_t size, size_t row, size_t col, int64_t** the_matrix);
static int64_t find_det(size_t size, int64_t** the_matrix);

static void gaussianElimination(double** matrix, size_t rows, size_t col) {
	for (int i = 0; i < rows; i++) {
		// Partial Pivoting
		for (int k = i + 1; k < rows; k++) {
			if (fabs(matrix[i][i]) < fabs(matrix[k][i])) {
				for (int j = 0; j <= rows; j++) {
					double temp = matrix[i][j];
					matrix[i][j] = matrix[k][j];
					matrix[k][j] = temp;
				}
			}
		}

		// Forward Elimination
		for (int k = i + 1; k < rows; k++) {
			double term = matrix[k][i] / matrix[i][i];
			for (int j = 0; j <= rows; j++) {
				matrix[k][j] -= term * matrix[i][j];
			}
		}
	}

	// Back Substitution
	double solution[6] = { 0 };
	for (int i = rows - 1; i >= 0; i--) {
		solution[i] = matrix[i][rows];
		for (int j = i + 1; j < rows; j++) {
			solution[i] -= matrix[i][j] * solution[j];
		}
		solution[i] /= matrix[i][i];
	}

	// Print the solution
	printf("Solution:\n");
	for (int i = 0; i < rows; i++) {
		printf("x%d = %f\n", i + 1, solution[i]);
	}
	printf("Part 2?: %f\n", solution[0] + solution[1] + solution[2]);
}

int advcal2023p24() {
//int main() {
	FILE* fptr;
	errno_t error;
	char line[BUFFER] = { '\0' };
	char temp_num[BUFFER] = { '\0' };
	int32_t index = 0;
	int32_t index_i = 0;
	struct point_3d incoming = { 0 };
	int32_t count = 0;
	//int64_t test_min = 7;
	int64_t test_min = 200000000000000;
	//int64_t test_max = 27;
	int64_t test_max = 400000000000000;
	double inverse[6][6];
	double det = 0;
	double** matrix = malloc(6 * sizeof(double*));
	if (matrix == NULL) {
		printf("Ran out of memory before we could begin\n");
		exit(-6);
	}
	for (index = 0; index < 6; index++) {
		matrix[index] = malloc(7 * sizeof(double));
		if (matrix[index] == NULL) {
			printf("Ran out of memory before we could begin. %d\n", index);
			exit(-6);
		}
	}

	error = fopen_s(&fptr, "input2023p24.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Error opening input file\n");
		return -1;
	}

	while (fgets(line, BUFFER, fptr) != NULL && num_points < MAX_SIZE) {
		index = 0;
		index_i = 0;
		while (line[index] != ',') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].x = stoai64(temp_num);

		index += 2;

		index_i = 0;
		while (line[index] != ',') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].y = stoai64(temp_num);

		index += 2;

		index_i = 0;
		while (line[index] != ' ') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].z = stoai64(temp_num);

		index += 3;

		index_i = 0;
		while (line[index] != ',') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].v_x = stoai64(temp_num);

		index += 2;

		index_i = 0;
		while (line[index] != ',') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].v_y = stoai64(temp_num);

		index += 2;

		index_i = 0;
		while (line[index] != '\n' && line[index] != '\0') {
			temp_num[index_i] = line[index];
			index_i++;
			index++;
		}
		temp_num[index_i] = '\0';
		points[num_points].v_z = stoai64(temp_num);

		num_points++;
	}
	fclose(fptr);

	for (index = 0; index < num_points - 1; index++) {
		for (index_i = index + 1; index_i < num_points; index_i++) {
			//assume parallel will never intersect (would be weird if they fly along the same path)

			if (slope_3d(points[index], points[index_i])) {
				printf("Parallel: %d, %d\n", index, index_i);
				continue;
			}
			incoming = check_intersect_2d(index, index_i);
			if (incoming.z == 0 && incoming.x >= test_min && incoming.x <= test_max && incoming.y >= test_min && incoming.y <= test_max) {
				count++;
			}
		}
	}
	printf("Part 1: %d\n", count);

	matrix[0][0] = points[0].v_y - points[1].v_y;
	matrix[0][1] = points[1].v_x - points[0].v_x;
	matrix[0][2] = 0;
	matrix[0][3] = points[1].y - points[0].y;
	matrix[0][4] = points[0].x - points[1].x;
	matrix[0][5] = 0;
	matrix[1][0] = points[0].v_y - points[2].v_y;
	matrix[1][1] = points[2].v_x - points[0].v_x;
	matrix[1][2] = 0;
	matrix[1][3] = points[2].y - points[0].y;
	matrix[1][4] = points[0].x - points[2].x;
	matrix[1][5] = 0;
	matrix[2][0] = points[1].v_z - points[0].v_z;
	matrix[2][1] = 0;
	matrix[2][2] = points[0].v_x - points[1].v_x;
	matrix[2][3] = points[0].z - points[1].z;
	matrix[2][4] = 0;
	matrix[2][5] = points[1].x - points[0].x;
	matrix[3][0] = points[2].v_z - points[0].v_z;
	matrix[3][1] = 0;
	matrix[3][2] = points[0].v_x - points[2].v_x;
	matrix[3][3] = points[0].z - points[2].z;
	matrix[3][4] = 0;
	matrix[3][5] = points[2].x - points[0].x;
	matrix[4][0] = 0;
	matrix[4][1] = points[0].v_z - points[1].v_z;
	matrix[4][2] = points[1].v_y - points[0].v_y;
	matrix[4][3] = 0;
	matrix[4][4] = points[1].z - points[0].z;
	matrix[4][5] = points[0].y - points[1].y;
	matrix[5][0] = 0;
	matrix[5][1] = points[0].v_z - points[2].v_z;
	matrix[5][2] = points[2].v_y - points[0].v_y;
	matrix[5][3] = 0;
	matrix[5][4] = points[2].z - points[0].z;
	matrix[5][5] = points[0].y - points[2].y;
	matrix[0][6] = (points[1].y * points[1].v_x - points[1].x * points[1].v_y) - (points[0].y * points[0].v_x - points[0].x * points[0].v_y);
	matrix[1][6] = (points[2].y * points[2].v_x - points[2].x * points[2].v_y) - (points[0].y * points[0].v_x - points[0].x * points[0].v_y);
	matrix[2][6] = (points[1].x * points[1].v_z - points[1].z * points[1].v_x) - (points[0].x * points[0].v_z - points[0].z * points[0].v_x);
	matrix[3][6] = (points[2].x * points[2].v_z - points[2].z * points[2].v_x) - (points[0].x * points[0].v_z - points[0].z * points[0].v_x);
	matrix[4][6] = (points[1].z * points[1].v_y - points[1].y * points[1].v_z) - (points[0].z * points[0].v_y - points[0].y * points[0].v_z);
	matrix[5][6] = (points[2].z * points[2].v_y - points[2].y * points[2].v_z) - (points[0].z * points[0].v_y - points[0].y * points[0].v_z);

	printf("\n");
	for (index = 0; index < 6; index++) {
		for (index_i = 0; index_i < 7; index_i++) {
			printf("%.f ", matrix[index][index_i]);
		}
		printf("\n");
	}
	printf("\n");
	gaussianElimination(matrix, 6, 7);

	printf("\n");

	for (index = 0; index < 6; index++) {
		free(matrix[index]);

	}
	free(matrix);
	return 0;
}


static struct point_3d check_intersect_2d(int16_t first, int16_t second) {
	struct point_3d inter = { 0 };
	struct point_slope first_eq = points[first];
	struct point_slope second_eq = points[second];
	double shift_s = 0;
	double slope_s = 0;
	double time_t = 0;
	double shift_t = 0;
	double slope_t = 0;
	double time_s = 0;

	if (DEBUG == 1) {
		printf("Equations: %d, %d:\n", first, second);
		printf("\tx=%" PRId64 "t+%" PRId64 "\n", first_eq.v_x, first_eq.x);
		printf("\ty=%" PRId64 "t+%" PRId64 "\nSecond equation:\n", first_eq.v_y, first_eq.y);
		printf("\tx=%" PRId64 "t+%" PRId64 "\n", second_eq.v_x, second_eq.x);
		printf("\ty=%" PRId64 "t+%" PRId64 "\n", second_eq.v_y, second_eq.y);
	}

	//solve x sides
	shift_s = (first_eq.x - second_eq.x) / ((double)second_eq.v_x);
	slope_s = first_eq.v_x / ((double)second_eq.v_x);
	if (DEBUG == 1) {
		printf("s=%.3ft+%.3f\n", slope_s, shift_s);
		printf("%" PRId64 "t+%" PRId64 "1=%" PRId64 "(%.3ft+%.3f)+%" PRId64 "\n", first_eq.v_y, first_eq.y, second_eq.v_y, slope_s, shift_s, second_eq.y);
	}
	slope_t = slope_s * second_eq.v_y;
	shift_t = shift_s * second_eq.v_y + second_eq.y;
	if (DEBUG == 1) {
		printf("%" PRId64 "t+%" PRId64 "1=%.3ft+%.3f\n", first_eq.v_y, first_eq.y, slope_t, shift_t);
	}
	shift_t = shift_t - first_eq.y;
	slope_t = first_eq.v_y - slope_t;
	time_t = shift_t / slope_t;
	if (DEBUG == 1) {
		printf("%.3ft=%.3f\n", slope_t, shift_t);
		printf("Time t=%.3f\n", time_t);
	}
	time_s = slope_s * time_t + shift_s;
	if (DEBUG == 1) {
		printf("Time s=%.3f\n", time_s);
	}

	if (time_t >= 0 && time_s >= 0) {
		inter.x = first_eq.v_x * time_t + first_eq.x;
		inter.y = first_eq.v_y * time_t + first_eq.y;
		inter.z = 0;
	} else {
		inter.z = -1;
	}

	return inter;
}

static char slope_3d(struct point_slope x, struct point_slope y) {
	int64_t t_x = x.v_y * y.v_z - x.v_z * y.v_y;
	int64_t t_y = x.v_z * y.v_x - x.v_x * y.v_z;
	int64_t t_z = x.v_x * y.v_y - x.v_y * y.v_x;
	return (t_x == 0 && t_y == 0 && t_z == 0);
}

static void find_inverse(int64_t** matrix, double m_minor[6][6]) {
	int16_t index = 0;
	int16_t index_i = 0;
	char sign = 1;
	double det = find_det(6, matrix);

	printf("\n");
	for (index = 0; index < 6; index++) {
		for (index_i = 0; index_i < 6; index_i++) {
			if ((index + index_i) % 2 == 0) {
				sign = 1;
			} else {
				sign = -1;
			}
			m_minor[index_i][index] = sign * find_minor(6, index, index_i, matrix) / det;
		}
	}
}

static int64_t find_minor(size_t size, size_t row, size_t col, int64_t** the_matrix) {
	int64_t the_m = 0;
	size_t index = 0;
	size_t index_i = 0;
	size_t new_size = size - 1;
	char sub_row = 0;
	char sub_col = 0;
	int64_t** temp = NULL;

	if (size < 2) {
		printf("HEY DUMBASS. HOW DO YOU GET A MATRIX SMALLER THAN 1?\n");
		exit(-6);
	}
	temp = malloc(new_size * sizeof(int64_t*));
	if (temp == NULL) {
		printf("Memory failure in matrix minor\n");
		exit(-7);
	}
	for (index = 0; index < new_size; index++) {
		temp[index] = malloc(new_size * sizeof(int64_t));
		if (temp[index] == NULL) {
			printf("Memory failure in matrix minor\n");
			exit(-7);
		}
	}
	sub_col = 0;
	sub_row = 0;
	for (index = 0; index < size; index++) {
		sub_col = 0;
		for (index_i = 0; index_i < size; index_i++) {
			if (row == index) {
				sub_row = 1;
				continue;
			}
			if (col == index_i) {
				sub_col = 1;
				continue;
			}
			temp[index - sub_row][index_i - sub_col] = the_matrix[index][index_i];
		}
	}
	the_m = find_det(new_size, temp);

	for (index = 0; index < new_size; index++) {
		free(temp[index]);
	}
	free(temp);
	return the_m;
}

static int64_t find_det(size_t size, int64_t** the_matrix) {
	int64_t ans = 0;
	size_t index = 0;
	int64_t sign = 1;
	int64_t temp = 0;

	if (DEBUG == 2 && size == 6) {
		for (index = 0; index < size; index++) {
			for (int in = 0; in < size; in++) {
				printf("%" PRId64 " ", the_matrix[index][in]);
			}
			printf("\n");
		}
		printf("\n");
	}

	if (size == 2) {
		ans = the_matrix[0][0] * the_matrix[1][1] - the_matrix[0][1] * the_matrix[1][0];
	} else {
		for (index = 0; index < size; index++) {
			if (index % 2 == 0) {
				sign = 1;
			} else {
				sign = -1;
			}
			temp = find_minor(size, 0, index, the_matrix);
			if ((the_matrix[0][index] >= 0 && temp >= 0) || (the_matrix[0][index] < 0 && temp < 0)) {
				temp *= the_matrix[0][index];
				if (temp < 0) {
					printf("OVERFLOW, number too big\n");
					exit(-7);
				}
			} else {
				temp *= the_matrix[0][index];
				if (temp > 0) {
					printf("UNDERFLOW, number too small\n");
					exit(-7);
				}
			}
			ans += sign * the_matrix[0][index] * find_minor(size, 0, index, the_matrix);
		}
	}

	return ans;
}