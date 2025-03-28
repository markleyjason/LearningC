#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <locale.h>
#include "hashtable.h"
#include "helper.h"

#define MAX_NAME 6
#define LINE_SIZE 50

static enum sign {
	less,
	greater,
	last
};

static struct rule {
	char cat;
	enum sign comp;
	uint64_t value;
	char next_rule[MAX_NAME];
};

static struct mapping {
	char name[MAX_NAME];
	int8_t num_rules;
	struct rule the_rules[5];
};

static struct part {
	uint64_t x;
	uint64_t m;
	uint64_t a;
	uint64_t s;
};

struct hashtable rule_list;
struct mapping starting_rule;

int32_t mapping_hash_funct(const void* data, const void* context);
int32_t searching_hash_funct(const void* data, const void* context);
int32_t compare_funct(const void* item1, const void* item2, const void* context);
uint64_t check_part(const struct part);
uint64_t check_group(struct part start, struct part end, char name[MAX_NAME], int8_t rule);

static int advcal2023p19(){
//int main() {
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
	struct part temp_part = { .x = 4000, .m = 4000, .a = 4000, .s = 4000 };
	uint64_t total = 0;

	setlocale(LC_NUMERIC, "");

	error = fopen_s(&fptr, "input2023p19.txt", "r");
	//error = fopen_s(&fptr, "testing.txt", "r");
	if (error) {
		printf("Error opening file\n");
		return 1;
	}
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
				hash_errors = insertHashTable(&rule_list, &temp_mapping, NULL, mapping_hash_funct); 
				if (hash_errors != SUCCESS) {
					printf("ERROR: failed to insert first rule into hash table\n");
					return hash_errors;
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
	fclose(fptr);
	cur_part.x = 1;
	cur_part.m = 1;
	cur_part.a = 1;
	cur_part.s = 1;

	total = check_group(cur_part, temp_part, "in", 0);
		
	printf("Part 2 answer: %llu\n", total);

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

uint64_t check_group(struct part start, struct part end, char name[MAX_NAME], int8_t rule) {
	uint64_t ans = 0;
	void* next_workflow;
	struct mapping cur_workflow;
	errno_t error;
	int8_t cur_rule = rule;
	char passing = 0;
	struct part temp_part1 = { 0 };

	next_workflow = containsItem(&rule_list, name, NULL, searching_hash_funct, NULL, compare_funct);
	if (next_workflow == NULL) {
		printf("Error getting next rule\n");
		return 0;
	}
	error = memcpy_s(&cur_workflow, sizeof(struct mapping), next_workflow, sizeof(struct mapping));
	if (error) {
		printf("Error copying next rule\n");
		return 0;
	}

	//evaluate the rules for the groups, recursively calling this method for each new group that is created. If we accept then we add all the possibilities to ans. If rejected remove that group.
	while (passing == 0 && cur_rule < 5) {
		switch (cur_workflow.the_rules[cur_rule].comp) {
		case last:
			passing = 1;
			break;
		case less:
			switch (cur_workflow.the_rules[cur_rule].cat) {
			case 'x':
				if (start.x < cur_workflow.the_rules[cur_rule].value) {
					if (end.x < cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - start.a + 1L) * (end.m - start.m + 1L) * (end.s - start.s + 1L) * (cur_workflow.the_rules[cur_rule].value - start.x);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = cur_workflow.the_rules[cur_rule].value - 1;
							temp_part1.m = end.m;
							temp_part1.a = end.a;
							temp_part1.s = end.s;
							ans += check_group(start, temp_part1, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						start.x = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 'm':
				if (start.m < cur_workflow.the_rules[cur_rule].value) {
					if (end.m < cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - start.a + 1) * (cur_workflow.the_rules[cur_rule].value - start.m) * (end.s - start.s + 1) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = end.x;
							temp_part1.m = cur_workflow.the_rules[cur_rule].value - 1;
							temp_part1.a = end.a;
							temp_part1.s = end.s;
							ans += check_group(start, temp_part1, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						start.m = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 'a':
				if (start.a < cur_workflow.the_rules[cur_rule].value) {
					if (end.a < cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (cur_workflow.the_rules[cur_rule].value - start.a) * (end.m - start.m + 1) * (end.s - start.s + 1) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = end.x;
							temp_part1.m = end.m;
							temp_part1.a = cur_workflow.the_rules[cur_rule].value - 1;
							temp_part1.s = end.s;
							ans += check_group(start, temp_part1, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						start.a = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 's':
				if (start.s < cur_workflow.the_rules[cur_rule].value) {
					if (end.s < cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans 
							ans += (end.a - start.a + 1) * (end.m - start.m + 1) * (cur_workflow.the_rules[cur_rule].value - start.s) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = end.x;
							temp_part1.m = end.m;
							temp_part1.a = end.a;
							temp_part1.s = cur_workflow.the_rules[cur_rule].value - 1;
							ans += check_group(start, temp_part1, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						start.s = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			}
			break;
		case greater:
			switch (cur_workflow.the_rules[cur_rule].cat) {
			case 'x':
				if (end.x > cur_workflow.the_rules[cur_rule].value) {
					if (start.x > cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - start.a + 1) * (end.m - start.m + 1) * (end.s - start.s + 1) * (end.x - cur_workflow.the_rules[cur_rule].value);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = cur_workflow.the_rules[cur_rule].value + 1;
							temp_part1.m = start.m;
							temp_part1.a = start.a;
							temp_part1.s = start.s;
							ans += check_group(temp_part1, end, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						end.x = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 'm':
				if (end.m > cur_workflow.the_rules[cur_rule].value) {
					if (start.m > cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - start.a + 1) * (end.m - cur_workflow.the_rules[cur_rule].value) * (end.s - start.s + 1) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = start.x;
							temp_part1.m = cur_workflow.the_rules[cur_rule].value + 1;
							temp_part1.a = start.a;
							temp_part1.s = start.s;
							ans += check_group(temp_part1, end, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						end.m = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 'a':
				if (end.a > cur_workflow.the_rules[cur_rule].value) {
					if (start.a > cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - cur_workflow.the_rules[cur_rule].value) * (end.m - start.m + 1) * (end.s - start.s + 1) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = start.x;
							temp_part1.m = start.m;
							temp_part1.a = cur_workflow.the_rules[cur_rule].value + 1;
							temp_part1.s = start.s;
							ans += check_group(temp_part1, end, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						end.a = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			case 's':
				if (end.s > cur_workflow.the_rules[cur_rule].value) {
					if (start.s > cur_workflow.the_rules[cur_rule].value) {
						//all are include in this rule
						passing = 1;
					} else { //section off all that pass the rule and do what is needed for them. The rest keep for the following rules.
						if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
							//add these to ans
							ans += (end.a - start.a + 1) * (end.m - start.m + 1) * (end.s - cur_workflow.the_rules[cur_rule].value) * (end.x - start.x + 1);
						} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
							temp_part1.x = start.x;
							temp_part1.m = start.m;
							temp_part1.a = start.a;
							temp_part1.s = cur_workflow.the_rules[cur_rule].value + 1;
							ans += check_group(temp_part1, end, cur_workflow.the_rules[cur_rule].next_rule, 0);
						}
						end.s = cur_workflow.the_rules[cur_rule].value;
					}
				}
				if (passing != 1) {
					cur_rule++;
				}
				break;
			}
			break;
		default:
			printf("ERROR GROUP: Expected a comp enum\n");
			exit(-2);
		}
	}
	if (cur_rule > 4) {
		printf("ERROR: current rule to large\n");
		return ans;
	}
	if (cur_workflow.the_rules[cur_rule].next_rule[0] == 'A') {
		ans += (end.a - start.a + 1) * (end.m - start.m + 1) * (end.s - start.s + 1) * (end.x - start.x + 1);
	} else if (cur_workflow.the_rules[cur_rule].next_rule[0] != 'R') {
		ans += check_group(start, end, cur_workflow.the_rules[cur_rule].next_rule, 0);
	}
	return ans;
}