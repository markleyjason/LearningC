#include <stdio.h>
#include "helper.h"

ad2015p2() {
	__int32 i;
	__int32 dims[3];
	__int32 sides[3];
	__int32 perm[3];
	__int32 minPerm;
	__int32 curDim = 0;
	__int32 minSide = 0;
	__int32 totalPaper = 0;
	__int32 totalRibbon = 0;
	FILE* fptr;
	__int32 buffer = 50;
	char line[50];

	char error = fopen_s(&fptr, "input2015p2.txt", "r");

	if (!error) {
		while(fgets(line, buffer, fptr) != NULL) {
			for (i = 0; i < 3; i++) {
				dims[i] = 0;
			}
			i = 0;
			if (line[i] != EOF) {
				curDim = 0;
				while (line[i] != '\n') {
					if (isDigit(line[i])) {
						dims[curDim] = dims[curDim] * 10 + ctoai(line[i]);
					}
					else {
						curDim++;
					}
					i++;
				}
				sides[0] = dims[0] * dims[1];
				sides[1] = dims[0] * dims[2];
				sides[2] = dims[1] * dims[2];

				minSide = findMin(sides, 3);

				perm[0] = 2 * dims[0] + 2 * dims[1];
				perm[1] = 2 * dims[0] + 2 * dims[2];
				perm[2] = 2 * dims[1] + 2 * dims[2];

				minPerm = findMin(perm, 3);

				totalPaper += 2 * (sides[0] + sides[1] + sides[2]) + minSide;

				printf("Volume cal: %d\n", findVolumeA(dims));
				totalRibbon += findVolumeA(dims) + minPerm;
			}
		}
		fclose(fptr);
	}
	printf("Total paper needed is: %d\n", totalPaper);
	printf("Total ribbon needed is: %d\n", totalRibbon);
}