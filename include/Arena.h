#pragma once

#include "Combat.h"
#include "Player.h"
#include "Enemy.h"

struct Arena {
    void main_menu();
private:
    // Some choices in fight/train menu should not cause a new move to be rolled
    // This will also prevent pre_round_checks from running unnecessarily
    // for the enemy
    bool continue_round = false;
    Player &player = Player::get();
    Enemy enemy = Enemy::generate_enemy(Player::get().get_stat("Level"));

    void fight_menu(bool safe_death = false);
    void train_menu();
    void pre_round_checks(Combat &fighter);
    void process_attack(Combat &attacker, Combat &defender);
    void print_stats();
    void consumables_menu();
    void player_death(bool training = false);
    void enemy_death(bool training = false);
};