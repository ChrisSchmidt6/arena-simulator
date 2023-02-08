#pragma once

#include <string>

#include "Item.h"
#include "Weapon.h"
#include "assets.h"

struct Combat {
    virtual std::string get_name() = 0;
    virtual int get_stat(std::string stat) = 0;
    virtual void display_stats() = 0;
    
    Weapon* get_weapon();
    int get_boost(std::string stat);
    bool is_alive();

    bool accuracy_roll(int opponent_defense);
    int damage_roll();
    void take_damage(int damage);

    void toggle_defending();
    void clear_def_cooldown();
    bool is_defending();
    bool can_defend();
    void toggle_accurate();
    void toggle_weakened();
    bool is_accurate();
    bool is_weakened();
    void reset_temps();
protected:
    Combat() {};
    virtual ~Combat() {};

    int max_health = 10;
    int health = 10;
    int attack = 1;
    int accuracy = 1;
    int defense = 1;
    int level = 1;
    int gold = 20;
    Item* weapon_slot = get_item(200);

    int att_boost = 0;
    int acc_boost = 0;
    int def_boost = 0;
private:
    bool defend_cooldown = false;
    bool defending = false;
    bool weakened = false;
    bool accurate = false;
};