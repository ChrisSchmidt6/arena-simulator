#pragma once

#include <vector>
#include <iostream>

#include "Player.h"
#include "Item.h"

struct Vendor {
    Vendor(std::string);
    void display_greeting();
    void buy_menu();
    void sell_menu();
    void remove_item(int);
private:
    std::string name;
    std::vector<Item*> inventory;
};