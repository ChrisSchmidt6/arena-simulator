#include <iostream>
#include <iomanip>
#include <random>

#include "Arena.h"
#include "Consumable.h"
#include "utility.h"

void Arena::main_menu() {
    const int tier = player.get_stat("Level");
    pairVec menu_items;

    do {
        std::cout << "Welcome to the arena! You can expect formidable foes if you dare to fight.\n\n";
        std::cout << "[Arena Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Fight", [this, tier]() -> void {
            // Generate new enemy if previously generated enemy is lower level
            if(enemy.get_stat("Level") != tier) enemy = Enemy::generate_enemy(tier);
            fight_menu();
        }));

        menu_items.push_back(std::make_pair("Train", [this, tier]() -> void {
            int amount = tier * 5;
            if(player.get_stat("Gold") < amount) {
                std::cout << "You don't have " << amount << " gold pieces to spend.\n";
                pause_until_enter();
                return;
            }

            pairVec confirm_items;
            bool early_return = false;

            do {
                std::cout << "There is a " << amount << " gold entry fee. Will you pay it?\n";
                std::cout << "[Confirmation Menu]\n";
                
                confirm_items.push_back(std::make_pair("Yes", [this, tier, amount, &early_return]() -> void {
                    if(enemy.get_stat("Level") != tier - 1) enemy = Enemy::generate_enemy(tier - 1);
                    player.decrease_gold(amount);
                    std::cout << "You have paid " << amount << " gold pieces to train.\n";
                    pause_until_enter();
                    train_menu();
                    early_return = true;
                }));

                confirm_items.push_back(std::make_pair("No", [&early_return]() -> void {
                    early_return = true;
                }));
            } while(print_menu(confirm_items) && !early_return);
            
        }));

    } while(print_menu(menu_items));
};

void Arena::fight_menu(bool safe_death) {
    const int tier = player.get_stat("Level");
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "You are fighting " << enemy.get_name() << ".\n\n";

    pairVec menu_items;

    // 1 = attack, 2 = accurate attack, 3 = defend
    int enemy_move;

    do {
        std::cout << "[Fight Menu]\n";

        if(continue_round) {
            // Check and update cooldowns
            pre_round_checks(enemy);
            pre_round_checks(player);
            
            // Set whether defending is an option
            int possible_moves = enemy.can_defend() ? 3 : 2;
            std::uniform_int_distribution<int> move_dist(1, possible_moves);
            // Enemy picks enemy_move
            enemy_move = move_dist(mt);

            // Set enemy to defending if that was chosen
            if(enemy_move == 2) enemy.toggle_accurate();
            if(enemy_move == 3) enemy.toggle_defending();
        }

        menu_items.clear();
        continue_round = false;

        // Insert blank so that fight options start at 1 instead of 0
        menu_items.push_back(std::make_pair("Blank", []() -> void {}));

        std::string attack_option = player.is_weakened() ? "Attack [weakened]" : "Attack";
        menu_items.push_back(std::make_pair(attack_option, [this]() -> void {
            process_attack(player, enemy);
            if(!enemy.is_alive()) return;
            // Process enemy attack if not defending
            if(!enemy.is_defending()) process_attack(enemy, player);
            continue_round = true;
        }));

        std::string accurate_option =
            player.is_weakened() ? "Accurate Attack [weakened]" : "Accurate Attack";
        menu_items.push_back(std::make_pair(accurate_option, [this]() -> void {
            // Double accuracy this turn, half damage next turn
            player.toggle_accurate();
            process_attack(player, enemy);
            if(!enemy.is_alive()) return;

            // Process enemy attack if not defending
            if(!enemy.is_defending()) process_attack(enemy, player);
            continue_round = true;
        }));

        if(player.can_defend()) menu_items.push_back(std::make_pair("Defend", [this]() -> void {
                // Double defense for a turn
                player.toggle_defending();
                // Process enemy attack if not defending
                if(!enemy.is_defending()) process_attack(enemy, player);
                else {
                    std::cout << "Both fighters stare at each other blankly, "
                        << "wondering whether they would be friends in another reality..\n"
                        << "(You both tried to defend)\n";
                    pause_until_enter();
                }
                continue_round = true;
            }));

        if(!safe_death) menu_items.push_back(std::make_pair("Check Consumables", [this]() -> void {
                consumables_menu();
            }));

        menu_items.push_back(std::make_pair("Check Statistics", [this]() -> void {
            print_stats();
        }));

    } while(print_menu(menu_items, true) && player.is_alive() && enemy.is_alive());

    // Reset cooldowns
    player.reset_temps();

    // Check for deaths
    if(!enemy.is_alive()) enemy_death(safe_death);
    else if(!player.is_alive()) player_death(safe_death);
    else {
        std::cout << "Something went wrong -> Fight ended but both fighters have health\n";
        pause_until_enter();
    }

    // Generate new enemy for a future fight
    enemy = Enemy::generate_enemy(tier);
};

void Arena::train_menu() {
    fight_menu(true);
};

void Arena::pre_round_checks(Combat &fighter) {
    if(fighter.is_defending() && !fighter.can_defend()) fighter.toggle_defending();
    else if(!fighter.can_defend()) fighter.clear_def_cooldown();

    if(fighter.is_accurate()) {
        fighter.toggle_accurate();
        if(!fighter.is_weakened()) fighter.toggle_weakened();
    } else if(fighter.is_weakened()) {
        fighter.toggle_weakened();
    }
};

void Arena::process_attack(Combat &attacker, Combat &defender) {
    int e_health = defender.get_stat("Health");
    int e_defense = defender.get_stat("Defense");
    if(defender.is_defending()) {
        e_defense += e_defense;
        std::cout << defender.get_name() << " has chosen to defend!\n";
    }
    e_defense += defender.get_boost("Defense");
    bool landed_hit = attacker.accuracy_roll(e_defense);

    // Include indicators of boosts and nerfs
    std::string possibleWeakened = attacker.is_weakened() ? "weakened " : "";
    std::string possibleAccurate = attacker.is_accurate() ? "more accurate " : "";

    if(landed_hit) {
        int damage = attacker.damage_roll();
        if(damage > e_health) damage = e_health;
        defender.take_damage(damage);
        
        std::cout << attacker.get_name() << " landed a " << possibleWeakened << possibleAccurate
            << "hit! " << defender.get_name() << " has taken " << damage << " damage.\n";
    } else {
        std::cout << defender.get_name() << " managed to avoid " << attacker.get_name() << "'s "
            << possibleWeakened << possibleAccurate << "strike!\n";
    }

    // Check if defender has died
    if(!defender.is_alive())
        std::cout << attacker.get_name() << " has defeated " << defender.get_name() << "!\n\n";
    else {
        save_to_file();
        pause_until_enter();
    }
};

void Arena::print_stats() {
    // Width of stat titles
    int tw = 12;
    // Width of fighter details
    int fw = 28;
    printf("%-*s%-*s%-*s\n", tw, "Names:", fw, player.get_name().c_str(), fw, (enemy.get_name() + " [Foe]").c_str());
    printf("%-*s%-*s%-*s\n", tw, "Health:",
        fw, (std::to_string(player.get_stat("Health")) + " / " + std::to_string(player.get_stat("Max Health"))).c_str(),
        fw, (std::to_string(enemy.get_stat("Health")) + " / " + std::to_string(enemy.get_stat("Max Health"))).c_str());
    printf("%-*s%-*s%-*s\n", tw, "Attack:",
        fw, (std::to_string(player.get_stat("Attack")) + " [+" + std::to_string(player.get_boost("Attack")) + "]").c_str(),
        fw, (std::to_string(enemy.get_stat("Attack")) + " [+" + std::to_string(enemy.get_boost("Attack")) + "]").c_str());
    printf("%-*s%-*s%-*s\n", tw, "Accuracy:",
        fw, (std::to_string(player.get_stat("Accuracy")) + " [+" + std::to_string(player.get_boost("Accuracy")) + "]").c_str(),
        fw, (std::to_string(enemy.get_stat("Accuracy")) + " [+" + std::to_string(enemy.get_boost("Accuracy")) + "]").c_str());
    printf("%-*s%-*s%-*s\n", tw, "Defense:",
        fw, (std::to_string(player.get_stat("Defense")) + " [+" + std::to_string(player.get_boost("Defense")) + "]").c_str(),
        fw, (std::to_string(enemy.get_stat("Defense")) + " [+" + std::to_string(enemy.get_boost("Defense")) + "]").c_str());
    printf("%-*s%-*s%-*s\n", tw, "Level:",
        fw, std::to_string(player.get_stat("Level")).c_str(),
        fw, std::to_string(enemy.get_stat("Level")).c_str());
    printf("%-*s%-*s%-*s\n", tw, "Weapon:",
        fw, (player.get_weapon()->ITEM_NAME + " [+" + std::to_string(player.get_weapon()->ATTACK_MOD) + "]").c_str(),
        fw, (enemy.get_weapon()->ITEM_NAME + " [+" + std::to_string(enemy.get_weapon()->ATTACK_MOD) + "]").c_str());
    pause_until_enter();
};

void Arena::consumables_menu() {
    pairVec menu_items;

    int potion_amount = player.get_potions().size();
    if(potion_amount == 0) {
        std::cout << "You do not have any potions in your inventory.\n";
        pause_until_enter();
        return;
    }
    bool go_back = false;

    do {
        menu_items.clear();

        menu_items.push_back(std::make_pair("Go back", [&go_back]() -> void {
            go_back = true;
        }));

        for(int i = 0; i < potion_amount; i++) {
            Consumable* potion = player.get_potions()[i];
            menu_items.push_back(std::make_pair("Drink " + potion->ITEM_NAME, [this, i, &go_back]() -> void {
                player.drink_potion(player.get_potions()[i]);
                if(!enemy.is_defending()) process_attack(enemy, player);
                continue_round = true;
                go_back = true;
            }));
        }
    } while (print_menu(menu_items, true) && !go_back);
};

void Arena::player_death(bool training) {
    player.reset_health();

    if(!training) {
        if(player.get_stat("Gold") > 0) {
            int gold_deducted = enemy.gold_reward() / 2;
            if(gold_deducted < 1) gold_deducted = 1;
            player.decrease_gold(gold_deducted);
            std::cout << "You paid " << enemy.get_name() << " " << gold_deducted << " gold piece(s).\n";
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> hundred_dist(1, 100);
        int loss_roll = hundred_dist(mt);
        if(loss_roll <= player.weapon_drop_chance()) {
            std::cout << enemy.get_name() << " shouts \"You are not worthy of your "
                << player.get_weapon()->ITEM_NAME << "!\" and takes your weapon as you black out.\n";
            player.remove_weapon();
        }
    }
    save_to_file();
    pause_until_enter();
};

void Arena::enemy_death(bool training) {
    pairVec menu_items;

    // Claim gold and experience
    if(!training) {
        player.increase_gold(enemy.gold_reward());
        std::cout << "You are rewarded with " << enemy.gold_reward() << " gold pieces.\n";
    } else {
        player.reset_health();
    }
    player.gain_experience(enemy.experience_reward());
    save_to_file();

    // Check if enemy drops weapon
    if(!training && enemy.weapon_reward()) {
        std::string weapon_name = enemy.get_weapon()->ITEM_NAME;
        std::cout << enemy.get_name() << " is impressed and wants to offer up their "
            << weapon_name << " as a token of respect!\n";
        
        bool early_return = false;
        do {
            menu_items.clear();

            menu_items.push_back(std::make_pair("Blank", []() -> void {}));
            menu_items.push_back(std::make_pair("Take " + weapon_name, [this, &early_return]() -> void {
                player.insert_item(enemy.get_weapon());
                std::cout << "You thank them and humbly accept their "
                    << enemy.get_weapon()->ITEM_NAME << ".\n";
                save_to_file();
                pause_until_enter();
                early_return = true;
            }));
            menu_items.push_back(std::make_pair("Humbly decline", [&early_return]() -> void {
                std::cout << "Although you appreciate the gesture, you decline their offer"
                    << " and let them know you hope to cross paths again.\n";
                pause_until_enter();
                early_return = true;
            }));
        } while(print_menu(menu_items, true) && !early_return);
    }
};