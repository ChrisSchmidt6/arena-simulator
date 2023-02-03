#pragma once

#include <iostream>

#include "Item.h"

struct Enemy {
    Enemy(std::string name, unsigned int max_health, unsigned int health,
        unsigned int attack, unsigned int accuracy, unsigned int defense,
        unsigned int level, unsigned int experience_rewarded,
        unsigned int gold, unsigned int drop_weapon_chance, Item* weapon):
        name(name), max_health(max_health), health(health),
        attack(attack), accuracy(accuracy), defense(defense),
        level(level), experience_rewarded(experience_rewarded),
        gold(gold), drop_weapon_chance(drop_weapon_chance), weapon(weapon) {};

    static Enemy generate_enemy(const unsigned int tier);
    void display_stats();
    unsigned int get_defense();
private:
    const std::string name;
    unsigned int max_health;
    unsigned int health;
    unsigned int attack;
    unsigned int accuracy;
    unsigned int defense;
    unsigned int level;
    unsigned int experience_rewarded;
    unsigned int gold;
    unsigned int drop_weapon_chance;
    Item* weapon;
};