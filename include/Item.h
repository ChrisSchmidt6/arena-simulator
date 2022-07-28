#pragma once

#include <string>
#include <unordered_map>

enum class Rarity { Common, Uncommon, Rare, Mythic };

struct Item {
    const unsigned int ID;
    const std::string ITEM_NAME;
    const unsigned int price;
    const unsigned int tier;
    const Rarity rarity;
    const bool can_drop;
    const bool vendor_item;

    virtual void display_item_options();
};

// inline std::unordered_map<unsigned int, Item> items = {
//     {000, Item(
//         000,
//         "Bjarne Stroustrup Action Figure",
//         0
//     )},
//     {201, Item(
//         201,
//         "Wooden Dagger",
//         10
//     )},
//     {202, Item(
//         202,
//         "Wooden Spear",
//         12
//     )},
//     {203, Item(
//         203,
//         "Wooden Sword",
//         12
//     )},
//     {204, Item(
//         204,
//         "Wooden Mace",
//         12
//     )},
// };

// inline Item* get_item(const unsigned int ID) {
//     return items.find(ID) == items.end() ? &items.at(0) : &items.at(ID);
// };