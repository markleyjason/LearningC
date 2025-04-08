#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER 150
#define MAX_SIZE 150
#define NODES 37

static enum type_2323 {
	n_slope,
	e_slope,
	s_slope,
	w_slope,
	standard,
	start,
	rock
};

static struct slope_grid_2323 {
	int16_t row;
	int16_t col;
	enum type_2323 slope;
	int32_t length;
};

static struct slope_queue_node {
	struct slope_grid_2323* data;
	int16_t i_row;
	int16_t i_col;
	struct slope_queue_node* next;
};

static struct slope_graph_node {
	char visited;
	int16_t weight;
	int16_t i_row;
	int16_t i_col;
	int16_t connection_weight[4];
	struct slope_graph_node* connections[4];
};

static struct slope_grid_2323 grid_2323[MAX_SIZE][MAX_SIZE];
static int16_t grid_size = 0;

static struct slope_queue_node* head;
static struct slope_queue_node* tail;

static struct slope_graph_node nodes[NODES];
static int16_t node_count = 0;

static void calculate_distance(int16_t end_r, int16_t end_c);

static void build_nodes(int16_t node);

static void build_path(int16_t start_node, int16_t end_node);

static int16_t find_node(int16_t row, int16_t col);
static struct slope_graph_node* move(enum type_2323 last_dir, int16_t i_row, int16_t i_col, int16_t* count, int16_t s_row, int16_t s_col);

static void append(int16_t n_row, int16_t n_col, int16_t c_row, int16_t c_col);
static struct slope_grid_2323* get_next();

int adv2023p23() {
//int main() {
	FILE* fptr;
	errno_t error;
	char line[BUFFER] = { '\0' };
	char started = 0;
	int16_t index_r = 0;
	int16_t index_c = 0;

	struct slope_grid_2323 temp;
	int16_t end_r = 0;
	int16_t end_c = 0;

	error = fopen_s(&fptr, "input2023p23.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Couldn't open file\n");
		return -1;
	}

	while (index_r < MAX_SIZE && fgets(line, BUFFER, fptr) != NULL) {
		index_c = 0;
		while (index_c < BUFFER && line[index_c] != '\n' && line[index_c] != '\0') {
			grid_2323[index_r][index_c].length = INT32_MIN;
			grid_2323[index_r][index_c].row = index_r;
			grid_2323[index_r][index_c].col = index_c;
			switch (line[index_c]) {
			case '.':
				if (started == 0) {
					grid_2323[index_r][index_c].slope = start;
					grid_2323[index_r][index_c].length = 0;
					started = 1;
					append(index_r, index_c, -1, -1);
					nodes[node_count].i_col = index_c;
					nodes[node_count].i_row = index_r;
					nodes[node_count].visited = 0;
					nodes[node_count].weight = 0;
					nodes[node_count].connection_weight[n_slope] = 0;
					nodes[node_count].connection_weight[e_slope] = -1;
					nodes[node_count].connection_weight[w_slope] = -1;
					nodes[node_count].connection_weight[s_slope] = -1;
					node_count++;
				} else {
					grid_2323[index_r][index_c].slope = standard;
				}
				break;
			case '#':
				grid_2323[index_r][index_c].slope = rock;
				break;
			case '^':
				grid_2323[index_r][index_c].slope = n_slope;
				break;
			case '>':
				grid_2323[index_r][index_c].slope = e_slope;
				break;
			case 'v':
				grid_2323[index_r][index_c].slope = s_slope;
				break;
			case '<':
				grid_2323[index_r][index_c].slope = w_slope;
				break;
			default:
				printf("ERROR: unknown character type: %c at (%d, %d)\n", line[index_c], index_r, index_c);
				return -2;
			}
			index_c++;
		}
		index_r++;
	}
	fclose(fptr);

	grid_size = index_r;
	end_r = grid_size - 1;
	end_c = grid_size - 2;
	
	calculate_distance(end_r, end_c);
	for (index_r = 0; index_r < grid_size; index_r++) {
		for (index_c = 0; index_c < grid_size; index_c++) {
			switch (grid_2323[index_r][index_c].slope) {
			case rock:
				printf("#");
				break;
			case start:
				printf("S");
				break;
			case standard:
				if (grid_2323[index_r][index_c].length >= 0) {
					printf("O");
				} else {
					printf(".");
				}
				break;
			case n_slope:
				if (grid_2323[index_r][index_c].length >= 0) {
					printf("O");
				} else {
					printf("^");
				}
				break;
			case e_slope:
				if (grid_2323[index_r][index_c].length >= 0) {
					printf("O");
				} else {
					printf(">");
				}
				break;
			case s_slope:
				if (grid_2323[index_r][index_c].length >= 0) {
					printf("O");
				} else {
					printf("v");
				}
				break;
			case w_slope:
				if (grid_2323[index_r][index_c].length >= 0) {
					printf("O");
				} else {
					printf("<");
				}
				break;
			}
		}
		printf("\n");
	}
	printf("Part 1: %d\n", grid_2323[end_r][end_c].length);

	nodes[1].connection_weight[s_slope] = 0;
	nodes[1].connection_weight[n_slope] = -1;
	nodes[1].connection_weight[e_slope] = -1;
	nodes[1].connection_weight[w_slope] = -1;
	nodes[1].i_col = end_c;
	nodes[1].i_row = end_r;
	node_count = 2;

	build_nodes(0);

	build_path(0, 1);

	printf("Part 2: %lu\n", nodes[1].weight);

	return 0;
}

static void calculate_distance(int16_t end_r, int16_t end_c) {
	struct slope_queue_node* temp = NULL;

	temp = get_next();
	if (temp == NULL) {
		printf("Queue is empty at the start\n");
		exit(-4);
	}

	while (temp != NULL) {
		//printf("Checking: (%d, %d), length: %d\n", temp->data->row, temp->data->col, temp->data->length);

		if (temp->data->row - 1 >= 0) {
			if (temp->data->row - 1 != temp->i_row) {
				switch (grid_2323[temp->data->row - 1][temp->data->col].slope) {
				case s_slope:
				case rock:
					break;
				case e_slope:
				case w_slope:
				case n_slope:
				case standard:
					if (temp->data->length + 1 > grid_2323[temp->data->row - 1][temp->data->col].length) {
						grid_2323[temp->data->row - 1][temp->data->col].length = temp->data->length + 1;
						append(temp->data->row - 1, temp->data->col, temp->data->row, temp->data->col);
					}
					break;
				default:
					printf("Check 1. Grid has a slope not recognized: %c at: (%d, %d), checking from (%d, %d)\n", grid_2323[temp->data->row - 1][temp->data->col].slope, temp->data->row - 1, temp->data->col, temp->data->row, temp->data->col);
					exit(-3);
				}
			}
		}
		if (temp->data->row + 1 < grid_size) {
			if (temp->data->row + 1 != temp->i_row) {
				switch (grid_2323[temp->data->row + 1][temp->data->col].slope) {
				case n_slope:
				case rock:
					break;
				case e_slope:
				case w_slope:
				case s_slope:
				case standard:
					if (temp->data->length + 1 > grid_2323[temp->data->row + 1][temp->data->col].length) {
						grid_2323[temp->data->row + 1][temp->data->col].length = temp->data->length + 1;
						append(temp->data->row + 1, temp->data->col, temp->data->row, temp->data->col);
					}
					break;
				default:
					printf("Check 2. Grid has a slope not recognized: %c at: (%d, %d), checking from (%d, %d)\n", grid_2323[temp->data->row + 1][temp->data->col].slope, temp->data->row + 1, temp->data->col, temp->data->row, temp->data->col);
					exit(-3);
				}
			}
		}
		if (temp->data->col - 1 >= 0) {
			if (temp->data->col - 1 != temp->i_col) {
				switch (grid_2323[temp->data->row][temp->data->col - 1].slope) {
				case e_slope:
				case rock:
					break;
				case s_slope:
				case w_slope:
				case n_slope:
				case standard:
					if (temp->data->length + 1 > grid_2323[temp->data->row][temp->data->col - 1].length) {
						grid_2323[temp->data->row][temp->data->col - 1].length = temp->data->length + 1;
						append(temp->data->row, temp->data->col - 1, temp->data->row, temp->data->col);
					}
					break;
				default:
					printf("Check 3. Grid has a slope not recognized: %c at (%d, %d), checking from (%d, %d)\n", grid_2323[temp->data->row][temp->data->col - 1].slope, temp->data->row, temp->data->col - 1, temp->data->row, temp->data->col);
					exit(-3);
				}
			}
		}
		if (temp->data->col + 1 < grid_size) {
			if (temp->data->col + 1 != temp->i_col) {
				switch (grid_2323[temp->data->row][temp->data->col + 1].slope) {
				case w_slope:
				case rock:
					break;
				case e_slope:
				case n_slope:
				case s_slope:
				case standard:
					if (temp->data->length + 1 > grid_2323[temp->data->row][temp->data->col + 1].length) {
						grid_2323[temp->data->row][temp->data->col + 1].length = temp->data->length + 1;
						append(temp->data->row, temp->data->col + 1, temp->data->row, temp->data->col);
					}
					break;
				default:
					printf("Check 4. Grid has a slope not recognized: %c at (%d, %d), checking from (%d, %d)\n", grid_2323[temp->data->row][temp->data->col + 1].slope, temp->data->row, temp->data->col + 1, temp->data->row, temp->data->col);
					exit(-3);
				}
			}
		}
		free(temp);
		temp = get_next();
	}
	//printf("Done: (%d, %d)\n", temp->data->row, temp->data->col);
}

static void build_path(int16_t start_node, int16_t end_node) {
	int32_t count = 0;
	int8_t index = 0;

	//printf("Node: (%d, %d), weight: %d\n", nodes[start_node].i_row, nodes[start_node].i_col, nodes[start_node].weight);

	nodes[start_node].visited = 1;

	for (index = 0; index < 4; index++) {
		if (nodes[start_node].connection_weight[index] > 0 && nodes[start_node].connections[index]->visited != 1) {
			if (nodes[end_node].i_row != nodes[start_node].connections[index]->i_row || nodes[end_node].i_col != nodes[start_node].connections[index]->i_col) {
				nodes[start_node].connections[index]->weight = nodes[start_node].weight + nodes[start_node].connection_weight[index];
				build_path(find_node(nodes[start_node].connections[index]->i_row, nodes[start_node].connections[index]->i_col), end_node);
			} else {
				//printf("End weight attempt. New Weight: %d, Current weight: %d\n", nodes[start_node].weight + nodes[start_node].connection_weight[index], nodes[end_node].weight);
				if (nodes[start_node].weight + nodes[start_node].connection_weight[index] > nodes[end_node].weight) {
					nodes[end_node].weight = nodes[start_node].weight + nodes[start_node].connection_weight[index];
				}
			}
		}
	}
	nodes[start_node].visited = 0;
}

static void build_nodes(int16_t node) {
	enum type_2323 dir = n_slope; //go north east south west 0123
	int16_t row = nodes[node].i_row;
	int16_t col = nodes[node].i_col;
	int16_t count = 0;

	//first check north
	if (nodes[node].connection_weight[n_slope] == -1) {
		if (grid_2323[row - 1][col].slope < 5) {
			row--;
			count += 2;

			if (grid_2323[row - 1][col].slope < 5) {
				nodes[node].connections[n_slope] = move(n_slope, row - 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row][col - 1].slope < 5) {
				nodes[node].connections[n_slope] = move(w_slope, row, col - 1, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row][col + 1].slope < 5) {
				nodes[node].connections[n_slope] = move(e_slope, row, col + 1, &count, nodes[node].i_row, nodes[node].i_col);
			}
			nodes[node].connection_weight[n_slope] = count;
		} else {
			nodes[node].connection_weight[n_slope] = 0;
		}
	}

	//east
	count = 0;
	row = nodes[node].i_row;
	col = nodes[node].i_col;
	if (nodes[node].connection_weight[e_slope] == -1) {
		if (grid_2323[row][col + 1].slope < 5) {
			col++;
			count += 2;

			if (grid_2323[row - 1][col].slope < 5) {
				nodes[node].connections[e_slope] = move(n_slope, row - 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row + 1][col].slope < 5) {
				nodes[node].connections[e_slope] = move(s_slope, row + 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row][col + 1].slope < 5) {
				nodes[node].connections[e_slope] = move(e_slope, row, col + 1, &count, nodes[node].i_row, nodes[node].i_col);
			}
			nodes[node].connection_weight[e_slope] = count;
		} else {
			nodes[node].connection_weight[e_slope] = 0;
		}
	}

	//south
	count = 0;
	row = nodes[node].i_row;
	col = nodes[node].i_col;
	if (nodes[node].connection_weight[s_slope] == -1) {
		if (grid_2323[row + 1][col].slope < 5) {
			row++;
			count += 2;

			if (grid_2323[row][col - 1].slope < 5) {
				nodes[node].connections[s_slope] = move(w_slope, row, col - 1, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row + 1][col].slope < 5) {
				nodes[node].connections[s_slope] = move(s_slope, row + 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row][col + 1].slope < 5) {
				nodes[node].connections[s_slope] = move(e_slope, row, col + 1, &count, nodes[node].i_row, nodes[node].i_col);
			}
			nodes[node].connection_weight[s_slope] = count;
		} else {
			nodes[node].connection_weight[s_slope] = 0;
		}
	}

	//west
	count = 0;
	row = nodes[node].i_row;
	col = nodes[node].i_col;
	if (nodes[node].connection_weight[w_slope] == -1) {
		if (grid_2323[row][col - 1].slope < 5) {
			col--;
			count += 2;

			if (grid_2323[row - 1][col].slope < 5) {
				nodes[node].connections[w_slope] = move(n_slope, row - 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row + 1][col].slope < 5) {
				nodes[node].connections[w_slope] = move(s_slope, row + 1, col, &count, nodes[node].i_row, nodes[node].i_col);
			} else if (grid_2323[row][col - 1].slope < 5) {
				nodes[node].connections[w_slope] = move(e_slope, row, col - 1, &count, nodes[node].i_row, nodes[node].i_col);
			}
			nodes[node].connection_weight[w_slope] = count;
		} else {
			nodes[node].connection_weight[w_slope] = 0;
		}
	}
}

static int16_t find_node(int16_t row, int16_t col) {
	int16_t index = 0;

	for (index = 0; index < node_count && index < NODES; index++) {
		if (nodes[index].i_col == col && nodes[index].i_row == row) {
			break;
		}
	}

	if (index >= node_count) {
		index = -1;
	}

	return index;
}

static struct slope_graph_node* move(enum type_2323 last_dir, int16_t i_row, int16_t i_col, int16_t* count, int16_t s_row, int16_t s_col) {
	int16_t row = i_row;
	int16_t col = i_col;
	int16_t ans = *count;
	enum type_2323 temp;

	if (find_node(s_row, s_col) == -1) {
		printf("Error, start isn't a node: (%d, %d)\n", s_row, s_col);
	}

	while (grid_2323[row][col].slope == standard) {
		//printf("Next square (%d, %d). Type %d, count: %d\n", row, col, grid_2323[row][col].slope, ans);
		if (last_dir != s_slope && row - 1 > 0) {
			if (grid_2323[row - 1][col].slope != rock) {
				row--;
				ans++;
				last_dir = n_slope;
				continue;
			}
		}
		if (last_dir != n_slope && row + 1 < MAX_SIZE) {
			if (grid_2323[row + 1][col].slope != rock) {
				row++;
				ans++;
				last_dir = s_slope;
				continue;
			}
		}
		if (last_dir != e_slope && col - 1 > 0) {
			if (grid_2323[row][col - 1].slope != rock) {
				col--;
				ans++;
				last_dir = w_slope;
				continue;
			}
		}
		if (last_dir != w_slope && col + 1 < MAX_SIZE) {
			if (grid_2323[row][col + 1].slope != rock) {
				col++;
				ans++;
				last_dir = e_slope;
				continue;
			}
		}
	}

	ans++;
	*count = ans;
	switch (last_dir) {
	case n_slope:
		if (grid_2323[row - 1][col].slope < 5) {
			row--;
			temp = s_slope;
		} else if (grid_2323[row][col - 1].slope < 5) {
			col--;
			temp = e_slope;
		} else if (grid_2323[row][col + 1].slope < 5) {
			col++;
			temp = w_slope;
		}
		break;
	case s_slope:
		if (grid_2323[row + 1][col].slope < 5) {
			row++;
			temp = n_slope;
		} else if (grid_2323[row][col - 1].slope < 5) {
			col--;
			temp = e_slope;
		} else if (grid_2323[row][col + 1].slope < 5) {
			col++;
			temp = w_slope;
		}
		break;
	case e_slope:
		if (grid_2323[row - 1][col].slope < 5) {
			row--;
			temp = s_slope;
		} else if (grid_2323[row + 1][col].slope < 5) {
			row++;
			temp = n_slope;
		} else if (grid_2323[row][col + 1].slope < 5) {
			col++;
			temp = w_slope;
		}
		break;
	case w_slope:
		if (grid_2323[row - 1][col].slope < 5) {
			row--;
			temp = s_slope;
		} else if (grid_2323[row][col - 1].slope < 5) {
			col--;
			temp = e_slope;
		} else if (grid_2323[row + 1][col].slope < 5) {
			row++;
			temp = n_slope;
		}
		break;
	}

	if (grid_2323[row][col].slope == rock) {
		printf("ERROR: MOVED ONTO A ROCK!!!!!\n");
		exit(-5);
	}
		
	if (find_node(row, col) == -1) {
		nodes[node_count].connection_weight[s_slope] = -1;
		nodes[node_count].connection_weight[n_slope] = -1;
		nodes[node_count].connection_weight[e_slope] = -1;
		nodes[node_count].connection_weight[w_slope] = -1;
		nodes[node_count].i_col = col;
		nodes[node_count].i_row = row;
		nodes[node_count].visited = 0;
		nodes[node_count].connection_weight[temp] = *count;
		ans = find_node(s_row, s_col);
		if (ans == -1) {
			printf("ERROR: incoming row, col not a node. (%d, %d)\n", s_row, s_col);
			exit(-4);
		} else {
			nodes[node_count].connections[temp] = &nodes[find_node(s_row, s_col)];
		}
		node_count++;
		ans = find_node(row, col);
		printf("Node Added: (%d, %d)\n", row, col);
		build_nodes(node_count - 1);
	} else {
		ans = find_node(row, col);
		nodes[ans].connection_weight[temp] = *count;
		nodes[ans].connections[temp] = &nodes[find_node(s_row, s_col)];
	}
	
	return &nodes[ans];
}

static void append(int16_t n_row, int16_t n_col, int16_t c_row, int16_t c_col) {
	struct slope_queue_node* temp = malloc(sizeof(struct slope_queue_node));
	if (temp == NULL) {
		printf("Error making node\n");
		exit(-3);
	}
	temp->data = &grid_2323[n_row][n_col];
	temp->i_col = c_col;
	temp->i_row = c_row;
	temp->next = NULL;
	if (head == NULL) {
		head = temp;
		tail = head;
		head->next = NULL;
	} else {
		tail->next = temp;
		tail = temp;
	}
} 

static struct slope_grid_2323* get_next() {
	struct slope_queue_node* temp = head;
	if (head != NULL) {
		head = head->next;
	}
	return temp;
}