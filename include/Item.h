#pragma once

#include <string>

enum class Rarity { Common, Uncommon, Rare, Mythic };

struct Item {
    const unsigned int ID;
    const std::string ITEM_NAME;
    const unsigned int PRICE;
    const unsigned int TIER;
    const Rarity RARITY;
    const bool CAN_DROP;
    const bool VENDOR_ITEM;

    Item(unsigned int id, std::string item_name, unsigned int price,
        unsigned int tier, Rarity rarity, bool can_drop, bool vendor_item):
        ID(id), ITEM_NAME(item_name), PRICE(price), TIER(tier),
        RARITY(rarity), CAN_DROP(can_drop), VENDOR_ITEM(vendor_item) {};

    virtual void display_item_options() {};
};