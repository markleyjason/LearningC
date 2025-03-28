#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hashtable.h"
#define NAME_SIZE 3
#define MAX_LISTENERS 7
#define MAX_INPUTS 10
#define INPUT_BUFFER 40

enum comp_type {
	flip,
	conj
};

enum pulse_type {
	low_pulse,
	high_pulse
};

enum state {
	off,//also treated as low for conj input states
	on//also treated as high for conj input states
};

struct component {
	char name[NAME_SIZE];
	char listener[MAX_LISTENERS][NAME_SIZE];
	int16_t num_listens;
	enum comp_type type;
	enum state state;
	char inputs[MAX_INPUTS][NAME_SIZE];
	enum state input_states[MAX_INPUTS];
	int16_t input_state_size;
};

struct queue_message {
	enum pulse_type type;
	char receiver[NAME_SIZE];
	char sender[NAME_SIZE];
};

struct node {
	struct queue_message data;
	struct node* next;
};

void broadcast(void);
void handle_pulse(enum pulse_type type, char comp[NAME_SIZE], char sender[NAME_SIZE]);
void handle_conj(enum pulse_type type, struct component* handler, char sender[NAME_SIZE]);
void handle_flip_comp(enum pulse_type type, struct component* handler);
void append_queue(enum pulse_type type, char comp[NAME_SIZE], char sender[NAME_SIZE]);

int32_t mapping_hash_funct_2320(const void* data, const void* context);
int32_t searching_hash_funct_2320(const void* data, const void* context);
int32_t compare_funct_2320(const void* item1, const void* item2, const void* context);

int64_t low_pulse_count;
int64_t high_pulse_count;
hashtable component_list;
struct node* queue_head;
struct node* queue_tail;
char debug = 1;
char sent = 0;

char bm_flag = 0;
char cl_flag = 0;
char tn_flag = 0;
char dr_flag = 0;

uint64_t count_2320 = 0;


int adv2023p20(){
//int main() {
	FILE* fptr;
	errno_t error;
	char line[INPUT_BUFFER];
	hashtableReturnCodes hash_errors;
	struct component temp = { 0 };
	struct component* temp_s;
	uint64_t index = 0;
	int16_t output_i = 0;
	char temp_name[NAME_SIZE] = { '\0' };
	struct node* temp_n;

	queue_head = NULL;

	hash_errors = setUpHashTable(&component_list, 20, sizeof(struct component));
	if (hash_errors != SUCCESS) {
		printf("ERROR setting up hashtable\n");
		return -2;
	}

	error = fopen_s(&fptr, "input2023p20.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Error opening file\n");
		return -1;
	}
	while (fgets(line, INPUT_BUFFER, fptr) != NULL) {
		index = 0;
		temp.num_listens = 0;
		temp.input_state_size = 0;
		switch (line[index]) {
		case '&':
			temp.type = conj;
			temp.state = off;
			temp.name[0] = line[1];
			temp.name[1] = line[2];
			index = 7;
			output_i = 0;
			temp.input_state_size = 0;
			temp.num_listens = 0;
			//build output list, connect to any conj
			while (line[index] != '\n' && line[index] != '\0') {
				temp_name[0] = line[index];
				index++;
				temp_name[1] = line[index];
				index++;
				error = strcpy_s(temp.listener[temp.num_listens], NAME_SIZE, temp_name);
				temp.num_listens++;
				if (error) {
					printf("ERROR copying name to output list for component: %s\n", temp.name);
				}
				temp_s = containsItem(&component_list, temp_name, NULL, searching_hash_funct_2320, NULL, compare_funct_2320);
				if (temp_s != NULL) {
					if (temp_s->type == conj) {
						error = strcpy_s(temp_s->inputs[temp_s->input_state_size], NAME_SIZE, temp.name);
						if (error) {
							printf("ERROR copying to input list for %s\n", temp.name);
							return -4;
						}
						temp_s->input_states[temp_s->input_state_size] = off;
						temp_s->input_state_size++;
					}
				}
				if (line[index] == ',') {
					index += 2;
				}
			}
			hash_errors = insertHashTable(&component_list, &temp, NULL, mapping_hash_funct_2320);
			if (hash_errors != SUCCESS) {
				printf("ERROR inserting conj: %s into hash table\n", temp.name);
				return -5;
			}
			break;
		case '%':
			temp.type = flip;
			temp.state = off;
			temp.name[0] = line[1];
			temp.name[1] = line[2];
			index = 7;
			output_i = 0;
			temp.input_state_size = 0;
			temp.num_listens = 0;
			//build output list, connect to any conj
			while (line[index] != '\n' && line[index] != '\0') {
				temp_name[0] = line[index];
				index++;
				temp_name[1] = line[index];
				index++;
				temp_name[2] = '\0';
				error = strcpy_s(temp.listener[temp.num_listens], NAME_SIZE, temp_name);
				temp.num_listens++;
				if (error) {
					printf("ERROR copying name to output list for component: %s\n", temp.name);
				}
				temp_s = containsItem(&component_list, temp_name, NULL, searching_hash_funct_2320, NULL, compare_funct_2320);
				if (temp_s != NULL) {
					if (temp_s->type == conj) {
						error = strcpy_s(temp_s->inputs[temp_s->input_state_size], NAME_SIZE, temp.name);
						if (error) {
							printf("ERROR copying to input list for %s\n", temp.name);
							return -4;
						}
						temp_s->input_states[temp_s->input_state_size] = off;
						temp_s->input_state_size++;
					}
				}
				if (line[index] == ',') {
					index += 2;
				}
			}
			hash_errors = insertHashTable(&component_list, &temp, NULL, mapping_hash_funct_2320);
			if (hash_errors != SUCCESS) {
				printf("ERROR inserting conj: %s into hash table\n", temp.name);
				return -5;
			}
			break;
		default:
			if (line[0] == 'b') {
				temp.type = flip;
				temp.state = off;
				temp.name[0] = 'i';
				temp.name[1] = 'n';
				index = 15;
				output_i = 0;
				temp.input_state_size = 0;
				//build output list, connect to any conj
				while (line[index] != '\n' && line[index] != '\0') {
					temp_name[0] = line[index];
					index++;
					temp_name[1] = line[index];
					index++;
					temp_name[2] = '\0';
					error = strcpy_s(temp.listener[temp.num_listens], NAME_SIZE, temp_name);
					temp.num_listens++;
					if (error) {
						printf("ERROR copying name to output list for component: %s\n", temp.name);
					}
					temp_s = containsItem(&component_list, temp_name, NULL, searching_hash_funct_2320, NULL, compare_funct_2320);
					if (temp_s != NULL) {
						if (temp_s->type == conj) {
							error = strcpy_s(temp_s->inputs[temp_s->input_state_size], NAME_SIZE, temp.name);
							if (error) {
								printf("ERROR copying to input list for %s\n", temp.name);
								return -4;
							}
							temp_s->input_states[temp_s->input_state_size] = off;
							temp_s->input_state_size++;
						}
					}
					if (line[index] == ',') {
						index += 2;
					}
				}
				hash_errors = insertHashTable(&component_list, &temp, NULL, mapping_hash_funct_2320);
				if (hash_errors != SUCCESS) {
					printf("ERROR inserting conj: %s into hash table\n", temp.name);
					return -5;
				}
			} else {
				printf("ERROR parsing input\n");
				return -1;
			}
		}
	}
	fclose(fptr);
    count_2320 = 0;

	while (count_2320 <= 1000) {
		if (queue_head == NULL) {
			if (count_2320 >= 1000) {
				break;
			}
			count_2320++;
			if (debug == 0) {
				printf("%s -low-> %s\n", "button", "broadcaster");
			}
			low_pulse_count++;
			broadcast();
		} else {
			temp_n = queue_head;
			queue_head = queue_head->next;
			handle_pulse(temp_n->data.type, temp_n->data.receiver, temp_n->data.sender);
			free(temp_n);
		}
	}
	printf("Part 1: %llu\n", low_pulse_count* high_pulse_count);
	while (sent == 0) {
		if (queue_head == NULL) {
			count_2320++;
			//printf("Index: %llu\n", count_2320);
			if (debug == 0) {
				printf("%s -low-> %s\n", "button", "broadcaster");
			}
			low_pulse_count++;
			broadcast();
		} else {
			temp_n = queue_head;
			queue_head = queue_head->next;
			handle_pulse(temp_n->data.type, temp_n->data.receiver, temp_n->data.sender);
			free(temp_n);
		}
	}
	printf("Index: %llu\n", count_2320);
	return 0;
}

void broadcast(void) {
	int16_t index;
	struct component* temp = containsItem(&component_list, "in", NULL, searching_hash_funct_2320, NULL, compare_funct_2320);
	if (temp == NULL) {
		printf("ERROR finding broadcast component\n");
		exit(-5);
	}
	for (index = 0; index < temp->num_listens; index++) {
		low_pulse_count++;
		append_queue(low_pulse, temp->listener[index], "in");
	}
}

void handle_pulse(enum pulse_type type, char comp[NAME_SIZE], char sender[NAME_SIZE]) {
	struct component* handler = containsItem(&component_list, comp, NULL, searching_hash_funct_2320, NULL, compare_funct_2320);
	if (handler == NULL) {
		if (strcmp("ou", comp) == 0) {
			return;
		}
		//printf("ERROR didn't find component: %s, sender: %s, type: %d\n", comp, sender, type);
		//exit(-8);
		if (sent == 0 && type == low_pulse) {
			printf("Button presses: %llu\n", low_pulse_count + high_pulse_count);
			sent = 1;
		}
		
		return;
	} else if (strcmp(comp, "vr") == 0 && type == high_pulse) {
		printf("Comp: %s got sent: %d from: %s at count: %llu\n", comp, type, sender, count_2320);
	}
	switch (handler->type) {
	case conj:
		handle_conj(type, handler, sender);
		break;
	case flip:
		handle_flip_comp(type, handler);
		break;
	}
}

void handle_conj(enum pulse_type type, struct component* handler, char sender[NAME_SIZE]) {
	int16_t index = 0;
	char correct_state = 0;
	
	for (index = 0; index < handler->input_state_size; index++) {
		if (strcmp(handler->inputs[index], sender) == 0) {
			handler->input_states[index] = type;
		}
	}
	for (index = 0; index < handler->input_state_size; index++) {
		if (handler->input_states[index] == low_pulse) {
			correct_state = 1;
		}
	}
	if (correct_state == 0) {
		for (index = 0; index < handler->num_listens; index++) {
			low_pulse_count++;
			append_queue(low_pulse, handler->listener[index], handler->name);
		}
	} else {
		for (index = 0; index < handler->num_listens; index++) {
			high_pulse_count++;
			append_queue(high_pulse, handler->listener[index], handler->name);
		}
	}
}

void handle_flip_comp(enum pulse_type type, struct component* handler) {
	int16_t index = 0;
	switch (type) {
	case low_pulse:
		if (handler->state == off) {
			handler->state = on;
			for (index = 0; index < handler->num_listens; index++) {
				high_pulse_count++;
				append_queue(high_pulse, handler->listener[index], handler->name);
			}
		} else {
			handler->state = off;
			for (index = 0; index < handler->num_listens; index++) {
				low_pulse_count++;
				append_queue(low_pulse, handler->listener[index], handler->name);
			}
		}
		break;
	case high_pulse:
		//do nothing for now.
		break;
	default:
		printf("ERROR: Expected high or low\n");
		exit(-2);
	}
}

void append_queue(enum pulse_type type, char comp[NAME_SIZE], char sender[NAME_SIZE]) {
	struct node* temp = malloc(sizeof(struct node));
	errno_t error;
	if (temp == NULL) {
		printf("ERROR making new node for queue\n");
		exit(-3);
	}
	temp->data.type = type;
	error = strcpy_s(temp->data.receiver, NAME_SIZE, comp);
	if (error) {
		printf("ERROR copying receiver name in append method, sender: %s\n", comp);
		exit(-7);
	}
	error = strcpy_s(temp->data.sender, NAME_SIZE, sender);
	if (error) {
		printf("ERROR copying sender name in append method, sender: %s\n", comp);
		exit(-7);
	}
	if (debug == 0) {
		switch (type) {
		case low_pulse:
			printf("%s -low-> %s\n", sender, comp);
			break;
		case high_pulse:
			printf("%s -high-> %s\n", sender, comp);
			break;
		default:
			printf("ERROR no type sent for appending to queue, sender: %s\n", sender);
			exit(-6);
		}	
	}
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

int32_t mapping_hash_funct_2320(const void* data, const void* context) {
	struct component* the_component = (struct component*)data;

	return the_component->name[0] + the_component->name[1];
}

int32_t searching_hash_funct_2320(const void* data, const void* context) {
	char* name = (char*)data;
	return name[0] + name[1];
}

int32_t compare_funct_2320(const void* item1, const void* item2, const void* context) {
	struct component* first = (struct component*)item1;
	char* second = (char*)item2;
	return strcmp(first->name, second);
}