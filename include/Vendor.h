#pragma once

#include <vector>
#include <iostream>

#include "Player.h"
#include "Item.h"

struct Vendor {
    Vendor(std::string);
    void display_greeting();
    void buy_item();
    void sell_item();
    void remove_item(int);
private:
    std::string name;
    std::vector<Item*> inventory;
};