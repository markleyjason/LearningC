#include <stdlib.h>
#include <stdio.h>

#define EGGNOG 150
static void adv2015p17();

static void adv2015p17(){
//main() {
	unsigned __int32 bottles[20] = { 0 };
	unsigned char beingUsed[20] = { '0' };
	unsigned __int32 stackPointer = 0;
	unsigned __int32 movingInts[20] = { 0 };
	unsigned __int32 lastOnePosition[20] = { 0 };
	FILE* fptr;
	errno_t error;
	unsigned __int32 index = 0;
	unsigned __int32 numCombinations = 0;
	unsigned __int32 numBottles = 0;
	unsigned __int32 numOnes = 1;
	unsigned __int32 curMov = 0;
	unsigned __int32 curLiters = 0;
	unsigned __int32 minBots = 0;

	error = fopen_s(&fptr, "input2015p17.txt", "r");

	if (!error) {
		while (fscanf_s(fptr, "%d", &bottles[index]) != EOF) {
			index++;
		}
		fclose(fptr);
		numBottles = index;
		
		//stack pointer needs to equal the number of ones - 1;
		beingUsed[0] = 1;
		movingInts[0] = 1;
		lastOnePosition[0] = 1;
		curMov = 0;
		while (numOnes < numBottles) {
			//calculate
			curLiters = 0;
			/*for (index = 0; index < numBottles; index++) {
				printf("%d, ", beingUsed[index]);
			}
			printf("\n");*/
			for (index = 0; index < numBottles; index++) {
				if (beingUsed[index] == 1) {
					curLiters += bottles[index];
				}
			}
			if (curLiters == EGGNOG) {
				if (numCombinations == 0) {
					numCombinations++;
					minBots = numOnes;
				} else if(minBots == numOnes) {
					numCombinations++;
				} else {
					break;
				}
			}
			//make next combination
			//thinking about this "wrong" when I reach the end I need to keep popping of the stack till it is done then I need to add the stack back so for 1 0 1 1 0 1 I have 4,3,2,1 on the stack pop off 1 moving two giving 1 0 1 0 1 1 then pop off 3
			//so it should be if stackPointer != 0 then pop otherwise i need to add them back (call the functions)
			if (curMov == numBottles - 1) {
				if (stackPointer == 0) { //reset point
					numOnes++;
					for (index = 0; index < numOnes; index++) {
						beingUsed[index] = 1;
						movingInts[index] = numOnes - index;
						lastOnePosition[index] = index;
					}
					stackPointer = index - 1;
					curMov = index - 1;
					for (; index < numBottles; index++) {
						beingUsed[index] = 0;
					}
				} else {
					//clean up
					for (index = numBottles - 1; numBottles - 1 - index < movingInts[stackPointer]; index--) {
						beingUsed[index] = 0;
					}
					//pop to get the information
					stackPointer--;
					beingUsed[lastOnePosition[stackPointer]] = 0;
					lastOnePosition[stackPointer]++;
					//set up to check if we are at the base case (end of the line) or need to make another call (push to the stack
					for (index = lastOnePosition[stackPointer]; index - lastOnePosition[stackPointer] < movingInts[stackPointer]; index++) {
						beingUsed[index] = 1;
					}
					curMov = index - 1;
					while (curMov != numBottles - 1 && movingInts[stackPointer] > 1) {
						stackPointer++;
						movingInts[stackPointer] = numOnes - stackPointer;
						lastOnePosition[stackPointer] = lastOnePosition[stackPointer - 1] + 1;
					}
				}

			} else {
				beingUsed[curMov] = 0;
				curMov++;
				beingUsed[curMov] = 1;
			}
		}
		printf("Number of combinations: %d\n", numCombinations);
	}
}
