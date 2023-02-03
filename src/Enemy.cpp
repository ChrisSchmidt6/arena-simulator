#include <random>
#include <vector>

#include "Enemy.h"
#include "assets.h"
#include "Player.h"

Enemy Enemy::generate_enemy(const unsigned int tier) {
    std::random_device rd;
    std::mt19937 mt(rd());

    // Pick random name from vector containing different names
    std::uniform_int_distribution<int> name_dist(0, enemy_names.size() - 1);
    std::string name = enemy_names[name_dist(mt)];

    // Base pool of 5 stat increases
    int available_stat_points = 5;
    // Add another stat increase every 2nd tier increase
    available_stat_points += tier / 2;

    unsigned int max_health = 10;
    unsigned int attack = 1;
    unsigned int accuracy = 1;
    unsigned int defense = 1;
    unsigned int weapon_tier = 1;
    unsigned int max_weapon_tier = tier + 2;

    std::vector<unsigned int*> stats = { &max_health, &attack, &accuracy, &defense, &weapon_tier };

    do {
        // Pick a random stat from the list of stat references
        std::uniform_int_distribution<int> stat_dist(0, stats.size() - 1);
        int random_stat_location = stat_dist(mt);
        unsigned int* stat_to_increase = stats[random_stat_location];

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
    unsigned int gold = gold_dist(mt);
    unsigned int drop_weapon_chance;
    unsigned int experience_rewarded = 1.5 * max_health;

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
        name, max_health, max_health, attack,
        accuracy, defense, tier, experience_rewarded,
        gold, drop_weapon_chance, weapon
    );
}

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
}

unsigned int Enemy::get_defense() {
    return defense;
}