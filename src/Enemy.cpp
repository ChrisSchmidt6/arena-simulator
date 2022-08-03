#include "Enemy.h"

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