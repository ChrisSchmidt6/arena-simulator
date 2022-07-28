#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "Item.h"

class Player {
public:
    inline static std::string name;

    inline static void insert_item(Item* item) {
        inventory.push_back(item);
    };

    inline static void remove_item(int location) {
        inventory.erase(inventory.begin() + location);
    };

    inline static bool buy_item(Item* item) {
        if(gold >= item->price) {
            gold -= item->price;
            inventory.push_back(item);
            return true;
        } else {
            return false;
        }
    };

    inline static void display_stats() {
        std::cout << "Health: " << health << std::endl;
        std::cout << "Attack: " << attack << std::endl;
        std::cout << "Defense: " << defense << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Experience: " << experience << std::endl;
        std::cout << "Gold: " << gold << std::endl;
    };

    inline static void display_inventory() {
        for(int i = 0; i < inventory.size(); i++) {
            std::cout << inventory[i]->ITEM_NAME << std::endl;
        }
    };

    inline static std::string get_save_data() {
        std::stringstream ss;

        ss << "Health: " << health << std::endl;
        ss << "Attack: " << attack << std::endl;
        ss << "Defense: " << defense << std::endl;
        ss << "Level: " << level << std::endl;
        ss << "Experience: " << experience << std::endl;
        ss << "Gold: " << gold << std::endl;
        ss << "Inventory: \n\t";

        for(int i = 0; i < inventory.size(); i++) {
            ss << inventory[i]->ID;
            (i == inventory.size() - 1) ? ss << "\n" : ss << ", ";
            if((i + 1) % 5 == 0 && i != inventory.size() - 1) ss << "\n\t";
        }

        return ss.str();
    };

    inline static bool load_save_data(std::string &save_data) {
        try {
            int pos = save_data.find(": ", 0) + 2;
            int len = save_data.find("\n", pos) - pos;
            int current_stat = 0;

            do {
                unsigned int parsed_stat = std::stoi(save_data.substr(pos, len));

                switch(current_stat) {
                    case 0:
                        health = parsed_stat;
                        break;
                    case 1:
                        attack = parsed_stat;
                        break;
                    case 2:
                        defense = parsed_stat;
                        break;
                    case 3:
                        level = parsed_stat;
                        break;
                    case 4:
                        experience = parsed_stat;
                        break;
                    case 5:
                        gold = parsed_stat;
                        break;
                    default:
                        std::cout << "Error occurred while loading player stats\n";
                        break;
                }

                pos = save_data.find(": ", pos) + 2;
                len = save_data.find("\n", pos) - pos;
                current_stat++;
            } while(save_data.find("Inventory: \n\t", pos) != std::string::npos);

            pos = save_data.find("Inventory: \n\t") + 13;
            int ogPos = pos;
            
            len = 0;
            while(len != std::string::npos && pos >= ogPos) {
                len = save_data.find(',', pos);
                (len == std::string::npos) ? len = save_data.find('\n', pos) - pos : len -= pos;

                // Currently not loading inventory, wait for new Item implementation
                // insert_item(get_item(stoi(save_data.substr(pos, len))));

                pos = save_data.find(',', pos + len) + 2;
                pos += save_data[pos] == '\n' ? 1 : 0;
            }
        } catch(const std::exception & ex) {
            std::cout << ex.what() << "\n";
            return false;
        }

        return true;
    };
private:
    inline static unsigned int health = 10; // Stat 0
    inline static unsigned int attack = 1; // Stat 1
    inline static unsigned int defense = 1; // Stat 2
    inline static unsigned int level = 1; // Stat 3
    inline static unsigned int experience = 0; // Stat 4
    inline static unsigned int gold = 10; // Stat 5
    inline static std::vector<Item*> inventory;
};