#pragma once

#include <string>
#include <unordered_map>

struct Item {
    const unsigned int ID;
    const std::string ITEM_NAME;
    
    Item(unsigned int id, std::string item_name, unsigned int price) : ID(id), ITEM_NAME(item_name), price(price) {};
    unsigned int get_price();
private:
    unsigned int price;
};

inline std::unordered_map<unsigned int, Item> items = {
    {000, Item(
        000,
        "Bjarne Stroustrup Action Figure",
        0
    )},
    {201, Item(
        201,
        "Wooden Dagger",
        10
    )},
    {202, Item(
        202,
        "Wooden Spear",
        12
    )},
    {203, Item(
        203,
        "Wooden Sword",
        12
    )},
    {204, Item(
        204,
        "Wooden Mace",
        12
    )},
};

inline Item* get_item(const unsigned int ID) {
    return items.find(ID) == items.end() ? &items.at(0) : &items.at(ID);
};