#include <random>

#include "Combat.h"

Weapon* Combat::get_weapon() {
    // This shouldn't fail since only weapons will be stored in weapon_slot
    return static_cast<Weapon*>(weapon_slot);
};

bool Combat::is_alive() {
    return health > 0;
};

bool Combat::accuracy_roll(int opponent_defense) {
    std::random_device rd;
    std::mt19937 mt(rd());

    int temp_accuracy = accuracy;
    if(is_accurate()) temp_accuracy += accuracy;

    int hit_scale = temp_accuracy - opponent_defense;
    // hit_chance min is -12 and max is 12 (30% loss vs 30% gain)
    if(hit_scale < -15) hit_scale = -15;
    if(hit_scale > 15) hit_scale = 15;

    int hit_chance = 65 + (hit_scale * 2);
    std::uniform_int_distribution<int> hundred_dist(1, 100);
    if(hundred_dist(mt) <= hit_chance) return true;
    return false;
};

int Combat::damage_roll() {
    // (Attack stat + weapon modifier) / 2
    // Will likely be tweaked in the future
    int max_damage = (attack + get_weapon()->ATTACK_MOD) / 2;

    if(is_weakened()) max_damage /= 2;
    // Minimum damage of 1
    if(max_damage == 0) return 1;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dmg_dist(1, max_damage);
    return dmg_dist(mt);
};

void Combat::take_damage(int damage) {
    if(damage > health) health = 0;
    else health -= damage;
};

void Combat::toggle_defending() {
    defending = !defending;
    if(defending) defend_cooldown = true;
};

void Combat::clear_def_cooldown() {
    defend_cooldown = false;
};

bool Combat::is_defending() {
    return defending;
};

bool Combat::can_defend() {
    return !defend_cooldown;
};

void Combat::toggle_accurate() {
    accurate = !accurate;
};

void Combat::toggle_weakened() {
    weakened = !weakened;
};

bool Combat::is_accurate() {
    return accurate;
};

bool Combat::is_weakened() {
    return weakened;
};

void Combat::clear_cooldowns() {
    defend_cooldown = false;
    defending = false;
    accurate = false;
    weakened = false;
};