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

    static Enemy generate_enemy(const int TIER);
    int gold_reward();
    bool weapon_reward();
    int experience_reward();
private:
    std::string name;
    int experience_rewarded;
    int drop_weapon_chance;

    static constexpr double XP_MOD = 1.5;
    static const int GOLD_MIN_BASE = 5;
    static const int GOLD_MAX_BASE = 10;
    static constexpr double GOLD_MIN_MOD = 1.5;
    static constexpr double GOLD_MAX_MOD = 2;
};