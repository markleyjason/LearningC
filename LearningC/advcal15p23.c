#include <stdio.h>
#include <stdint.h>
#include "helper.h"
#define MAX_INSTRUCT_LEN 100

enum instructions_adv15p23 {
	hlf,
	tpl,
	inc,
	jmp,
	jie,
	jio
};

struct instruction_adv15p23 {
	enum instructions_adv15p23 type;
	char reg;
	int32_t extra;
};

int advcal15p23() {
	uint32_t reg_a = 0;
	uint32_t reg_b = 0;
	uint32_t instr = 0;
	size_t   logic_len = 0;
	struct instruction_adv15p23 instructions[MAX_INSTRUCT_LEN];
	FILE* fptr;
	errno_t error;
	char line[15] = "\0";

	error = fopen_s(&fptr, "input2015p23.txt", "r");
	if (error) {
		printf("Failed to open file\n");
		return -1;
	}

	while (fgets(line, 15, fptr) != NULL) {
		switch (line[0]) {
		case 'j':
			if (line[1] == 'm') {
				instructions[logic_len].type = jmp;
				instructions[logic_len].extra = stoai(&line[4]);
			} else if (line[2] == 'e') {
				instructions[logic_len].type = jie;
				instructions[logic_len].reg = line[4];
				instructions[logic_len].extra = stoai(&line[7]);
			} else {
				instructions[logic_len].type = jio;
				instructions[logic_len].reg = line[4];
				instructions[logic_len].extra = stoai(&line[7]);
			}
			break;
		case 'h':
			instructions[logic_len].type = hlf;
			instructions[logic_len].reg = line[4];
			break;
		case 't':
			instructions[logic_len].type = tpl;
			instructions[logic_len].reg = line[4];
			break;
		case 'i':
			instructions[logic_len].type = inc;
			instructions[logic_len].reg = line[4];
			break;
		}
		logic_len++;
	}

	while (instr < logic_len && instr >= 0) {
		switch (instructions[instr].type) {
		case inc:
			if (instructions[instr].reg == 'a') {
				reg_a++;
			} else {
				reg_b++;
			}
			instr++;
			break;
		case tpl:
			if (instructions[instr].reg == 'a') {
				reg_a *= 3;
			} else {
				reg_b *= 3;
			}
			instr++;
			break;
		case hlf:
			if (instructions[instr].reg == 'a') {
				reg_a = reg_a / 2;
			} else {
				reg_b = reg_b / 2;
			}
			instr++;
			break;
		case jmp:
			instr += instructions[instr].extra;
			break;
		case jie:
			if (instructions[instr].reg == 'a') {
				if (reg_a % 2 == 0) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			} else {
				if (reg_b % 2 == 0) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			}
			break;
		case jio:
			if (instructions[instr].reg == 'a') {
				if (reg_a == 1) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			} else {
				if (reg_b == 1) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			}
			break;
		}
	}
	printf("Reg b: %i\n", reg_b);
	printf("Reg a: %i\n", reg_a);
	instr = 0;
	reg_a = 1;
	reg_b = 0;
	while (instr < logic_len && instr >= 0) {
		switch (instructions[instr].type) {
		case inc:
			if (instructions[instr].reg == 'a') {
				reg_a++;
			} else {
				reg_b++;
			}
			instr++;
			break;
		case tpl:
			if (instructions[instr].reg == 'a') {
				reg_a *= 3;
			} else {
				reg_b *= 3;
			}
			instr++;
			break;
		case hlf:
			if (instructions[instr].reg == 'a') {
				reg_a = reg_a / 2;
			} else {
				reg_b = reg_b / 2;
			}
			instr++;
			break;
		case jmp:
			instr += instructions[instr].extra;
			break;
		case jie:
			if (instructions[instr].reg == 'a') {
				if (reg_a % 2 == 0) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			} else {
				if (reg_b % 2 == 0) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			}
			break;
		case jio:
			if (instructions[instr].reg == 'a') {
				if (reg_a == 1) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			} else {
				if (reg_b == 1) {
					instr += instructions[instr].extra;
				} else {
					instr++;
				}
			}
			break;
		}
		return 0;
	}
	printf("Reg b: %i\n", reg_b);
	printf("Reg a: %i\n", reg_a);
}