#pragma once

#include "Combat.h"
#include "Player.h"
#include "Enemy.h"

struct Arena {
    void main_menu();
    void fight_menu();
    void train_menu();
    void pre_round_checks(Combat &fighter);
    void process_attack(Combat &attacker, Combat &defender);
private:
    Combat &player = Player::get();
    Enemy enemy = Enemy::generate_enemy(Player::get().get_stat("Level"));;
};