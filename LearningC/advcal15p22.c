#include <stdint.h>
#include <stdio.h>

struct m_stats {
	int16_t health;
	int16_t damage;
	int16_t armor;
	int16_t mana;
};

struct game_state {
	int16_t shield_turns;
	int16_t poison_turns;
	int16_t recharge_turns;
	int32_t mana;
};

int32_t lowest = INT32_MAX;

void play_games(struct m_stats boss, struct m_stats player, struct game_state game);
void boss_turn(struct m_stats boss, struct m_stats player, struct game_state game);
void play_games_hard(struct m_stats boss, struct m_stats player, struct game_state game);
void boss_turn_hard(struct m_stats boss, struct m_stats player, struct game_state game);
void timers(struct m_stats* boss, struct m_stats* player, struct game_state* game);
void check_low(int32_t mana);

int main() {
	struct m_stats boss = { .health = 71, .damage = 10, .armor = 0, .mana = 0 };
	struct m_stats player = { .health = 50, .mana = 500, .armor = 0, .damage = 0 };
	//struct m_stats boss = { .health = 13, .damage = 8, .armor = 0, .mana = 0 };
	//struct m_stats player = { .health = 10, .mana = 250, .armor = 0, .damage = 0 };
	struct game_state game = { 0 };

	play_games(boss, player, game);

	printf("Lowest mana use: %lu\n", lowest);
	
	lowest = INT32_MAX;
	play_games_hard(boss, player, game);

	printf("Lowest mana use hard: %lu\n", lowest);


	return 0;
}

void play_games(struct m_stats boss, struct m_stats player, struct game_state game) {
	//attacks
	
	timers(&boss, &player, &game);
	if (boss.health <= 0) {
		check_low(game.mana);
		return;
	}
	if (player.mana < 53) {
		return;
	}
	if (player.mana >= 53) {
		game.mana += 53;
		boss.health -= 4;
		player.mana -= 53;
		boss_turn(boss, player, game);
		boss.health += 4;
		game.mana -= 53;
		player.mana += 53;
	}
	if (player.mana >= 73) {
		game.mana += 73;
		boss.health -= 2;
		player.mana -= 73;
		player.health += 2;
		boss_turn(boss, player, game);
		boss.health += 2;
		game.mana -= 73;
		player.mana += 73;
		player.health -= 2;
	}
	if (player.mana >= 113 && game.shield_turns == 0) {
		game.mana += 113;
		player.mana -= 113;
		player.armor += 7;
		game.shield_turns = 6;
		boss_turn(boss, player, game);
		game.mana -= 113;
		player.mana += 113;
		player.armor -= 7;
		game.shield_turns = 0;
	}
	if (player.mana >= 173 && game.poison_turns == 0) {
		game.mana += 173;
		player.mana -= 173;
		game.poison_turns = 6;
		boss_turn(boss, player, game);
		game.mana -= 173;
		player.mana += 173;
		game.poison_turns = 0;
	}
	if (player.mana >= 229 && game.recharge_turns == 0) {
		game.mana += 229;
		player.mana -= 229;
		game.recharge_turns = 5;
		boss_turn(boss, player, game);
		game.mana -= 229;
		player.mana += 229;
		game.shield_turns = 0;
	}
}

void boss_turn(struct m_stats boss, struct m_stats player, struct game_state game) {

	timers(&boss, &player, &game);
	if (boss.health == 0) {
		check_low(game.mana);
		return;
	}

	player.health -= boss.damage - player.armor;
	if (player.health > 0) {
		play_games(boss, player, game);
	}
}

void timers(struct m_stats* boss, struct m_stats* player, struct game_state* game) {
	if (game->poison_turns > 0) {
		boss->health -= 3;
		game->poison_turns--;
	}
	if (game->recharge_turns > 0) {
		player->mana += 101;
		game->recharge_turns--;
	}
	if (game->shield_turns > 0) {
		game->shield_turns--;
		if (game->shield_turns == 0) {
			player->armor = 0;
		}
	}
}

void check_low(int32_t mana) {
	if (mana < lowest) {
		lowest = mana;
		printf("Lowest Changed: %lu\n", lowest);
	}
}

void play_games_hard(struct m_stats boss, struct m_stats player, struct game_state game) {
	//attacks
	player.health--;
	if (player.health == 0) {
		return;
	}

	timers(&boss, &player, &game);
	if (boss.health <= 0) {
		check_low(game.mana);
		return;
	}
	if (player.mana < 53) {
		return;
	}
	if (player.mana >= 53) {
		game.mana += 53;
		boss.health -= 4;
		player.mana -= 53;
		boss_turn_hard(boss, player, game);
		boss.health += 4;
		game.mana -= 53;
		player.mana += 53;
	}
	if (player.mana >= 73) {
		game.mana += 73;
		boss.health -= 2;
		player.mana -= 73;
		player.health += 2;
		boss_turn_hard(boss, player, game);
		boss.health += 2;
		game.mana -= 73;
		player.mana += 73;
		player.health -= 2;
	}
	if (player.mana >= 113 && game.shield_turns == 0) {
		game.mana += 113;
		player.mana -= 113;
		player.armor += 7;
		game.shield_turns = 6;
		boss_turn_hard(boss, player, game);
		game.mana -= 113;
		player.mana += 113;
		player.armor -= 7;
		game.shield_turns = 0;
	}
	if (player.mana >= 173 && game.poison_turns == 0) {
		game.mana += 173;
		player.mana -= 173;
		game.poison_turns = 6;
		boss_turn_hard(boss, player, game);
		game.mana -= 173;
		player.mana += 173;
		game.poison_turns = 0;
	}
	if (player.mana >= 229 && game.recharge_turns == 0) {
		game.mana += 229;
		player.mana -= 229;
		game.recharge_turns = 5;
		boss_turn_hard(boss, player, game);
		game.mana -= 229;
		player.mana += 229;
		game.shield_turns = 0;
	}
}

void boss_turn_hard(struct m_stats boss, struct m_stats player, struct game_state game) {

	timers(&boss, &player, &game);
	if (boss.health == 0) {
		check_low(game.mana);
		return;
	}

	player.health -= boss.damage - player.armor;
	if (player.health > 0) {
		play_games_hard(boss, player, game);
	}
}