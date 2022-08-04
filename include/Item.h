#pragma once

#include <string>

enum class Rarity { Common, Uncommon, Rare, Mythic };
enum class VenType { None, Apothecary, Blacksmith, Chef };

struct Item {
    const unsigned int ID;
    const std::string ITEM_NAME;
    const VenType TYPE;
    const unsigned int PRICE;
    const unsigned int TIER;
    const Rarity RARITY;
    const bool CAN_DROP;

    Item(unsigned int id, std::string item_name, VenType type,
        unsigned int price, unsigned int tier, Rarity rarity,
        bool can_drop):
        ID(id), ITEM_NAME(item_name), TYPE(type), PRICE(price),
        TIER(tier), RARITY(rarity), CAN_DROP(can_drop) {};

    virtual void display_item_options() {};
};