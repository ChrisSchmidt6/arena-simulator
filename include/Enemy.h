#pragma once

#include <iostream>
#include <string>

#include "Combat.h"
#include "Item.h"

struct Enemy : Combat {
    Enemy(std::string name, int max_health, int attack, int accuracy,
        int defense, int level, int experience_rewarded, int gold,
        int drop_weapon_chance, Item* weapon);

    std::string get_name() override;
    int get_stat(std::string stat) override;
    void display_stats() override;

    static Enemy generate_enemy(const int tier);
private:
    std::string name;
    int experience_rewarded;
    int drop_weapon_chance;
};