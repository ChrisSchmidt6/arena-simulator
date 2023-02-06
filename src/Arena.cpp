#include <iostream>
#include <random>

#include "Arena.h"
#include "utility.h"
#include "Player.h"
#include "Enemy.h"

void Arena::main_menu() {
    pairVec menu_items;

    do {
        std::cout << "Welcome to the arena! You can expect formidable foes if you dare to fight.\n\n";
        std::cout << "[Arena Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Fight", [this]() -> void {
            fight_menu();
        }));

        menu_items.push_back(std::make_pair("Train", [this]() -> void {
            train_menu();
        }));

    } while(print_menu(menu_items));
};

void Arena::fight_menu() {
    const int tier = player.get_stat("Level");
    // Generate new enemy if previously generated enemy is lower level
    if(enemy.get_stat("Level") < tier) enemy = Enemy::generate_enemy(tier);
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
        
        pre_round_checks(enemy);

        // Set enemy to defending if that was chosen
        if(move == 2) enemy.toggle_focused();
        if(move == 3) enemy.toggle_defending();

        menu_items.clear();

        // Insert blank so that fight options start at 1 instead of 0
        menu_items.push_back(std::make_pair("Blank", []() -> void {}));

        menu_items.push_back(std::make_pair("Attack", [this]() -> void {
            pre_round_checks(player);
            // Regular attack
            process_attack(player, enemy);
            if(!enemy.is_alive()) return;
            // Process enemy attack if not defending
            if(!enemy.is_defending()) process_attack(enemy, player);
        }));

        if(!player.is_focused()) {
            menu_items.push_back(std::make_pair("Focused Attack", [this]() -> void {
                pre_round_checks(player);
                // Double accuracy this turn, half damage next turn
                player.toggle_focused();
                process_attack(player, enemy);
                if(!enemy.is_alive()) return;
                // Process enemy attack if not defending
                if(!enemy.is_defending()) process_attack(enemy, player);
            }));
        }

        if(!player.is_defending()) {
            menu_items.push_back(std::make_pair("Defend", [this]() -> void {
                pre_round_checks(player);
                // Double defense for a turn
                player.toggle_defending();
                // Process enemy attack if not defending
                if(!enemy.is_defending()) process_attack(enemy, player);
                else std::cout << "Both fighters stare at each other blankly, "
                    << "wondering whether they would be friends in another reality..\n";
            }));
        }

        menu_items.push_back(std::make_pair("Check Consumables", [this]() -> void {
            pre_round_checks(player);
            // Player::check_consumables();
            if(!enemy.is_defending()) process_attack(enemy, player);
        }));

    } while(print_menu(menu_items, true) && player.is_alive() && enemy.is_alive());

    if(!enemy.is_alive()) {
        // Handle enemy death
        std::cout << "Enemy death\n";
    } else if(!player.is_alive()) {
        // Handle player death
        std::cout << "Player death\n";
    }
};

void Arena::train_menu() {
    std::cout << "You will have to pay gold to train.\n";
};

void Arena::pre_round_checks(Combat &fighter) {
    if(fighter.is_defending()) fighter.toggle_defending();

    if(fighter.is_weakened() && fighter.is_focused()) {
        fighter.toggle_focused();
    } else if (fighter.is_weakened()) {
        fighter.toggle_weakened();
    }
};

void Arena::process_attack(Combat &attacker, Combat &defender) {
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
    pause_until_enter();
};