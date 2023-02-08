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
    bool is_alive();

    bool accuracy_roll(int opponent_defense);
    int damage_roll();
    void take_damage(int damage);

    void toggle_defending();
    bool is_defending();
    void toggle_focused();
    void toggle_weakened();
    bool is_focused();
    bool is_weakened();
    void clear_cooldowns();
protected:
    Combat() {};
    virtual ~Combat() {};

    int max_health = 10;
    int health = 10;
    int attack = 1;
    int accuracy = 1;
    int defense = 1;
    int level = 1;
    int gold = 10;
    Item* weapon_slot = get_item(200);
private:
    bool defending = false;
    bool weakened = false;
    bool focused = false;
};