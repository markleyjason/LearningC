#include <stdio.h>
#include <stdlib.h>

char lights1[100][100];
char lights2[100][100];

void changeLight1(const unsigned __int32 mainIndex, const unsigned __int32 subIndex);
void changeLight2(const unsigned __int32 mainIndex, const unsigned __int32 subIndex);

adv2015p18() {
//main() {
	FILE* fptr;
	errno_t error;
	char input;
	unsigned __int32 mIndex = 0;
	unsigned __int32 sIndex = 0;
	unsigned __int32 loop = 0;
	char lastused = 0;
	unsigned __int32 count = 0;

	error = fopen_s(&fptr, "input2015p18.txt", "r");

	if (!error) {
		input = getc(fptr);
		while (input != EOF) {
			if (input == '#') {
				lights1[mIndex][sIndex] = 1;
				sIndex++;
			} else if (input == '.') {
				lights1[mIndex][sIndex] = 0;
				sIndex++;
			} else {
				sIndex = 0;
				mIndex++;
			}
			input = getc(fptr);
		}
		
		for (loop = 0; loop < 100; loop++) {
			for (mIndex = 0; mIndex < 100; mIndex++) {
				for (sIndex = 0; sIndex < 100; sIndex++) {
					if (loop % 2 == 0) {
						changeLight1(mIndex, sIndex);
						lastused = 1;
					} else {
						changeLight2(mIndex, sIndex);
						lastused = 0;
					}
				}
			}
		}
		for (mIndex = 0; mIndex < 100; mIndex++) {
			for (sIndex = 0; sIndex < 100; sIndex++) {
				if (lastused == 1) {
					count += lights2[mIndex][sIndex];
				} else {
					count += lights1[mIndex][sIndex];
				}
			}
		}
		printf("Number of lights on is: %d", count);
	}
}

void changeLight1(const unsigned __int32 mainIndex, const unsigned __int32 subIndex) {
	unsigned __int32 lightsOn = 0;
	//find information top bottom
	if (mainIndex == 0 ) {
		lightsOn += lights1[mainIndex + 1][subIndex];
	} else if (mainIndex == 99) {
		lightsOn += lights1[mainIndex - 1][subIndex];
	} else {
		lightsOn += lights1[mainIndex + 1][subIndex];
		lightsOn += lights1[mainIndex - 1][subIndex];
	}

	if (subIndex == 0) {
		lightsOn += lights1[mainIndex][subIndex + 1];
	} else if (subIndex == 99) {
		lightsOn += lights1[mainIndex][subIndex - 1];
	} else {
		lightsOn += lights1[mainIndex][subIndex + 1];
		lightsOn += lights1[mainIndex][subIndex - 1];
	}

	if (mainIndex == 0) {
		if (subIndex == 0) {
			lightsOn = 2;
		} else if (subIndex == 99) {
			lightsOn = 2;
		} else {
			lightsOn += lights1[mainIndex + 1][subIndex - 1];
			lightsOn += lights1[mainIndex + 1][subIndex + 1];
		}
	} else if (mainIndex == 99) {
		if (subIndex == 0) {
			lightsOn = 2;
		} else if (subIndex == 99) {
			lightsOn = 2;
		} else {
			lightsOn += lights1[mainIndex - 1][subIndex - 1];
			lightsOn += lights1[mainIndex - 1][subIndex + 1];
		}
	} else {
		if(subIndex == 0) {
			lightsOn += lights1[mainIndex - 1][subIndex + 1];
			lightsOn += lights1[mainIndex + 1][subIndex + 1];
		} else if (subIndex == 99) {
			lightsOn += lights1[mainIndex - 1][subIndex - 1];
			lightsOn += lights1[mainIndex + 1][subIndex - 1];
		} else {
			lightsOn += lights1[mainIndex + 1][subIndex + 1];
			lightsOn += lights1[mainIndex - 1][subIndex - 1];
			lightsOn += lights1[mainIndex - 1][subIndex + 1];
			lightsOn += lights1[mainIndex + 1][subIndex - 1];
		}
	}
	if (lights1[mainIndex][subIndex] == 1) {
		if (lightsOn == 2 || lightsOn == 3) {
			lights2[mainIndex][subIndex] = 1;
		} else {
			lights2[mainIndex][subIndex] = 0;
		}
	} else {
		if (lightsOn == 3) {
			lights2[mainIndex][subIndex] = 1;
		} else {
			lights2[mainIndex][subIndex] = 0;
		}
	}
	if ((mainIndex == 0 && (subIndex == 0 || subIndex == 99)) || (mainIndex == 99 && (subIndex == 0 || subIndex == 99))) {
		lights2[mainIndex][subIndex] = 1;
	}
}


void changeLight2(const unsigned __int32 mainIndex, const unsigned __int32 subIndex) {
	unsigned __int32 lightsOn = 0;
	//find information top bottom
	if (mainIndex == 0) {
		lightsOn += lights2[mainIndex + 1][subIndex];
	} else if (mainIndex == 99) {
		lightsOn += lights2[mainIndex - 1][subIndex];
	} else {
		lightsOn += lights2[mainIndex + 1][subIndex];
		lightsOn += lights2[mainIndex - 1][subIndex];
	}

	if (subIndex == 0) {
		lightsOn += lights2[mainIndex][subIndex + 1];
	} else if (subIndex == 99) {
		lightsOn += lights2[mainIndex][subIndex - 1];
	} else {
		lightsOn += lights2[mainIndex][subIndex + 1];
		lightsOn += lights2[mainIndex][subIndex - 1];
	}

	if (mainIndex == 0) {
		if (subIndex == 0) {
			lightsOn += lights2[mainIndex + 1][subIndex + 1];
		} else if (subIndex == 99) {
			lightsOn += lights2[mainIndex + 1][subIndex - 1];
		} else {
			lightsOn += lights2[mainIndex + 1][subIndex - 1];
			lightsOn += lights2[mainIndex + 1][subIndex + 1];
		}
	} else if (mainIndex == 99) {
		if (subIndex == 0) {
			lightsOn += lights2[mainIndex - 1][subIndex + 1];
		} else if (subIndex == 99) {
			lightsOn += lights2[mainIndex - 1][subIndex - 1];
		} else {
			lightsOn += lights2[mainIndex - 1][subIndex - 1];
			lightsOn += lights2[mainIndex - 1][subIndex + 1];
		}
	} else {
		if (subIndex == 0) {
			lightsOn += lights2[mainIndex - 1][subIndex + 1];
			lightsOn += lights2[mainIndex + 1][subIndex + 1];
		} else if (subIndex == 99) {
			lightsOn += lights2[mainIndex - 1][subIndex - 1];
			lightsOn += lights2[mainIndex + 1][subIndex - 1];
		} else {
			lightsOn += lights2[mainIndex + 1][subIndex + 1];
			lightsOn += lights2[mainIndex - 1][subIndex - 1];
			lightsOn += lights2[mainIndex - 1][subIndex + 1];
			lightsOn += lights2[mainIndex + 1][subIndex - 1];
		}
	}
	if (lights2[mainIndex][subIndex] == 1) {
		if (lightsOn == 2 || lightsOn == 3) {
			lights1[mainIndex][subIndex] = 1;
		} else {
			lights1[mainIndex][subIndex] = 0;
		}
	} else {
		if (lightsOn == 3) {
			lights1[mainIndex][subIndex] = 1;
		} else {
			lights1[mainIndex][subIndex] = 0;
		}
	}
	if ((mainIndex == 0 && (subIndex == 0 || subIndex == 99)) || (mainIndex == 99 && (subIndex == 0 || subIndex == 99))) {
		lights1[mainIndex][subIndex] = 1;
	}
	
}