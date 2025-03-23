#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct stats {
	int16_t hp;
	int16_t damage;
	int16_t armor;
};

struct item {
	int16_t cost;
	int16_t damage;
	int16_t armor;
};

struct stats play_game(struct stats boss, FILE* fptr, struct stats player);

int advcal2015p21() {
	struct stats player = { .hp = 100, .damage = 0, .armor = 0 };
	struct stats boss = { .hp = 104, .damage = 8, .armor = 1 };
	int cost;
	int damage;
	int defence;
	int16_t attack = 1;
	FILE* fptr;
	FILE* ifptr;
	errno_t error;
	int16_t windex = 0;
	int16_t aindex = 0;
	int16_t rindex = 0;
	struct stats weapons[5];
	struct stats armor[5];
	struct stats ring[6];

	error = fopen_s(&fptr, "output2015p21.txt", "w+");
	if (error) {
		printf("Failed to open output file\n");
		return 0;
	}
	error = fopen_s(&ifptr, "input2015p21.txt", "r");
	if (error) {
		printf("Failed to open input file\n");
		return 0;
	}
	player.hp = 100;
	player.armor = 8;
	player.damage = 9;

	while (fscanf_s(ifptr, "%d %d %d", &cost, &damage, &defence) != EOF) {
		if (windex < 5) {
			weapons[windex].hp = cost;
			weapons[windex].damage = damage;
			windex++;
		} else if (aindex < 5) {
			armor[aindex].hp = cost;
			armor[aindex].armor = defence;
			aindex++;
		} else if (rindex < 6) {
			ring[rindex].hp = cost;
			ring[rindex].damage = damage;
			ring[rindex].armor = defence;
			rindex++;
		} else {
			printf("Too many lines dumbass\n");
			return 0;
		}
	}
	
	if (error) {
		printf("Failed to open output file\n");
		return 0;
	}
	for (windex = 0; windex < 5; windex++) {
		player.damage = weapons[windex].damage;
		player.armor = 0;
		play_game(boss, fptr, player);
		fprintf(fptr, "%i\n", weapons[windex].hp);
		for (aindex = 0; aindex < 5; aindex++) {
			player.armor = armor[aindex].armor;
			play_game(boss, fptr, player);
			fprintf(fptr, "%i\n", weapons[windex].hp + armor[aindex].hp);
			for (rindex = 0; rindex < 6; rindex++) {
				player.damage = weapons[windex].damage + ring[rindex].damage;
				player.armor = armor[aindex].armor + ring[rindex].armor;
				play_game(boss, fptr, player);
				fprintf(fptr, "%i\n", weapons[windex].hp + armor[aindex].hp + ring[rindex].hp);
				for (damage = rindex + 1; damage < 6; damage++) {
					player.damage = weapons[windex].damage + ring[rindex].damage + ring[damage].damage;
					player.armor = armor[aindex].armor + ring[rindex].armor + ring[damage].armor;
					play_game(boss, fptr, player);
					fprintf(fptr, "%i\n", weapons[windex].hp + armor[aindex].hp + ring[rindex].hp + ring[damage].hp);
				}
			}
		}
		for (rindex = 0; rindex < 6; rindex++) {
			player.damage = weapons[windex].damage + ring[rindex].damage;
			player.armor = ring[rindex].armor;
			play_game(boss, fptr, player);
			fprintf(fptr, "%i\n", weapons[windex].hp + ring[rindex].hp);
			for (damage = rindex + 1; damage < 6; damage++) {
				player.damage = weapons[windex].damage + ring[rindex].damage + ring[damage].damage;
				player.armor = ring[rindex].armor + ring[damage].armor;
				play_game(boss, fptr, player);
				fprintf(fptr, "%i\n", weapons[windex].hp + ring[rindex].hp + ring[damage].hp);
			}
		}
	}
	fclose(fptr);
	return 0;
}

struct stats play_game(struct stats boss, FILE* fptr, struct stats player) {
	struct stats ret = { 0 };
	int16_t attack = 1;
	boss.hp = 104;
	while (boss.hp > 0 && player.hp > 0) {
		attack = player.damage - boss.armor;
		if (attack < 1) {
			attack = 1;
		}
		boss.hp -= attack;
		attack = boss.damage - player.armor;
		if (attack < 1) {
			attack = 1;
		}
		player.hp -= attack;
	}
	if (boss.hp <= 0) {
		fprintf(fptr, "WIN: Player attack: %i, armor: %i cost: ", player.damage, player.armor);
		return player;
	} else {
		fprintf(fptr, "LOSE: Player attack: %i, armor: %i cost: ", player.damage, player.armor);
		return player;
	}
	return ret;
}