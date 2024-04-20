#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hashtable.h"
#include "helper.h"

#define MAX_NAME 6
#define LINE_SIZE 50

static enum sign {
	less,
	greater,
	equal,
	last
};

static struct rule {
	char cat;
	enum sign comp;
	int16_t value;
	char next_rule[MAX_NAME];
};

static struct mapping {
	char name[MAX_NAME];
	int8_t num_rules;
	struct rule the_rules[5];
};

static struct part {
	int32_t x;
	int32_t m;
	int32_t a;
	int32_t s;
};

struct hashtable rule_list;
struct mapping starting_rule;

int32_t mapping_hash_funct(const void* data, const void* context);
int32_t searching_hash_funct(const void* data, const void* context);
int32_t compare_funct(const void* item1, const void* item2, const void* context);
uint64_t check_part(const struct part);

//int advcal2023p19(){
int main() {
	FILE* fptr;
	errno_t error;
	char line[LINE_SIZE] = { '\0' };
	int16_t index = 0;
	int16_t sec_index = 0;
	int16_t third = 0;
	int16_t fourth = 0;
	enum HashTableReturnCodes hash_errors;
	char mode = 0;
	struct mapping temp_mapping = { .name = {'\0'}, .num_rules = 0, .the_rules = {'\0'} };
	struct part cur_part = { .x = 0, .m = 0, .a = 0, .s = 0 };
	uint64_t total = 0;

	error = fopen_s(&fptr, "input2023p19.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Error opening file\n");
		return 1;
	} else {
		hash_errors = setUpHashTable(&rule_list, 99, sizeof(struct mapping));
		if (hash_errors != SUCCESS) {
			printf("Error creating hash table\n");
			return hash_errors;
		}
		while (fgets(line, LINE_SIZE, fptr) != NULL) {
			index = 0;
			if (line[index] == '\n'){
				mode = 1;
			} else if (mode == 0) {
				//parse a rule
				temp_mapping.num_rules = 0;
				temp_mapping.name[0] = '\0';
				temp_mapping.the_rules[0].value = 0;
				temp_mapping.the_rules[1].value = 0;
				temp_mapping.the_rules[2].value = 0;
				temp_mapping.the_rules[3].value = 0;
				
				while (line[index] != '{') {
					temp_mapping.name[index] = line[index];
					index++;
				}
				temp_mapping.name[index] = '\0';
				index++;
				
				while (line[index + 1] == '>' || line[index + 1] == '<' || line[index + 1] == '=') {
					temp_mapping.the_rules[temp_mapping.num_rules].cat = line[index];
					index++;
					switch (line[index]) {
					case '>':
						temp_mapping.the_rules[temp_mapping.num_rules].comp = greater;
						break;
					case '<':
						temp_mapping.the_rules[temp_mapping.num_rules].comp = less;
						break;
					case '=':
						temp_mapping.the_rules[temp_mapping.num_rules].comp = equal;
						break;
					default:
						printf("ERROR: expected comp got %c\n", line[index]);
						return 2;
					}
					index++;
					
					while (isDigit(line[index])) {
						temp_mapping.the_rules[temp_mapping.num_rules].value = temp_mapping.the_rules[temp_mapping.num_rules].value * 10
							+ ctoai(line[index]);
						index++;
					}
					
					if (line[index] != ':') {
						printf("ERROR: expected ':' got %c\n", line[index]);
						return 3;
					}
					index++;
					
					sec_index = 0;
					while (line[index] != ',' && line[index] != '}') {
						temp_mapping.the_rules[temp_mapping.num_rules].next_rule[sec_index] = line[index];
						index++;
						sec_index++;
					}
					temp_mapping.the_rules[temp_mapping.num_rules].next_rule[sec_index] = '\0';
					temp_mapping.num_rules++;
					index++;
				}

				temp_mapping.the_rules[temp_mapping.num_rules].comp = last;
				sec_index = 0;
				while (line[index] != '}') {
					temp_mapping.the_rules[temp_mapping.num_rules].next_rule[sec_index] = line[index];
					index++;
					sec_index++;
				}
				temp_mapping.the_rules[temp_mapping.num_rules].next_rule[sec_index] = '\0';
				temp_mapping.num_rules++;

				if (strcmp(temp_mapping.name, "in") == 0) {
					error = memcpy_s(&starting_rule, sizeof(struct mapping), &temp_mapping, sizeof(struct mapping));
					if (error) {
						printf("ERROR: copy into starting rule failed\n");
						return 4;
					}
				} else {
					hash_errors = insertHashTable(&rule_list, &temp_mapping, NULL, mapping_hash_funct);
					if (hash_errors != SUCCESS) {
						printf("ERROR: failed to insert into hash table\n");
						return hash_errors;
					}
				}

			} else {
				//parse the part then check if accepted add else next part
				cur_part.x = 0;
				cur_part.m = 0;
				cur_part.a = 0;
				cur_part.s = 0;
				if (line[index] != '{') {
					printf("ERROR: expected '{' got %c\n", line[index]);
					return -1;
				}
				index++;
				if (line[index] != 'x') {
					printf("ERROR: expected 'x' got %c\n", line[index]);
					return -1;
				}
				index++;
				index++;
				while (isDigit(line[index])) {
					cur_part.x = cur_part.x * 10 + ctoai(line[index]);
					index++;
				}
				index++;
				if (line[index] != 'm') {
					printf("ERROR: expected 'm' got %c\n", line[index]);
					return -1;
				}
				index++;
				index++;
				while (isDigit(line[index])) {
					cur_part.m = cur_part.m * 10 + ctoai(line[index]);
					index++;
				}
				index++;
				if (line[index] != 'a') {
					printf("ERROR: expected 'a' got %c\n", line[index]);
					return -1;
				}
				index++;
				index++;
				while (isDigit(line[index])) {
					cur_part.a = cur_part.a * 10 + ctoai(line[index]);
					index++;
				}
				index++;
				if (line[index] != 's') {
					printf("ERROR: expected 's' got %c\n", line[index]);
					return -1;
				}
				index++;
				index++;
				while (isDigit(line[index])) {
					cur_part.s = cur_part.s * 10 + ctoai(line[index]);
					index++;
				}
				if (line[index] != '}') {
					printf("ERROR: expected '}' got %c\n", line[index]);
					return -1;
				}

				total += check_part(cur_part);
			}
		}
		printf("Part 1 answer: %llu\n", total);
		total = 0;
		for (index = 1; index < 4001; index++) {
			for (sec_index = 1; sec_index < 4001; sec_index++) {
				for (third = 1; third < 4001; third++) {
					for (fourth = 1; fourth < 4001; fourth++) {
						cur_part.x = index;
						cur_part.m = sec_index;
						cur_part.a = third;
						cur_part.s = fourth;
						if (check_part > 0) {
							total++;
						}
					}
				}
			}
			printf("index: %d\n", index);
		}
		printf("Part 2 answer: %llu\n", total);
	}
	return 0;
}

int32_t mapping_hash_funct(const void* data, const void* context) {
	struct mapping* the_mapping = (struct mapping*)data;

	return the_mapping->name[0] + the_mapping->name[1];
}

int32_t searching_hash_funct(const void* data, const void* context) {
	char* name = (char*)data;
	return name[0] + name[1];
}

int32_t compare_funct(const void* item1, const void* item2, const void* context) {
	struct mapping *first = (struct mapping*)item1;
	char* second = (char*)item2;
	return strcmp(first->name, second);
}

uint64_t check_part(const struct part cur_part) {
	uint64_t ans = 0;
	char passing = 0;
	int8_t current_rule = 0;
	struct mapping current_mapping;
	void* next_mapping_place;
	errno_t error;

	while (passing == 0) {
		if (starting_rule.the_rules[current_rule].comp == last) {
			passing = 1;
		} else {
			switch (starting_rule.the_rules[current_rule].comp) {
			case less:
				switch (starting_rule.the_rules[current_rule].cat) {
				case 'x':
					if (cur_part.x < starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'm':
					if (cur_part.m < starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'a':
					if (cur_part.a < starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 's':
					if (cur_part.s < starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				}
				break;
			case greater:
				switch (starting_rule.the_rules[current_rule].cat) {
				case 'x':
					if (cur_part.x > starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'm':
					if (cur_part.m > starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'a':
					if (cur_part.a > starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 's':
					if (cur_part.s > starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				}
				break;
			case equal:
				switch (starting_rule.the_rules[current_rule].cat) {
				case 'x':
					if (cur_part.x == starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'm':
					if (cur_part.m == starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 'a':
					if (cur_part.a == starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				case 's':
					if (cur_part.s == starting_rule.the_rules[current_rule].value) {
						passing = 1;
					} else {
						current_rule++;
					}
					break;
				}
				break;
			default:
				printf("ERROR expected compare enum\n");
				exit(-2);
			}
		}
	}
	next_mapping_place = containsItem(&rule_list, starting_rule.the_rules[current_rule].next_rule, NULL, searching_hash_funct, NULL, compare_funct);
	error = memcpy_s(&current_mapping, sizeof(struct mapping), next_mapping_place, sizeof(struct mapping));
	if (error) {
		printf("Error getting next rule");
	}
	passing = 0;
	while (passing == 0) {
		current_rule = 0;
		while (passing == 0) {
			if (current_mapping.the_rules[current_rule].comp == last) {
				passing = 1;
			} else {
				switch (current_mapping.the_rules[current_rule].comp) {
				case less:
					switch (current_mapping.the_rules[current_rule].cat) {
					case 'x':
						if (cur_part.x < current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'm':
						if (cur_part.m < current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'a':
						if (cur_part.a < current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 's':
						if (cur_part.s < current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					}
					break;
				case greater:
					switch (current_mapping.the_rules[current_rule].cat) {
					case 'x':
						if (cur_part.x > current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'm':
						if (cur_part.m > current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'a':
						if (cur_part.a > current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 's':
						if (cur_part.s > current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					}
					break;
				case equal:
					switch (current_mapping.the_rules[current_rule].cat) {
					case 'x':
						if (cur_part.x == current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'm':
						if (cur_part.m == current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 'a':
						if (cur_part.a == current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					case 's':
						if (cur_part.s == current_mapping.the_rules[current_rule].value) {
							passing = 1;
						} else {
							current_rule++;
						}
						break;
					}
					break;
				default:
					printf("ERROR expected compare enum\n");
					exit(-2);
				}
			}
		}

		if (current_mapping.the_rules[current_rule].next_rule[0] == 'A') {
			passing = 1;
		} else if (current_mapping.the_rules[current_rule].next_rule[0] == 'R') {
			passing = -1;
		} else {
			passing = 0;
		}
		if (passing == 0) {
			if (current_mapping.the_rules[current_rule].next_rule == 'R') {
				passing = -1;
			} else {
				next_mapping_place = containsItem(&rule_list, current_mapping.the_rules[current_rule].next_rule, NULL, searching_hash_funct, NULL, compare_funct);
				error = memcpy_s(&current_mapping, sizeof(struct mapping), next_mapping_place, sizeof(struct mapping));
				if (error) {
					printf("Error getting next rule");
				}
			}
		}
	}

	if (passing == 1) {
		ans = (uint64_t)cur_part.x + cur_part.m + cur_part.a + cur_part.s;
	}
	return ans;
}