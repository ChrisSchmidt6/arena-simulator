#include <random>

#include "Enemy.h"
#include "assets.h"
#include "Player.h"

void Enemy::generate_enemy() {
    // Pick random name from list of enemy names

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> distribution(0, enemy_names.size() - 1);

    std::cout << enemy_names[distribution(mt)] << "\n";

    Player& player = Player::get();

    const int tier = player.get_stat("Level");

    std::cout << tier << "\n";
    //Enemy new_enemy();
}

void Enemy::display_stats() {
    std::cout << "Attack: " << attack << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Gold: " << gold << "\n";
}

unsigned int Enemy::get_defense() {
    return defense;
}