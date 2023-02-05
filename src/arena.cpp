#include <iostream>
#include <random>

#include "arena.h"
#include "utility.h"
#include "Player.h"
#include "Enemy.h"

void arena_menu() {
    pairVec menu_items;

    do {
        std::cout << "Welcome to the arena! You can expect formidable foes if you dare to fight.\n\n";
        std::cout << "[Arena Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Fight", []() -> void {
            arena_fight();
        }));

        menu_items.push_back(std::make_pair("Train", []() -> void {
            arena_train();
        }));

    } while(print_menu(menu_items));
};

void arena_fight() {
    const int tier = Player::get().get_stat("Level");
    Enemy enemy = Enemy::generate_enemy(tier);
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "You are fighting " << enemy.get_name() << ".\n\n";

    pairVec menu_items;

    do {
        std::cout << "[Fight Menu]\n";

        // 1 = attack, 2 = focused attack, 3 = defend
        std::vector<int> enemy_moves { 1, 2, 3 };
        if(enemy.is_focused()) enemy_moves.erase(enemy_moves.begin() + 1);
        if(enemy.is_defending()) enemy_moves.erase(enemy_moves.begin() + 2);

        std::uniform_int_distribution<int> move_dist(0, enemy_moves.size() - 1);
        // Enemy picks move
        int move = enemy_moves[move_dist(mt)];
        
        arena_pre_round_checks(enemy);

        // Set enemy to defending if that was chosen
        if(move == 2) enemy.toggle_focused();
        if(move == 3) enemy.toggle_defending();

        menu_items.clear();

        menu_items.push_back(std::make_pair("Attack", [&enemy]() -> void {
            arena_pre_round_checks(Player::get());
            // Regular attack
            arena_attack(Player::get(), enemy);
            if(!enemy.is_alive()) return;
            // Process enemy attack if not defending
            if(!enemy.is_defending()) arena_attack(enemy, Player::get());
        }));

        if(!Player::get().is_focused()) {
            menu_items.push_back(std::make_pair("Focused Attack", [&enemy]() -> void {
                arena_pre_round_checks(Player::get());
                // Double accuracy this turn, half damage next turn
                Player::get().toggle_focused();
                arena_attack(Player::get(), enemy);
                if(!enemy.is_alive()) return;
                // Process enemy attack if not defending
                if(!enemy.is_defending()) arena_attack(enemy, Player::get());
            }));
        }

        if(!Player::get().is_defending()) {
            menu_items.push_back(std::make_pair("Defend", [&enemy]() -> void {
                arena_pre_round_checks(Player::get());
                // Double defense for a turn
                Player::get().toggle_defending();
                // Process enemy attack if not defending
                if(!enemy.is_defending()) arena_attack(enemy, Player::get());
                else std::cout << "Both fighters stare at each other blankly, "
                    << "wondering whether they would be friends in another reality..\n";
            }));
        }

        menu_items.push_back(std::make_pair("Check Consumables", [&enemy]() -> void {
            arena_pre_round_checks(Player::get());
            // Player::check_consumables();
            if(!enemy.is_defending()) arena_attack(enemy, Player::get());
        }));

    } while(print_menu(menu_items, true) && Player::get().is_alive() && enemy.is_alive());

    if(!enemy.is_alive()) {
        // Handle enemy death
        std::cout << "Enemy death\n";
    } else if(!Player::get().is_alive()) {
        // Handle player death
        std::cout << "Player death\n";
    }
};

void arena_pre_round_checks(Combat &fighter) {
    if(fighter.is_defending()) fighter.toggle_defending();

    if(fighter.is_weakened() && fighter.is_focused()) {
        fighter.toggle_focused();
    } else if (fighter.is_weakened()) {
        fighter.toggle_weakened();
    }
};

void arena_attack(Combat &attacker, Combat &defender) {
    int e_health = defender.get_stat("Health");
    int e_defense = defender.get_stat("Defense");
    if(defender.is_defending()) {
        std::cout << defender.get_name() << " has chosen to defend!\n";
        e_defense *= 2;
    }

    bool landed_hit = attacker.accuracy_roll(e_defense);

    if(landed_hit) {
        int damage = attacker.damage_roll();
        if(damage > e_health) damage = e_health;
        defender.take_damage(damage);
        
        // Display "focused" if attack was focused
        std::string optional = attacker.is_focused() ? "focused " : "";
        std::cout << attacker.get_name() << " landed a " << optional << "hit! "
            << defender.get_name() << " has taken " << damage << " damage.\n";

        // Check if defender is dead, if so, name and shame.
        if(!defender.is_alive()) std::cout << defender.get_name() << " has fallen!\n";
    } else {
        // Display "focused" or "tried" depending on attack type
        std::string verb = attacker.is_focused() ? " focused" : " tried";
        std::cout << attacker.get_name()
            << verb << " as hard as they could, but alas, they missed their attack.\n";
    }

    // Set weakened to true, if this was a focused hit
    if(attacker.is_focused()) attacker.toggle_weakened();
};

void arena_train() {
    std::cout << "You will have to pay gold to train.\n";
};