#pragma once

#include "Combat.h"

void arena_menu();
void arena_fight();
void arena_pre_round_checks(Combat &fighter);
void arena_attack(Combat &attacker, Combat &defender);
void arena_focused_attack(Combat &attacker, Combat &defender);
void arena_enemy_turn(int move, Combat &fighter);
void arena_train();