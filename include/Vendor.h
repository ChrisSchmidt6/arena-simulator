#pragma once

#include <vector>
#include <iostream>

#include "Player.h"
#include "Item.h"

struct Vendor {
    const std::string name;
    
    void buy_menu();
    void sell_menu();
    void remove_item(int);

    virtual void display_greeting() const;
    virtual void generate_inventory();
private:
    std::vector<Item*> inventory;
};