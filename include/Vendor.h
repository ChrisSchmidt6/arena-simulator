#pragma once

#include <vector>

#include "Item.h"

struct Vendor {
    const std::string NAME;
    const unsigned int TIER;
    const VenType TYPE;

    Vendor(std::string name, unsigned int tier, VenType type);
    
    static void main_menu(Vendor& apothecary, Vendor& blacksmith, Vendor& chef);

    void buy_menu();
    void sell_menu();
    void remove_item(int item_location);

    void generate_inventory();
protected:
    std::vector<Item*> inventory;
};