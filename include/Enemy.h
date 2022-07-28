#pragma once

#include <vector>
#include <iostream>
#include <sstream>

struct Enemy {
    Enemy(std::string name, unsigned int attack, unsigned int defense, unsigned int health, unsigned int level, unsigned int gold)
        : name(name), attack(attack), defense(defense), health(health), level(level), gold(gold) {};
    void display_stats();
    unsigned int get_defense();
private:
    const std::string name;
    unsigned int attack;
    unsigned int defense;
    unsigned int health;
    unsigned int level;
    unsigned int gold;
};