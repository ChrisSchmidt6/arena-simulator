#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "Player.h"
#include "Weapon.h"
#include "utility.h"

void Player::insert_item(Item* item) {
    inventory.push_back(item);
};

bool Player::remove_item(Item* item) {
    int item_location = has_item(item);
    if(item_location == -1) return false;
    inventory.erase(inventory.begin() + item_location);
    return true;
};

bool Player::buy_item(Item* item) {
    if(gold >= item->PRICE) {
        gold -= item->PRICE;
        inventory.push_back(item);
        return true;
    } else {
        return false;
    }
};

int Player::has_item(Item* item) {
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i] == item) {
            return i;
        }
    }
    return -1;
}

void Player::equip_weapon(Item* weapon) {
    int inventory_location;
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i] == weapon) {
            inventory_location = i;
            break;
        }
    }
    Item* old_weapon = weapon_slot;
    weapon_slot = weapon;
    if(old_weapon->ID != 200) inventory[inventory_location] = old_weapon;
    else inventory.erase(inventory.begin() + inventory_location);
};

void Player::display_stats() {
    std::cout << "Max Health: " << max_health << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Attack: " << attack << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Experience: " << experience << "\n";
};

void Player::inventory_menu() {
    pairVec menu_items;

    do {
        std::cout << "You have " << gold << " gold pieces.\n\n";
        std::cout << "[Inventory Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair(
            "View equipped " + weapon_slot->ITEM_NAME,
            [this]() -> void {
                if(weapon_slot->ID == 200) {
                    std::cout << "There's no reason to stand around examining your fists.\n";
                } else {
                    weapon_menu();
                }
            }));

        for(int i = 0; i < inventory.size(); i++) {
            menu_items.push_back(std::make_pair(
                "View options - " + inventory[i]->ITEM_NAME,
                [this, i]() -> void {
                    inventory[i]->display_item_options();
                }));
        }

    } while(print_menu(menu_items));
};

void Player::weapon_menu() {
    pairVec menu_items;

    do {
        // This cannot fail as you're only able to equip weapons
        Weapon* weapon = static_cast<Weapon*>(weapon_slot);
        std::cout << "Your " << weapon->ITEM_NAME << " has an attack modifier of " << weapon->ATTACK_MOD << "\n\n";
        std::cout << "[Equipped Weapon Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair(
            "Unequip " + weapon->ITEM_NAME,
            [this, weapon]() -> void {
                if(weapon->ID == 200) {
                    std::cout << "You try to remove your fists... but you fail. Congratulations, your fists are now sore.\n\n";
                    return;
                } else {
                    inventory.push_back(weapon_slot);
                    weapon_slot = get_item(200);
                    std::cout << "You are no longer wielding your " << weapon->ITEM_NAME << ".\n\n";
                    return;
                }
            }));

    } while(print_menu(menu_items));
};

std::string Player::get_save_data() {
    std::stringstream ss;

    ss << "Max Health: " << max_health << "\n";
    ss << "Health: " << health << "\n";
    ss << "Attack: " << attack << "\n";
    ss << "Defense: " << defense << "\n";
    ss << "Level: " << level << "\n";
    ss << "Experience: " << experience << "\n";
    ss << "Gold: " << gold << "\n";
    ss << "Weapon: " << weapon_slot->ID << "\n";
    ss << "Inventory: \n\t";

    for(int i = 0; i < inventory.size(); i++) {
        ss << inventory[i]->ID;
        (i == inventory.size() - 1) ? ss << "\n" : ss << ", ";
        if((i + 1) % 5 == 0 && i != inventory.size() - 1) ss << "\n\t";
    }

    return ss.str();
};

bool Player::load_save_data(std::string &save_data) {
    try {
        int pos = save_data.find(": ", 0) + 2;
        int len = save_data.find("\n", pos) - pos;
        int current_stat = 0;

        do {
            unsigned int parsed_stat = std::stoi(save_data.substr(pos, len));

            switch(current_stat) {
                case 0:
                    max_health = parsed_stat;
                    break;
                case 1:
                    health = parsed_stat;
                    break;
                case 2:
                    attack = parsed_stat;
                    break;
                case 3:
                    defense = parsed_stat;
                    break;
                case 4:
                    level = parsed_stat;
                    break;
                case 5:
                    experience = parsed_stat;
                    break;
                case 6:
                    gold = parsed_stat;
                    break;
                case 7:
                    weapon_slot = get_item(parsed_stat);
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
            if(len == 0) break;

            insert_item(get_item(stoi(save_data.substr(pos, len))));

            pos = save_data.find(',', pos + len) + 2;
            pos += (save_data[pos] == '\n') ? 1 : 0;
        }
    } catch(const std::exception & ex) {
        std::cout << ex.what() << "\n";
        return false;
    }

    return true;
};