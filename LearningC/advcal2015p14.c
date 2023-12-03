#include <stdlib.h>
#include <stdio.h>

enum deerState {
	MOVING,
	RESTING
};

typedef struct MoveRestCycle {
	char name[10];
	unsigned __int32 speed;
	unsigned __int32 movingTime;
	unsigned __int32 restingTime;
	unsigned __int32 stateStartTime;
	enum deerState state;
}MoveRestCycle;

adv2015p14() {
//main() {
	unsigned __int32 deerSize = 0;
	MoveRestCycle deerCycles[9];
	unsigned __int32 distances[9] = { 0 };
	unsigned __int32 points[9] = { 0 };
	FILE* fptr;
	errno_t error;
	unsigned __int32 time = 0;
	unsigned __int32 index = 0;
	unsigned __int32 winningDist = 0;
	unsigned __int32 winningInd = 0;

	error = fopen_s(&fptr, "input2015p14.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fscanf_s(fptr, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", deerCycles[index].name, 10, &deerCycles[index].speed, &deerCycles[index].movingTime, &deerCycles[index].restingTime) != EOF) {
			deerCycles[index].stateStartTime = 0;
			deerCycles[index].state = MOVING;
			index++;
			deerSize++;
		}
		fclose(fptr);
		for (time = 0; time < 2503; time++) {
			winningDist = 0;
			winningInd = 0;
			for (index = 0; index < deerSize; index++) {
				if (deerCycles[index].state == MOVING) {
					if ((time - deerCycles[index].stateStartTime) == deerCycles[index].movingTime) {
						deerCycles[index].state = RESTING;
						deerCycles[index].stateStartTime = time;
					} else {
						distances[index] += deerCycles[index].speed;
					}
				} else {
					if ((time - deerCycles[index].stateStartTime) == deerCycles[index].restingTime) {
						deerCycles[index].state = MOVING;
						deerCycles[index].stateStartTime = time;
						distances[index] += deerCycles[index].speed;
					}
				}
				if (winningDist < distances[index]) {
					winningDist = distances[index];
					winningInd = index;
				}
			}
			points[winningInd] += 1;
		}
	}
	for (index = 0; index < deerSize; index++) {
		printf("%s moved %d, earning %d points", deerCycles[index].name, distances[index], points[index]);
		if (deerCycles[index].state == MOVING) {
			printf(" state is MOVING\n");
		} else {
			printf(" state is RESTING\n");
		}
	}
}