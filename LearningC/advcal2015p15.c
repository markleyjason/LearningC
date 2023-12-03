#include <stdio.h>
#include <stdlib.h>

#define MAX_TEASPOONS 100
#define NAME_LENGTH 50
#define MAX_NUM_INGRE 10

typedef struct ingredientProperty {
	char name[NAME_LENGTH];
	__int32 capacity;
	__int32 durability;
	__int32 flavor;
	__int32 texture;
	__int32 calories;
}ingredientProperty;

adv2015p15() {
//main() {
	ingredientProperty ingredients[MAX_NUM_INGRE];
	unsigned __int32 numIngredients = 0;
	unsigned __int32 index = 0;
	unsigned __int32 ingreAmount[MAX_NUM_INGRE] = { 0 };
	unsigned __int32 movingIndex = 0;
	unsigned __int32 lastNumberIndex = 0;
	unsigned __int32 startingIndex = 0;
	__int32 capacity;
	__int32 durability;
	__int32 flavor;
	__int32 texture;
	__int32 calories;
	__int32 max = INT_MIN;
	__int32 tempMax;
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "input2015p15.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fscanf_s(fptr, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d", ingredients[index].name, NAME_LENGTH, &ingredients[index].capacity, &ingredients[index].durability,
			&ingredients[index].flavor, &ingredients[index].texture, &ingredients[index].calories) != EOF) {
			index++;
			numIngredients++;
		}
		fclose(fptr);
		//do calculations finding max
		ingreAmount[0] = MAX_TEASPOONS;
		if (numIngredients < MAX_NUM_INGRE && numIngredients > 0) {
			while (ingreAmount[numIngredients - 1] < MAX_TEASPOONS) {
				//calculate it
				capacity = 0;
				durability = 0;
				flavor = 0;
				texture = 0;
				calories = 0;
				for (index = 0; index < numIngredients; index++) {
					capacity += ingredients[index].capacity * ingreAmount[index];
					durability += ingredients[index].durability * ingreAmount[index];
					flavor += ingredients[index].flavor * ingreAmount[index];
					texture += ingredients[index].texture * ingreAmount[index];
					calories += ingredients[index].calories * ingreAmount[index];
				}
				if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0 || calories != 500) {
					tempMax = 0;
				} else {
					tempMax = capacity * durability * flavor * texture;
				}
				if (tempMax > max) {
					max = tempMax;
				}

				movingIndex++;
				if (movingIndex == numIngredients) {
					movingIndex = lastNumberIndex + 1;
					ingreAmount[movingIndex] = 1 + ingreAmount[numIngredients - 1];
					ingreAmount[lastNumberIndex]--;
					lastNumberIndex = movingIndex;
					if (lastNumberIndex == numIngredients - 1) {
						for (index = 0; index < movingIndex; index++) {
							if (ingreAmount[index] > 0) {
								lastNumberIndex = index;
							}
						}
					} else {
						ingreAmount[numIngredients - 1] = 0;
					}
				} else {
					ingreAmount[movingIndex] = 1;
					ingreAmount[movingIndex - 1]--;
				}
			}
		} else {
			printf("ERROR: too many ingredients provided or not enough.\n");
		}
		printf("Top score is: %d\n", max);
	}
}