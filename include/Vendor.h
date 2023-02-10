#pragma once

#include <vector>
#include <string>

#include "Item.h"

struct Vendor {
    const VenType TYPE;

    Vendor(VenType type);
    
    static void main_menu(Vendor& apothecary, Vendor& blacksmith, Vendor& chef);

    void business_menu();
    void buy_menu();
    void sell_menu();
    void remove_item(int item_location);

    void generate_inventory();
protected:
    std::vector<Item*> inventory;
    std::string vendor_type;
    const double SALE_PERCENT = 0.7;
};