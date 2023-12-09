#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

#define GRIDSIZE 141
static char partGrid[GRIDSIZE][GRIDSIZE] = { '\0' };

static unsigned __int32 partSum(const unsigned __int32 height, const unsigned __int32 width);
static unsigned __int32 gearSum(const unsigned __int32 height, const unsigned __int32 width);
static char findSymbol(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex);
static unsigned __int32 findDoubleNumberProduct(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex);
static unsigned __int32 returnNumber(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex);

adv2023p3() {
//main() {
	FILE* fptr;
	errno_t error;
	unsigned __int32 mIndex = 0;
	unsigned __int32 sIndex = 0;
	unsigned __int32 sum = 0;
	unsigned __int32 sum2 = 0;
	unsigned __int32 width = 0;
	unsigned __int32 height = 0;
	char line[GRIDSIZE] = { '\0' };


	error = fopen_s(&fptr, "input2023p3.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, GRIDSIZE, fptr) != NULL) {
			if (line[0] != '\n') {
				while (line[sIndex] != '\n' && line[sIndex] != '\0') {
					partGrid[mIndex][sIndex] = line[sIndex];
					sIndex++;
				}
				if (width == 0) {
					width = sIndex;
				}
				sIndex = 0;
				mIndex++;
			}
		}
		height = mIndex;
	}
	sum = partSum(height, width);
	sum2 = gearSum(height, width);
	printf("Part sum: %d\n", sum);
	printf("Gear ratio sum: %d\n", sum2);

}

static unsigned __int32 partSum(const unsigned __int32 height, const unsigned __int32 width) {
	unsigned __int32 mIndex = 0;
	unsigned __int32 sIndex = 0;
	unsigned __int32 partSum = 0;
	unsigned __int32 tempNumber = 0;
	char hasSymbol = 0;

	while (mIndex < height) {
		while (sIndex < width) {
			if (isDigit(partGrid[mIndex][sIndex])) {
				if (hasSymbol == 0) {
					hasSymbol = findSymbol(height, width, mIndex, sIndex);
				}
				tempNumber = ctoai(partGrid[mIndex][sIndex]) + tempNumber * 10;
			} else if (hasSymbol == 1) {
				partSum += tempNumber;
				tempNumber = 0;
				hasSymbol = 0;
			} else if (tempNumber != 0) {
				tempNumber = 0;
			}
			sIndex++;
		}
		if (hasSymbol == 1) {
			partSum += tempNumber;
		}
		tempNumber = 0;
		hasSymbol = 0;
		sIndex = 0;
		mIndex++;
	}
	return partSum;
}

static unsigned __int32 gearSum(const unsigned __int32 height, const unsigned __int32 width) {
	unsigned __int32 mIndex = 0;
	unsigned __int32 sIndex = 0;
	unsigned __int32 sum = 0;
	unsigned __int32 tempNumber = 0;

	while (mIndex < height) {
		while (sIndex < width) {
			if (!isDigit(partGrid[mIndex][sIndex]) && partGrid[mIndex][sIndex] == '*') {
				
				printf("%c at (%d, %d)\n", partGrid[mIndex][sIndex], mIndex, sIndex);
				tempNumber = findDoubleNumberProduct(height, width, mIndex, sIndex);
				printf("%d\n", tempNumber);
				sum += tempNumber;
			}
			sIndex++;
		}
		tempNumber = 0;
		sIndex = 0;
		mIndex++;
	}
	return sum;

}

static char findSymbol(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex) {
	if (sIndex == 0) {
		if (mIndex == 0) {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			}
		} else if (mIndex == height - 1) {
			if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			}
		} else {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				return 1;
			}
		}
	} else if (sIndex == width - 1) {
		if (mIndex == 0) {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			}
		} else if (mIndex == height - 1) {
			if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			}
		} else {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				return 1;
			}
		}
	} else {
		if (mIndex == 0) {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			}
		} else if (mIndex == height - 1) {
			if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			}
		} else {
			if (partGrid[mIndex + 1][sIndex] != '.' && !isDigit(partGrid[mIndex + 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex - 1] != '.' && !isDigit(partGrid[mIndex][sIndex - 1]))) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex] != '.' && !isDigit(partGrid[mIndex - 1][sIndex])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex - 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				return 1;
			} else if (partGrid[mIndex - 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				return 1;
			} else if ((partGrid[mIndex][sIndex + 1] != '.' && !isDigit(partGrid[mIndex][sIndex + 1]))) {
				return 1;
			} else if (partGrid[mIndex + 1][sIndex + 1] != '.' && !isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				return 1;
			}
		}
	}

	return 0;
}

static unsigned __int32 findDoubleNumberProduct(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex) {
	unsigned __int32 firstNumber = 0;
	unsigned __int32 secondNumber = 0;
	if (sIndex == 0) {//sIndex = 0
		if (mIndex == 0) {//mIndex = 0
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			}else if (isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
				} else {
					return 0;
				}
			}
			if ((isDigit(partGrid[mIndex][sIndex + 1]))) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
		} else if (mIndex == height - 1) {//mIndex = height -1
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			}else if (isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
				} else {
					return 0;
				}
			} 
			if ((isDigit(partGrid[mIndex][sIndex + 1]))) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
		} else { //0 < mIndex < Height
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			} else if (isDigit(partGrid[mIndex + 1][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
				} else {
					return 0;
				}
			} 
			if (isDigit(partGrid[mIndex][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			} else if (isDigit(partGrid[mIndex - 1][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
				} else {
					return 0;
				}
			}
		}
	} else if (sIndex == width - 1) {//sIndex = width -1
		if (mIndex == 0) {//mIndex == 0
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			}else if (isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
		} else if (mIndex == height - 1) {//mIndex = Hieght - 1
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			}else if (isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
		} else {// mIndex < 0 > H
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			} else if (isDigit(partGrid[mIndex + 1][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			} else if (isDigit(partGrid[mIndex - 1][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
				} else {
					return 0;
				}
			}
		}
	} else { // sIndex > 0 < H
		if (mIndex == 0) { //mIndex = 0
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			} else {
				if (isDigit(partGrid[mIndex + 1][sIndex - 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
					} else {
						return 0;
					}
				}
				if (isDigit(partGrid[mIndex + 1][sIndex + 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
					} else {
						return 0;
					}
				}
			}
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
		} else if (mIndex == height - 1) { //mIndex == H -1
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			} else {
				if (isDigit(partGrid[mIndex - 1][sIndex - 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
					} else {
						return 0;
					}
				}
				if (isDigit(partGrid[mIndex - 1][sIndex + 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
					} else {
						return 0;
					}
				}
			}
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
		} else {//mIndex > 0 < H
			if (isDigit(partGrid[mIndex + 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex + 1, sIndex);
				} else {
					return 0;
				}
			} else {
				if (isDigit(partGrid[mIndex + 1][sIndex - 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex + 1, sIndex - 1);
					} else {
						return 0;
					}
				}
				if (isDigit(partGrid[mIndex + 1][sIndex + 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex + 1, sIndex + 1);
					} else {
						return 0;
					}
				}
			}
			
			if (isDigit(partGrid[mIndex][sIndex - 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex - 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex][sIndex + 1])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex, sIndex + 1);
				} else {
					return 0;
				}
			}
			if (isDigit(partGrid[mIndex - 1][sIndex])) {
				if (firstNumber == 0) {
					firstNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else if (secondNumber == 0) {
					secondNumber = returnNumber(height, width, mIndex - 1, sIndex);
				} else {
					return 0;
				}
			} else {
				if (isDigit(partGrid[mIndex - 1][sIndex - 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex - 1, sIndex - 1);
					} else {
						return 0;
					}
				}
				if (isDigit(partGrid[mIndex - 1][sIndex + 1])) {
					if (firstNumber == 0) {
						firstNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
					} else if (secondNumber == 0) {
						secondNumber = returnNumber(height, width, mIndex - 1, sIndex + 1);
					} else {
						return 0;
					}
				}
			}
		}
	}

	return firstNumber * secondNumber;
}

static unsigned __int32 returnNumber(const unsigned __int32 height, const unsigned __int32 width, const unsigned __int32 mIndex, const unsigned __int32 sIndex) {
	unsigned __int32 num = 0;
	unsigned __int32 temp = 0;
	unsigned __int32 index = sIndex;

	if (sIndex == 0) {
		while (index < width && isDigit(partGrid[mIndex][index])) {
			num = ctoai(partGrid[mIndex][index]) + num * 10;
			index++;
		}
	} else if (isDigit(partGrid[mIndex][sIndex - 1])) {//search
		index = sIndex - 1;
		while (index > 0 && isDigit(partGrid[mIndex][index])) {
			index--;
		}
		if (index != 0 || !isDigit(partGrid[mIndex][index])) {
			index++;
		}
		while (index < width && isDigit(partGrid[mIndex][index])){
			num = ctoai(partGrid[mIndex][index]) + (num * 10);
			index++;
		}
	} else {
		while (index < width && isDigit(partGrid[mIndex][index])) {
			num = ctoai(partGrid[mIndex][index]) + num * 10;
			index++;
		}
	}
	return num;
}