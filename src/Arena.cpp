#include <iostream>
#include <random>

#include "Arena.h"
#include "utility.h"

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

        if(player.can_defend()) {
            menu_items.push_back(std::make_pair("Defend", [this]() -> void {
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
        }

        menu_items.push_back(std::make_pair("Check Consumables", [this]() -> void {
            std::cout << "Feature in progress\n";
            pause_until_enter();
            // If player doesn't use consumable, don't do any of the following
            // pre_round_checks(player);
            // if(!enemy.is_defending()) process_attack(enemy, player);
            // continue_round = true;
        }));

        menu_items.push_back(std::make_pair("Check Statistics", [this]() -> void {
            print_stats();
        }));

    } while(print_menu(menu_items, true) && player.is_alive() && enemy.is_alive());

    // Reset cooldowns
    player.clear_cooldowns();

    // Check for deaths
    if(!enemy.is_alive()) enemy_death();
    else if(!player.is_alive()) player_death();
    else {
        std::cout << "Something went wrong -> Fight ended but both fighters have health\n";
        pause_until_enter();
    }

    // Generate new enemy for a future fight
    enemy = Enemy::generate_enemy(tier);
};

void Arena::train_menu() {
    std::cout << "You will have to pay gold to train.\n";
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
        std::cout << defender.get_name() << " has chosen to defend!\n";
        e_defense *= 2;
    }

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
    else pause_until_enter();
};

void Arena::print_stats() {
    std::cout << "Names:\t\t" << player.get_name() << "\t" << enemy.get_name() << " [Foe]\n";
    std::cout << "Health:\t\t"
        << player.get_stat("Health") << "/" << player.get_stat("Max Health")
        << "\t" << enemy.get_stat("Health") << "/" << enemy.get_stat("Max Health") << "\n";
    std::cout << "Attack:\t\t" << player.get_stat("Attack") << "\t" << enemy.get_stat("Attack") << "\n";
    std::cout << "Acc.:\t\t" << player.get_stat("Accuracy") << "\t" << enemy.get_stat("Accuracy") << "\n";
    std::cout << "Def.:\t\t" << player.get_stat("Defense") << "\t" << enemy.get_stat("Defense") << "\n";
    std::cout << "Level:\t\t" << player.get_stat("Level") << "\t" << enemy.get_stat("Level") << "\n";
    std::cout << player.get_name() << "'s weapon: "
        << player.get_weapon()->ITEM_NAME << " [+" << player.get_weapon()->ATTACK_MOD << "]\n";
    std::cout << "[Foe] " << enemy.get_name() << "'s weapon: "
        << enemy.get_weapon()->ITEM_NAME << " [+" << enemy.get_weapon()->ATTACK_MOD << "]\n";
    pause_until_enter();
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
    }
    player.gain_experience(enemy.experience_reward());
    save_to_file();

    // Check if enemy drops weapon
    if(!training && enemy.weapon_reward()) {
        std::string weapon_name = enemy.get_weapon()->ITEM_NAME;
        std::cout << enemy.get_name() << " is impressed and wants to offer up their "
            << weapon_name << " as a token of respect!\n";
        
        menu_items.clear();

        menu_items.push_back(std::make_pair("Blank", []() -> void {}));
        menu_items.push_back(std::make_pair("Take " + weapon_name, [this]() -> void {
            player.insert_item(enemy.get_weapon());
            std::cout << "You thank them and humbly accept their "
                << enemy.get_weapon()->ITEM_NAME << ".\n";
            save_to_file();
            pause_until_enter();
        }));
        menu_items.push_back(std::make_pair("Humbly decline", []() -> void {
            std::cout << "Although you appreciate the gesture, you decline their offer"
                << " and let them know you hope to cross paths again.\n";
            pause_until_enter();
        }));

        print_menu(menu_items, true);
    }
};