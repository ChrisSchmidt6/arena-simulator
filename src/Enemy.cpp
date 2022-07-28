#include "Enemy.h"

void Enemy::display_stats() {
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Defense: " << defense << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Gold: " << gold << std::endl;
}

unsigned int Enemy::get_defense() {
    return defense;
}