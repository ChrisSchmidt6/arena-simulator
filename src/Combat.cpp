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
    if(is_focused()) temp_accuracy += accuracy;

    int hit_scale = opponent_defense - temp_accuracy;
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
};

bool Combat::is_defending() {
    return defending;
};

void Combat::toggle_focused() {
    focused = !focused;
};

void Combat::toggle_weakened() {
    weakened = !weakened;
};

bool Combat::is_focused() {
    return focused;
};

bool Combat::is_weakened() {
    return weakened;
};

void Combat::clear_cooldowns() {
    defending = false;
    focused = false;
    weakened = false;
};