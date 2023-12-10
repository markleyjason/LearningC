#include <stdlib.h>
#include <stdio.h>

main() {
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "input2023p8.txt", "r");

	if (!error) {

		fclose(fptr);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0;
}