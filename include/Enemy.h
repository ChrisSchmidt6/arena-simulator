#pragma once

#include <iostream>

#include "Weapon.h"

struct Enemy {
    Enemy(std::string name, unsigned int attack, unsigned int defense, unsigned int health,
        unsigned int level, unsigned int gold, Weapon weapon):
        name(name), attack(attack), defense(defense), health(health),
        level(level), gold(gold), weapon(weapon) {};

    static void generate_enemy();
    void display_stats();
    unsigned int get_defense();
private:
    const std::string name;
    unsigned int attack;
    unsigned int defense;
    unsigned int health;
    unsigned int level;
    unsigned int gold;
    Weapon weapon;
};