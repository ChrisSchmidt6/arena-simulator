#pragma once

#include <vector>
#include <sstream>
#include <string>

#include "Item.h"

class Player {
public:
    inline static std::string name;
    inline static unsigned int gold = 10;

    inline static void insert_item(Item* item) {
        inventory.push_back(item);
    };

    inline static void remove_item(int location) {
        inventory.erase(inventory.begin() + location);
    };

    inline static void clear_inventory() {
        inventory.clear();
    };

    inline static void display_stats() {
        std::cout << "Attack: " << attack << std::endl;
        std::cout << "Defense: " << defense << std::endl;
        std::cout << "Health: " << health << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Experience: " << experience << std::endl;
        std::cout << "Gold: " << gold << std::endl;
    }

    inline static void display_inventory() {
        for(int i = 0; i < inventory.size(); i++) {
            std::cout << inventory[i]->ITEM_NAME << std::endl;
        }
    }

    inline static std::string get_save_data() {
        std::stringstream ss;

        ss << "Attack: " << attack << std::endl;
        ss << "Defense: " << defense << std::endl;
        ss << "Health: " << health << std::endl;
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
            int pos, len;
            pos = save_data.find("Attack: ") + 8;
            len = save_data.find("\n", pos) - pos;
            attack = std::stoi(save_data.substr(pos, len));

            pos = save_data.find("Defense: ") + 8;
            len = save_data.find("\n", pos) - pos;
            defense = std::stoi(save_data.substr(pos, len));

            pos = save_data.find("Health: ") + 8;
            len = save_data.find("\n", pos) - pos;
            health = std::stoi(save_data.substr(pos, len));

            pos = save_data.find("Level: ") + 7;
            len = save_data.find("\n", pos) - pos;
            level = std::stoi(save_data.substr(pos, len));

            pos = save_data.find("Experience: ") + 12;
            len = save_data.find("\n", pos) - pos;
            level = std::stoi(save_data.substr(pos, len));

            pos = save_data.find("Gold: ") + 6;
            len = save_data.find("\n", pos) - pos;
            gold = std::stoi(save_data.substr(pos, len));

            inventory.clear();
            pos = save_data.find("Inventory: \n\t") + 13;
            int ogPos = pos;
            
            len = 0;
            while(len != std::string::npos && pos >= ogPos) {
                len = save_data.find(',', pos);
                (len == std::string::npos) ? len = save_data.find('\n', pos) - pos : len -= pos;

                insert_item(get_item(stoi(save_data.substr(pos, len))));

                pos = save_data.find(',', pos + len) + 2;
                pos += save_data[pos] == '\n' ? 1 : 0;
            }
        } catch(std::exception e) {
            return false;
        }

        return true;
    };
private:
    inline static unsigned int attack = 1;
    inline static unsigned int defense = 1;
    inline static unsigned int health = 10;
    inline static unsigned int level = 1;
    inline static unsigned int experience = 0;
    inline static std::vector<Item*> inventory;
};