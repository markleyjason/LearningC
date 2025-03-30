#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define MAX_SPOTS 131 * 3 * 3
#define MAX_LINE 133 * 3 * 3
#define MAX_STEPS 458

enum plot_type_2321 {
	start,
	plot,
	rock
};

struct plot_2321 {
	enum plot_type_2321 type;
	int16_t row;
	int16_t col;
	int64_t visited;
	char count;
};

struct queue_message {
	int16_t row;
	int16_t col;
	int64_t steps;
};

struct node {
	struct queue_message data;
	struct node* next;
};

struct plot_2321 grid_2321[MAX_SPOTS][MAX_SPOTS] = { '\0' };
char line[MAX_LINE] = { '\0' };
struct node* queue_head;
struct node* queue_tail;
int64_t size;

void take_steps(int16_t row, int16_t col, int64_t steps);
void print_grid(int64_t size, FILE* wptr);
static void append_queue(int16_t row, int16_t col, int64_t steps);

int adv2023p21() {
//int main() {
	clock_t start_c, end;
	double dif;
	FILE* fptr;
	FILE* rptr;
	errno_t error;
	int16_t index = 0;
	int16_t index_r = 0;
	int16_t start_col = 0;
	int16_t start_row = 0;
	uint64_t count = 0;
	char working = '\0';
	struct node* temp_n;


	error = fopen_s(&fptr, "input2023p21.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");
	if (error) {
		printf("Failed to open input file\n");
		return -1;
	}

	//error = fopen_s(&rptr, "testing_input.txt", "w");
	/*error = fopen_s(&rptr, "output.txt", "w");
	if (error) {
		printf("Failed to open output file\n");
		return -1;
	}*/
	
	while (fgets(line, MAX_LINE, fptr) != NULL) {
		index_r = 0;
		if (index >= MAX_SPOTS) {
			printf("Input too large\n");
			return -1;
		}
		while (index_r < MAX_SPOTS && index_r < MAX_LINE && line[index_r] != '\n' && line[index_r] != '\0') {
			working = line[index_r];
			grid_2321[index][index_r].row = index;
			grid_2321[index][index_r].col = index_r;
			grid_2321[index][index_r].visited = -1;
			switch (working) {
			case '.':
				grid_2321[index][index_r].type = plot;
				break;
			case '#':
				grid_2321[index][index_r].type = rock;
				break;
			case 'S':
				grid_2321[index][index_r].type = start;
				start_row = index;
				start_col = index_r;
				break;
			default:
				printf("Error expect a type found: %c, index: %lu col: %lu\n", working, index, index_r);
				return -2;
			}
			index_r++;
		}
		index++;
	}
	size = index;
	fclose(fptr);

	/*for (start_row = 0; start_row < 3; start_row++) {
		for (index = 0; index < size; index++) {
			for (start_col = 0; start_col < 3; start_col++) {
				for (index_r = 0; index_r < size; index_r++) {
					switch (grid_2321[index][index_r].type) {
					case start:
						if (start_row == start_col && start_row == 1) {
							fprintf(rptr, "S");
						} else {
							fprintf(rptr, ".");
						}
						break;
					case rock:
						fprintf(rptr, "#");
						break;
					case plot:
						fprintf(rptr, ".");
					}
				}
			}
			fprintf(rptr, "\n");
		}
	}
	fclose(rptr);
	return 0;*/
	//print_grid(size);
	start_c = clock();

	take_steps(start_row, start_col, MAX_STEPS);
	while (queue_head != NULL) {
		temp_n = queue_head;
		queue_head = queue_head->next;
		take_steps(temp_n->data.row, temp_n->data.col, temp_n->data.steps);
		free(temp_n);
	}

	//print_grid(size, rptr);
	
	for (index_r = 0; index_r < size; index_r++) {
		for (index = 0; index < size; index++) {
			if (grid_2321[index_r][index].count == 1) {
				count++;
			}
			grid_2321[index_r][index].visited = -1;
		}
	}
	printf("Part 1 count: %llu\n", count);

	end = clock();
	dif = (double)(end - start_c) * 1000 / CLOCKS_PER_SEC;
	printf("Time spent: %f", dif);

	return 0;
}

void take_steps(int16_t row, int16_t col, int64_t steps) {
	//printf("%d\n", steps);
	if (steps % 2 == 0) {
		grid_2321[row][col].count = 1;
	}
	if (steps == 0) {
		return;
	}
	if (row - 1 >= 0 && grid_2321[row - 1][col].type != rock && grid_2321[row - 1][col].visited == -1) {
		grid_2321[row - 1][col].visited = steps - 1;
		append_queue(row - 1, col, steps - 1);
	}
	if (row + 1 < size && grid_2321[row + 1][col].type != rock && grid_2321[row + 1][col].visited == -1) {
		grid_2321[row + 1][col].visited = steps;
		append_queue(row + 1, col, steps - 1);
	}
	if (col - 1 >= 0 && grid_2321[row][col - 1].type != rock && grid_2321[row][col - 1].visited == -1) {
		grid_2321[row][col - 1].visited = steps - 1;
		append_queue(row, col - 1, steps - 1);
	}
	if (col + 1 >= 0 && grid_2321[row][col + 1].type != rock && grid_2321[row][col + 1].visited == -1) {
		grid_2321[row][col  + 1].visited = steps - 1;
		append_queue(row, col + 1, steps - 1);
	}
}

void print_grid(int64_t size, FILE* wptr) {
	int16_t row, col;

	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			if(grid_2321[row][col].count == 1) {
				fprintf(wptr, "O");
			} else if (grid_2321[row][col].visited == 1) {
				fprintf(wptr, "V");
			} else {
				switch (grid_2321[row][col].type) {
				case plot:
					fprintf(wptr, ".");
					break;
				case start:
					fprintf(wptr, "S");
					break;
				case rock:
					fprintf(wptr, "#");
					break;
				}
			}
		}
		fprintf(wptr, "\n");
	}
	fprintf(wptr, "\n");
}

static void append_queue(int16_t row, int16_t col, int64_t steps) {
	struct node* temp = malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("ERROR making new node for queue\n");
		exit(-3);
	}
	temp->data.steps = steps;
	temp->data.row = row;
	temp->data.col = col;
	if (queue_head == NULL) {
		queue_head = temp;
		queue_tail = queue_head;
		queue_head->next = NULL;
	} else {
		queue_tail->next = temp;
		queue_tail = temp;
	}
	queue_tail->next = NULL;
}