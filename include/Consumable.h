#pragma once

#include "Item.h"

struct Consumable : Item {
    const unsigned int ATTACK_MOD;
    const unsigned int DEFENSE_MOD;
    const unsigned int HEALTH_REGEN;

    Consumable(unsigned int id, std::string item_name, VenType type,
        unsigned int price, unsigned int tier, Rarity rarity, bool can_drop,
        unsigned int attack_mod, unsigned int defense_mod,
        unsigned int health_regen): 
        Item(id, item_name, type, price, tier, rarity, can_drop),
        ATTACK_MOD{attack_mod}, DEFENSE_MOD(defense_mod),
        HEALTH_REGEN(health_regen) {};
    
    void display_item_options() override;
};