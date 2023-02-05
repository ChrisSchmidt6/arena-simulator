#include <random>
#include <vector>

#include "Enemy.h"
#include "assets.h"
#include "Player.h"

Enemy::Enemy(std::string name, int max_health, int attack, int accuracy,
    int defense, int level, int experience_rewarded, int gold,
    int drop_weapon_chance, Item* weapon):
    experience_rewarded(experience_rewarded), drop_weapon_chance(drop_weapon_chance) {
    
    this->name = name;
    this->max_health = max_health;
    this->health = max_health;
    this->accuracy = accuracy;
    this->defense = defense;
    this->level = level;
    this->gold = gold;
    this->weapon_slot = weapon;
};

std::string Enemy::get_name() {
    return name;
};

int Enemy::get_stat(std::string stat) {
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
    } else {
        throw std::invalid_argument("std::string stat must be a valid Player statistic");
    }
};

void Enemy::display_stats() {
    std::cout << "[" << name << "]\n";
    std::cout << "Health: " << health << "/" << max_health << "\n";
    std::cout << "Attack: " << attack << "\n";
    std::cout << "Accuracy: " << accuracy << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Experience rewarded: " << experience_rewarded << "\n";
    std::cout << "Gold: " << gold << "\n";
    std::cout << "Chance to drop weapon: " << drop_weapon_chance << "\n";
};

Enemy Enemy::generate_enemy(const int tier) {
    std::random_device rd;
    std::mt19937 mt(rd());

    // Pick random name from vector containing different names
    std::uniform_int_distribution<int> name_dist(0, enemy_names.size() - 1);
    std::string name = enemy_names[name_dist(mt)];

    // Base pool of 3 stat increases
    // Add another stat increase every 2nd tier increase
    int available_stat_points = 3;
    available_stat_points += tier / 2;

    int max_health = 10;
    int attack = 1;
    int accuracy = 1;
    int defense = 1;
    int weapon_tier = 1;
    int max_weapon_tier = tier + 1;

    std::vector<int*> stats = { &max_health, &attack, &accuracy, &defense, &weapon_tier };

    do {
        // Pick a random stat from the list of stat references
        std::uniform_int_distribution<int> stat_dist(0, stats.size() - 1);
        int random_stat_location = stat_dist(mt);
        int* stat_to_increase = stats[random_stat_location];

        // Pick a number between 1 and available points left
        std::uniform_int_distribution<int> stat_inc_dist(1, available_stat_points);
        int increase_amount = stat_inc_dist(mt);

        // If stat to be changed is weapon tier, and amount is greater than max weapon tier,
        // instead change weapon tier to max amount and deduct that from points
        if(stat_to_increase == &weapon_tier && increase_amount > max_weapon_tier) {
            *stat_to_increase += max_weapon_tier;
            available_stat_points -= max_weapon_tier;
        } else {
            // Otherwise carry on as normal
            *stat_to_increase += increase_amount;
            available_stat_points -= increase_amount;
        }

        // Remove stat from list of stats
        stats.erase(stats.begin() + random_stat_location);
    } while(stats.size() > 0 && available_stat_points > 0);

    // Create vector of weapons based on weapon tier
    std::vector<Item*> weapon_options;
    for(int i = 0; i < item_container.size(); i++) {
        Item* item = item_container[i];
        if(item->TIER == weapon_tier && item->TYPE == VenType::Blacksmith) {
            weapon_options.push_back(item);
        }
    }
    // Pick random weapon from vector
    std::uniform_int_distribution<int> weapon_dist(0, weapon_options.size() - 1);
    Item* weapon = weapon_options[weapon_dist(mt)];

    // Randomize rewards
    int min_gold = 2 * tier;
    int max_gold = 3 * tier;
    std::uniform_int_distribution<int> gold_dist(min_gold, max_gold);
    int gold = gold_dist(mt);
    int drop_weapon_chance;
    int experience_rewarded = 1.5 * max_health;

    switch(weapon->RARITY) {
        case Rarity::Common:
            drop_weapon_chance = 20;
            break;
        case Rarity::Uncommon:
            drop_weapon_chance = 10;
            break;
        case Rarity::Rare:
            drop_weapon_chance = 5;
            break;
        case Rarity::Mythic:
            drop_weapon_chance = 2;
            break;
        default:
            drop_weapon_chance = 0;
            break;
    };

    return Enemy(
        name, max_health, attack, accuracy, defense, tier,
        experience_rewarded, gold, drop_weapon_chance, weapon
    );
};