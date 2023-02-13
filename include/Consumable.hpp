#pragma once

#include "Item.hpp"

struct Consumable : Item {
    const int ATTACK_MOD;
    const int ACCURACY_MOD;
    const int DEFENSE_MOD;
    const int HEALTH_REGEN;

    Consumable(int id, std::string item_name, VenType type,
        int price, int tier, Rarity rarity, bool can_drop,
        int attack_mod, int accuracy_mod,
        int defense_mod, int health_regen): 
        Item(id, item_name, type, price, tier, rarity, can_drop),
        ATTACK_MOD{attack_mod}, ACCURACY_MOD(accuracy_mod),
        DEFENSE_MOD(defense_mod), HEALTH_REGEN(health_regen) {};
    
    void display_item_options() override;
};