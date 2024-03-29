#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "Game.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "utility.hpp"

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

void Player::remove_weapon() {
    weapon_slot = get_item(200);
};

int Player::weapon_drop_chance() {
    return LOSE_WEAPON_CHANCE;
};

void Player::increase_gold(int amount) {
    gold += amount;
};

void Player::decrease_gold(int amount) {
    gold = amount > gold ? 0 : gold - amount;
};

void Player::gain_experience(int amount) {
    std::cout << "You gain " << amount << " experience.\n";
    experience += amount;
    total_experience += amount;
    pause_until_enter();
    if(experience > experience_target) {
        experience -= experience_target;
        level_up();
    }
};

std::string Player::get_name() {
    return name;
};

int Player::get_stat(std::string stat) {
    if(stat == "Max Health") {
        return max_health;
    } else if(stat == "Health") {
        return health;
    } else if(stat == "Attack") {
        return attack;
    } else if(stat == "Accuracy") {
        return accuracy;
    } else if(stat == "Defense") {
        return defense;
    } else if(stat == "Level") {
        return level;
    } else if(stat == "Experience") {
        return experience;
    } else if(stat == "Gold") {
        return gold;
    } else {
        throw std::invalid_argument("std::string stat must be a valid Player statistic");
    }
};

void Player::display_stats() {
    // Width of stat titles
    int tw = 14;
    printf("%-*s%-s\n", tw, "Health:", (std::to_string(health) + " / " + std::to_string(max_health)).c_str());
    printf("%-*s%-s\n", tw, "Attack:", std::to_string(attack).c_str());
    printf("%-*s%-s\n", tw, "Accuracy:", std::to_string(accuracy).c_str());
    printf("%-*s%-s\n", tw, "Defense:", std::to_string(defense).c_str());
    printf("%-*s%-s\n", tw, "Level:", std::to_string(level).c_str());
    printf("%-*s%-s\n", tw, "Experience:", (std::to_string(experience) + " / " + std::to_string(experience_target)).c_str());
    printf("%-*s%-s\n", tw, "Total Exp.:", std::to_string(total_experience).c_str());
};

void Player::inventory_menu() {
    pairVec menu_items;

    do {
        std::cout << "You have " << gold << " gold.\n\n";
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
            Item* item = inventory[i];
            menu_items.push_back(std::make_pair(
                "View options - " + inventory[i]->ITEM_NAME,
                [item]() -> void {
                    item->display_item_options();
                }));
        }
    } while(print_menu(menu_items));
};

void Player::weapon_menu() {
    pairVec menu_items;

    do {
        Weapon* weapon = get_weapon();
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
                    std::cout << "You are no longer wielding your " << weapon->ITEM_NAME << ".\n";
                    pause_until_enter();
                    return;
                }
            }));

    } while(print_menu(menu_items));
};

std::vector<Item*> Player::get_items_by_type(VenType type) {
    std::vector<Item*> items;
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i]->TYPE == type) {
            items.push_back(inventory[i]);
        }
    }
    return items;
};

void Player::drink_potion(Consumable* potion) {
    std::cout << "You gulp down your " << potion->ITEM_NAME << " quickly and feel invigorated.\n";
    att_boost += potion->ATTACK_MOD;
    acc_boost += potion->ACCURACY_MOD;
    def_boost += potion->DEFENSE_MOD;
    remove_item(potion);

    int new_health = health + potion->HEALTH_REGEN;
    health = new_health > max_health ? max_health : new_health;
    save_to_file();
    pause_until_enter();
};

void Player::eat_food(Consumable* food) {
    std::cout << "You devour your " << food->ITEM_NAME << " and feel satiated.\n";
    int old_health = health;
    int new_health = health + food->HEALTH_REGEN;
    health = new_health > max_health ? max_health : new_health;
    std::cout << "You have restored " << (health - old_health) << " health.\n";
    remove_item(food);
    save_to_file();
    pause_until_enter();
};

void Player::reset_health() {
    health = max_health;
};

void Player::level_up() {
    level++;
    std::cout << "Congratulations, you have leveled up!\n";

    // Regenerate vendor inventories
    Game::get().generate_inventories();

    // Free health increase every 2nd level
    bool health_increase = level % 2;
    if(health_increase) {
        std::cout << "Your max health has increased to " << ++max_health << "!\n";
        if(health < max_health) health++;
    }
    experience_target *= EXPERIENCE_SCALING;
    save_to_file();
    pause_until_enter();

    pairVec menu_items;
    int stat_points = 2;

    do {
        std::cout << "You have " << stat_points << " point(s) to increase stats. Pick a stat to increase by 1.\n\n";
        std::cout << "[Level Up Menu]\n";
        menu_items.clear();

        menu_items.push_back(std::make_pair("Blank", []() -> void {}));

        menu_items.push_back(std::make_pair("Health", [this, &stat_points]() -> void {
            stat_points--;
            std::cout << "Your max health has increased to " << ++max_health << "!\n";
            save_to_file();
            pause_until_enter();
        }));

        menu_items.push_back(std::make_pair("Attack", [this, &stat_points]() -> void {
            stat_points--;
            std::cout << "Your attack has increased to " << ++attack << "!\n";
            save_to_file();
            pause_until_enter();
        }));

        menu_items.push_back(std::make_pair("Accuracy", [this, &stat_points]() -> void {
            stat_points--;
            std::cout << "Your accuracy has increased to " << ++accuracy << "!\n";
            save_to_file();
            pause_until_enter();
        }));

        menu_items.push_back(std::make_pair("Defense", [this, &stat_points]() -> void {
            stat_points--;
            std::cout << "Your defense has increased to " << ++defense << "!\n";
            save_to_file();
            pause_until_enter();
        }));
    } while(print_menu(menu_items, true) && stat_points > 0);
};

std::string Player::get_save_data() {
    std::stringstream ss;

    ss << "Max Health: " << max_health << "\n";
    ss << "Health: " << health << "\n";
    ss << "Attack: " << attack << "\n";
    ss << "Accuracy: " << accuracy << "\n";
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
    reset_player_data();
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
                    accuracy = parsed_stat;
                    break;
                case 4:
                    defense = parsed_stat;
                    break;
                case 5:
                    level = parsed_stat;
                    break;
                case 6:
                    experience = parsed_stat;
                    break;
                case 7:
                    gold = parsed_stat;
                    break;
                case 8:
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

        // Calibrate experience variables
        int i = 0;
        while(i++ < level - 1) {
            total_experience += experience_target;
            experience_target *= EXPERIENCE_SCALING;
        }
        total_experience += experience;
    } catch(const std::exception & ex) {
        std::cout << ex.what() << "\n";
        return false;
    }

    return true;
};

void Player::reset_player_data() {
    max_health = 10;
    health = 10;
    attack = 1;
    accuracy = 1;
    defense = 1;
    level = 1;
    experience = 0;
    total_experience = 0;
    gold = 30;
    inventory.clear();
};