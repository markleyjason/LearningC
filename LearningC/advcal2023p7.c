#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "helper.h"

#define LINEBUFFER 15

typedef struct Hand {
	char cards[6];
	int16_t bet;
	char has5;
	char has4;
	char fullHouse;
	char has3;
	char has2P;
	char hasP;
}AdvHand;

static void setWinnings(AdvHand* newHand);
static void insert(int16_t size, AdvHand newHand);
static int16_t compareHands(const AdvHand first, const AdvHand second);
static int16_t compareCards(const char first, const char second);

static AdvHand hands[1000];

adv2023p7() {
//int main() {
	FILE* fptr;
	errno_t error;
	int16_t handCount = 0;
	AdvHand tempHand = { .bet = 0, .cards = { '\0' } };
	char* token = NULL;
	char* nextTok = NULL;
	char line[LINEBUFFER] = { '\0' };
	uint32_t total = 0;
	int16_t index = 0;
	
	
	error = fopen_s(&fptr, "input2023p7.txt", "r");
	//error = fopen_s(&fptr, "testing_input.txt", "r");

	if (!error) {
		while (fgets(line, LINEBUFFER, fptr) != NULL) {
			token = strtok_s(line, " \n", &nextTok);
			tempHand.cards[0] = token[0];
			tempHand.cards[1] = token[1];
			tempHand.cards[2] = token[2];
			tempHand.cards[3] = token[3];
			tempHand.cards[4] = token[4];
			tempHand.cards[5] = token[5];
			token = strtok_s(NULL, " \n", &nextTok);
			tempHand.bet = stoai(token);
			setWinnings(&tempHand);
			insert(handCount, tempHand);
			handCount++;
			nextTok = NULL;
			token = NULL;
		}
		fclose(fptr);
		for (index = 0; index < handCount; index++) {
			total += (handCount - index) * hands[index].bet;
		}
		printf("Total: %d\n", total);
	} else {
		printf("Failed to open file\n");
		return -1;
	}
	return 0
}

static void setWinnings(AdvHand* newHand) {
	uint16_t counts[13] = { 0 };
	uint16_t index = 0;
	char have3 = 0;
	char have2 = 0;
	for (index = 0; index < 5; index++) {
		switch (newHand->cards[index]) {
		case 'A':
			counts[0]++;
			break;
		case 'K':
			counts[1]++;
			break;
		case 'Q':
			counts[2]++;
			break;
		case 'J':
			counts[12]++;
			break;
		case 'T':
			counts[3]++;
			break;
		case '9':
			counts[4]++;
			break;
		case '8':
			counts[5]++;
			break;
		case '7':
			counts[6]++;
			break;
		case '6':
			counts[7]++;
			break;
		case '5':
			counts[8]++;
			break;
		case '4':
			counts[9]++;
			break;
		case '3':
			counts[10]++;
			break;
		case '2':
			counts[11]++;
			break;
		}
	}

	for (index = 0; index < 12; index++) {
		if (counts[index] + counts[12] == 5) {
			newHand->has5 = 1;
			newHand->has4 = 0;
			newHand->fullHouse = 0;
			newHand->has3 = 0;
			newHand->has2P = 0;
			newHand->hasP = 0;
			return;
		} else if (counts[index] > 0 && counts[index] + counts[12] == 4) {
			newHand->has5 = 0;
			newHand->has4 = 1;
			newHand->fullHouse = 0;
			newHand->has3 = 0;
			newHand->has2P = 0;
			newHand->hasP = 0;
			return;
		} else if (counts[index] > 0 && counts[index] + counts[12] == 3) {
			have3++;
		} else if (counts[index] == 2) {
			have2++;
		}
	}
	if (have3 == 1 && have2 == 1 || (have3 == 2 && counts[12] == 1)) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 1;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if (have3 == 1 || have3 == 3) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 1;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if (have2 == 2) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 1;
		newHand->hasP = 0;
	} else if (have2 == 1 || counts[12] == 1) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 1;
	} else {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	}
}

static void setWinningsP1(AdvHand* newHand) {
	int16_t index = 0;
	char has = 1;
	char firstT = newHand->cards[0];
	int16_t firstCount = 0;
	char secondT = newHand->cards[1];
	int16_t secondCount = 0;
	char thirdT = newHand->cards[2];
	int16_t thirdCount = 0;
	char fourthT = newHand->cards[3];
	int16_t fourthCount = 0;
	char fifthT = newHand->cards[4];
	int16_t fifthCount = 0;
	for (index = 0; index < 5; index++) {
		if (firstT == newHand->cards[index]) {
			firstCount++;
		} else if (secondT == newHand->cards[index]) {
			secondCount++;
		} else if (thirdT == newHand->cards[index]) {
			thirdCount++;
		} else if (fourthT == newHand->cards[index]) {
			fourthCount++;
		} else if (fifthT == newHand->cards[index]) {
			fifthCount++;
		}
	}
	if (firstCount == 5) {
		newHand->has5 = 1;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if (firstCount == 4 || secondCount == 4) {
		newHand->has5 = 0;
		newHand->has4 = 1;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if ((firstCount == 2 && secondCount == 3) || (firstCount == 3 && secondCount == 2) || (firstCount == 3 && thirdCount == 2) || (firstCount == 2 && thirdCount == 3) || (firstCount == 3 && fourthCount == 2) || (firstCount == 2 && fourthCount == 3)) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 1;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if (firstCount == 3 || secondCount == 3 || thirdCount == 3) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 1;
		newHand->has2P = 0;
		newHand->hasP = 0;
	} else if ((firstCount == 2 && secondCount == 2) || (firstCount == 2 && thirdCount == 2) || (firstCount == 2 && fourthCount == 2) || (secondCount == 2 && thirdCount == 2) || (secondCount == 2 && fourthCount == 2)) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 1;
		newHand->hasP = 0;
	} else if (firstCount > 1 || secondCount > 1 || thirdCount > 1 || fourthCount > 1) {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 1;
	} else {
		newHand->has5 = 0;
		newHand->has4 = 0;
		newHand->fullHouse = 0;
		newHand->has3 = 0;
		newHand->has2P = 0;
		newHand->hasP = 0;
	}
}

static void insert(int16_t size, AdvHand newHand) {
	int16_t index = 0;
	AdvHand tempHand = { .bet = 0, .cards = { '\0' } };
	AdvHand tempHand2 = { .bet = 0, .cards = { '\0' } };
	char inserted = 0;	

	while (index < size && inserted == 0) {
		if (compareHands(newHand, hands[index]) > 0) {
			inserted = 1;
			tempHand = hands[index];
			hands[index] = newHand;
		}
		index++;
	}
	if (inserted == 0) {
		hands[index] = newHand;
	} else {
		while (index < size) {
			tempHand2 = hands[index];
			hands[index] = tempHand;
			tempHand = tempHand2;
			index++;
		}
		hands[index] = tempHand;
	}
}

static int16_t compareHands(const AdvHand first, const AdvHand second) {
	int16_t index = 0;
	int16_t sIndex = 0;
	int16_t highestCard = 0;

	while (highestCard == 0) {
		highestCard = compareCards(first.cards[index], second.cards[sIndex]);
		index++;
		sIndex++;
	}
	
	if (first.has5 == 1) {
		if (second.has5 == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.has5 == 1) {
		return -1;
	}

	if (first.has4 == 1) {
		if (second.has4 == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.has4 == 1) {
		return -1;
	}

	if (first.fullHouse == 1) {
		if (second.fullHouse == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.fullHouse == 1) {
		return -1;
	}

	if (first.has3 == 1) {
		if (second.has3 == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.has3 == 1) {
		return -1;
	}
	if (first.has2P == 1) {
		if (second.has2P == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.has2P == 1) {
		return -1;
	}

	if (first.hasP == 1) {
		if (second.hasP == 1) {
			return highestCard;
		}
		return 1;
	} else if (second.hasP == 1) {
		return -1;
	}
	
	return highestCard;
}

static int16_t compareCards(const char first, const char second) {
	if (first == second) {
		return 0;
	}
	if (first == 'J') {
		return -1;
	} else if (second == 'J') {
		return 1;
	}
	if (first == 'A') {
		return 1;
	}
	if (second == 'A') {
		return -1;
	}
	if (first == 'K') {
		return 1;
	}
	if (second == 'K') {
		return -1;
	}
	if (first == 'Q') {
		return 1;
	}
	if (second == 'Q') {
		return -1;
	}
	if (first == 'T') {
		return 1;
	}
	if (second == 'T') {
		return -1;
	}
	if (first > second) {
		return 1;
	} else {
		return -1;
	}
}

static int16_t compareCardsP1(const char first, const char second) {
	if (first == second) {
		return 0;
	}
	if (first == 'A') {
		return 1;
	}
	if (second == 'A') {
		return -1;
	}
	if (first == 'K') {
		return 1;
	}
	if (second == 'K') {
		return -1;
	}
	if (first == 'J') {
		return 1;
	} else if (second == 'J') {
		return -1;
	}
	if (first == 'Q') {
		return 1;
	}
	if (second == 'Q') {
		return -1;
	}
	if (first == 'T') {
		return 1;
	}
	if (second == 'T') {
		return -1;
	}
	if (first > second) {
		return 1;
	} else {
		return -1;
	}
}