#include <stdio.h>



 static void adv2015p1() {
	 int floor = 0;
	 int position = 1;
	 FILE* fptr;
	 char c;

	 char error = fopen_s(&fptr, "input2015p1.txt", "r");
	 if (fptr != NULL) {
		 c = (char)fgetc(fptr);
		 while (c != EOF) {
			 if (c == '(') {
				 floor++;
			 }
			 else {
				 floor--;
			 }
			 if (floor == -1) {
				 printf("He entered the basement at position: %d\n", position);
			 }
			 position++;
			 c = (char)fgetc(fptr);
		 }
		 fclose(fptr);
	 }
	 printf("Final floor is %d\n", floor);
}