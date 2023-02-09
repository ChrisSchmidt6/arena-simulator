#include <random>
#include <vector>
#include <cmath>

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
    this->attack = attack;
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

int Enemy::gold_reward() {
    return gold;
};

bool Enemy::weapon_reward() {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> drop_dist(1, 100);
    bool will_drop = drop_dist(mt) < drop_weapon_chance;
    return will_drop;
};

int Enemy::experience_reward() {
    return experience_rewarded;
};

Enemy Enemy::generate_enemy(const int tier) {
    std::random_device rd;
    std::mt19937 mt(rd());

    // Pick random name from vector containing different names
    std::uniform_int_distribution<int> name_dist(0, enemy_names.size() - 1);
    std::string name = enemy_names[name_dist(mt)];

    // Base pool of 3 stat increases unless training
    // Add another stat increase every 2nd tier increase if not training
    int available_stat_points = 0;
    if(tier >= Player::get().get_stat("Level")) {
        available_stat_points =  3;
        available_stat_points += floor(tier / 5);
    }

    // Every 4th tier, increase base stats by 1
    const int BASE_INCREASE = floor(tier / 3);
    int base_health = 10 + floor(tier / 2);
    int max_health = base_health + BASE_INCREASE;
    int attack = 1 + BASE_INCREASE;
    int accuracy = 1 + BASE_INCREASE;
    int defense = 1 + BASE_INCREASE;
    int weapon_tier = 1 + BASE_INCREASE;
    int max_weapon_tier = tier + 1;

    std::vector<int*> stats = { &max_health, &attack, &accuracy, &defense, &weapon_tier };

    while(available_stat_points > 0 && stats.size() > 0) {
        // Pick a random stat from the list of stat references
        std::uniform_int_distribution<int> stat_dist(0, stats.size() - 1);
        int random_stat_location = stat_dist(mt);
        int* stat_to_increase = stats[random_stat_location];

        // Pick a number between 1 and available points left
        std::uniform_int_distribution<int> stat_inc_dist(1, available_stat_points);
        int increase_amount = stat_inc_dist(mt);

        // Increase stat by amount, remove amount from available points
        *stat_to_increase += increase_amount;
        available_stat_points -= increase_amount;

        // If stat to be changed is weapon_tier and is greater than max_weapon_tier,
        // set it to max_weapon_tier and refund the difference
        if(stat_to_increase == &weapon_tier && weapon_tier > max_weapon_tier) {
            int change_amount = max_weapon_tier - weapon_tier;
            available_stat_points += change_amount;
            weapon_tier = max_weapon_tier;
        }

        // Remove stat from list of stats
        stats.erase(stats.begin() + random_stat_location);
    }

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