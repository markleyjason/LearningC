#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int advcal15p20() {
	int32_t index = 1;
	int32_t count = 0;
	int32_t currentHouse = 665279;
	
	while (count < 29000000) {
		currentHouse++;
		count = 0;
		index = 1;
		count = currentHouse * 10;
		while (index < currentHouse) {
			if (currentHouse % index == 0) {
				count += index * 10;
			}
			index++;
		}
		
	}
	printf("Houses: %i with: %i\n", currentHouse, count);
	count = 0;
	currentHouse = 10000;
	while (count < 29000000) {
		index = 1;
		currentHouse++;
		count = 0;
		count = currentHouse * 11;
		while (index < currentHouse) {
			if (index * 50 >= currentHouse) {
				if (currentHouse % index == 0) {
					count += index * 11;
				}
			}
			index++;
		}
		printf("House %i, Count: %i\n", currentHouse, count);
	}
	printf("Houses: %i with: %i\n", currentHouse, count);
	return 0;
}