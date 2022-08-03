#pragma once

#include <vector>

#include "Item.h"

struct Vendor {
    const std::string name;
    
    void buy_menu();
    void sell_menu();
    void remove_item(int item_location);

    virtual void generate_inventory();
private:
    std::vector<Item*> inventory;
};