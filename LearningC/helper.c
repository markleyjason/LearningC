#include "helper.h"
#include <stdlib.h>
#include <stdint.h>

char isDigit(const char input) {
	int32_t ret = 0;
	if (input - '0' >= 0 && input - '0' <= 9) {
		ret = 1;
	}
	return ret;
}

int32_t stringIsDigit(const char* string, const size_t index) {
	int32_t offset = 1;
	switch (string[index]) {
	case 'z':
	case 'Z':
		if (string[index + offset] == 'e' || string[index + offset] == 'E') {
			offset++;
			if (string[index + offset] == 'r' || string[index + offset] == 'R') {
				offset++;
				if (string[index + offset] == 'o' || string[index + offset] == 'O') {
					return 0;
				}
			}
		}
		break;
	case 'o':
	case 'O':
		if (string[index + offset] == 'n' || string[index + offset] == 'N') {
			offset++;
			if (string[index + offset] == 'e' || string[index + offset] == 'E') {
				return 1;
			}
		}
		break;
	case 't':
	case 'T':
		if (string[index + offset] == 'w' || string[index + offset] == 'W') {
			offset++;
			if (string[index + offset] == 'o' || string[index + offset] == 'O') {
				return 2;
			}
		} else if (string[index + offset] == 'h' || string[index + offset] == 'H') {
			offset++;
			if (string[index + offset] == 'r' || string[index + offset] == 'R') {
				offset++;
				if (string[index + offset] == 'e' || string[index + offset] == 'E') {
					offset++;
					if (string[index + offset] == 'e' || string[index + offset] == 'E') {
						return 3;
					}
				}
				
			}
		}
		break;
	case 'f':
	case 'F':
		if (string[index + offset] == 'o' || string[index + offset] == 'O') {
			offset++;
			if (string[index + offset] == 'u' || string[index + offset] == 'U') {
				offset++;
				if (string[index + offset] == 'r' || string[index + offset] == 'R') {
					return 4;
				}
				
			}
		} else if (string[index + offset] == 'i' || string[index + offset] == 'I') {
			offset++;
			if (string[index + offset] == 'v' || string[index + offset] == 'V') {
				offset++;
				if (string[index + offset] == 'e' || string[index + offset] == 'E') {
					return 5;
				}

			}
		}
		break;
	case 's':
	case'S':
		if (string[index + offset] == 'i' || string[index + offset] == 'I') {
			offset++;
			if (string[index + offset] == 'x' || string[index + offset] == 'X') {
				return 6;
			}
		} else if (string[index + offset] == 'e' || string[index + offset] == 'E') {
			offset++;
			if (string[index + offset] == 'v' || string[index + offset] == 'V') {
				offset++;
				if (string[index + offset] == 'e' || string[index + offset] == 'E') {
					offset++;
					if (string[index + offset] == 'n' || string[index + offset] == 'N') {
						return 7;
					}
				}

			}
		}
		break;
	case 'e':
	case 'E':
		if (string[index + offset] == 'i' || string[index + offset] == 'I') {
			offset++;
			if (string[index + offset] == 'g' || string[index + offset] == 'G') {
				offset++;
				if (string[index + offset] == 'h' || string[index + offset] == 'H') {
					offset++;
					if (string[index + offset] == 't' || string[index + offset] == 'T') {
						return 8;
					}
				}

			}
		}
		break;
	case 'n':
	case 'N':
		if (string[index + offset] == 'i' || string[index + offset] == 'I') {
			offset++;
			if (string[index + offset] == 'n' || string[index + offset] == 'N') {
				offset++;
				if (string[index + offset] == 'e' || string[index + offset] == 'E') {
					return 9;
				}

			}
		}
		break;
	}
	return -1;
}

int32_t stoai(const char* input) {
	int32_t factor = 10;
	int32_t sign = 1;
	int32_t index = 0;
	int32_t num = 0;
	if (input[0] == '-') {
		sign = -1;
		index++;
	}
	while (input[index] != '\0') {
		num = num * factor + ctoai(input[index]);
		index++;
	}
	return num * sign;
}

uint32_t stoaui(const char* input) {
	int32_t factor = 10;
	int32_t index = 0;
	uint32_t num = 0;
	while (input[index] != '\0') {
		num = num * factor + ctoai(input[index]);
		index++;
	}
	return num;
}

int64_t stoai64(const char* input) {
	int32_t factor = 10;
	int32_t sign = 1;
	int32_t index = 0;
	int64_t num = 0;
	if (input[0] == '-') {
		sign = -1;
		index++;
	}
	while (input[index] != '\0') {
		num = num * factor + ctoai(input[index]);
		index++;
	}
	return num * sign;
}

int32_t writtenstoad(const char* input) {
	int32_t value = 0;
	if (input[0] == 'z' || input[0] == 'Z') {
		value = 0;
	}else if (input[0] == 'o' || input[0] == 'O') {
		value = 1;
	} else if (input[0] == 't' || input[0] == 'T') {
		if (input[1] == 'w' || input[1] == 'W') {
			value = 2;
		} else {
			value = 3;
		}
	} else if (input[0] == 'f' || input[0] == 'F') {
		if (input[1] == 'o' || input[1] == 'O') {
			value = 4;
		} else {
			value = 5;
		}
	} else if (input[0] == 's' || input[0] == 'S') {
		if (input[1] == 'i' || input[1] == 'I') {
			value = 6;
		} else {
			value = 7;
		}
	} else if (input[0] == 'e' || input[0] == 'E') {
		value = 8;
	} else {
		value = 9;
	}
	return value;
}

//Assumes all integers in the array are only a single digit (0-9)
char* uint32arraytostring(const int32_t size, const int32_t* start) {
	char* array = malloc(sizeof(int32_t) * size + 1);
	int32_t index = 0;
	if (array != NULL) {
		while (index < size) {
			array[index] = start[index] + '0';
			index++;
		}
		array[index] = '\0';
	}
	
	return array;
}

int32_t ctoai(const char input) {
	return (int32_t)input - '0';
}

int32_t hctoai(const char digit) {
	int32_t val = 0;
	if (isDigit(digit)) {
		return ctoai(digit);
	} else {
		switch (digit) {
		case 'a':
		case 'A':
			val = 10;
			break;
		case 'b':
		case 'B':
			val = 11;
			break;
		case 'c':
		case 'C':
			val = 12;
			break;
		case 'd':
		case 'D':
			val = 13;
			break;
		case 'e':
		case 'E':
			val = 14;
			break;
		case 'f':
		case 'F':
			val = 15;
			break;
		default:
			val = -1;
		}
	}
	return val;
}

int32_t findMin(const int32_t* array, const int32_t length) {
	int i = 0;
	int min = INT_MAX;

	for (i = 0; i < length; i++) {
		if (array[i] < min) {
			min = array[i];
		}
	}
	return min;
}

int32_t findVolume(const int32_t length, const int32_t width, const int32_t height) {
	return length * width * height;
}
int32_t findVolumeA(const int32_t* input) {
	return findVolume(input[0], input[1], input[2]);
}
