#include "include_file.h"
using json = nlohmann::json;

static void welcome_page() {
    std::cout << "Welcome to the game!\n"
              << "Controls:\n"
              << "Press 1 to attack\n"
              << "Press 2 to heal\n"
              << "Press 3 to charge attack\n"
              << "Press 4 to MANUAL SAVE\n"
              << "Press 5 to MANUAL LOAD\n"
              << "Press 6 to exit\n";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choice = 0;
    Player p;
    std::unique_ptr<Monster> m;
    std::string monster_type;
    std::string nickname;
    std::vector<std::string> action_history;

    welcome_page();

    std::cout << "Create your nickname: ";
    std::getline(std::cin, nickname);
    std::cout << "Hello, " << nickname << "!\n\n";

    if (std::rand() % 2 == 0) {
        m = std::make_unique<Goblin>();
        monster_type = "Goblin";
        std::cout << "A sneaky Goblin appears!\n";
    } else if (std::rand() % 2 == 0) {
        m = std::make_unique<Dragon>();
        monster_type = "Dragon";
        std::cout << "A terrifying Dragon appears!\n";
    }else{
        m = std::make_unique<Bat>();
        monster_type = "Bat";
        std::cout << "A terrifying Bat appears!\n";
    }


    while (m->monster_health > 0 && p.player_health > 0) {
        std::cout << "-----------------------------------\n";
        std::cout << "Player HP: " << p.player_health << " | " << monster_type << " HP: " << m->monster_health << "\n";
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        if (choice == 1) {
            m->damage_player(p);
            std::cout << "You dealt " << p.player_damage << " hp to the " << monster_type << ".\n";
            action_history.emplace_back("Attacked " + monster_type + " for 30 damage");
        }
        else if (choice == 2) {
            p.heal_player();
            std::cout << "You healed 20 HP!\n";
            action_history.emplace_back("Healed 20 HP");
        }
        else if (choice == 3) {
            m->charge_player(p);
            std::cout << "You dealt " << p.player_charge << " hp to the " << monster_type << ".\n";
            action_history.emplace_back("Used charge attack for 50 damage");
        }
        else if (choice == 4) {
            action_history.emplace_back("Manually saved the game");
            saveGameJSON(p, *m, nickname, action_history, monster_type);
            continue;
        }
        else if (choice == 5) {
            loadGameJSON(p, m, nickname, action_history, monster_type);
            action_history.emplace_back("Manually loaded a save");
            continue;
        }
        else if (choice == 6) {
            std::cout << "\n--- Exiting Game Without Saving ---\n";
            return 0;
        }
        else {
            std::cout << "Please enter a number from 1-6.\n";
            continue;
        }

        if (m->monster_health > 0) {
            int m_dmg = m->monster_damage();
            m->attack_monster(p, m_dmg);
            std::cout << "The " << monster_type << " dealt " << m_dmg << " damage to you!\n";
            action_history.emplace_back(monster_type + " counter-attacked for " + std::to_string(m_dmg) + " damage");
        }
    }

    if (m->monster_health <= 0) {
        std::cout << "\nCongratulations " << nickname << ", You won against the " << monster_type << "!\n";
        action_history.emplace_back("Won the game");
    }
    else if (p.player_health <= 0) {
        std::cout << "\nGame over " << nickname << ", You lost!\n";
        action_history.emplace_back("Lost the game");
    }

    json game_data;
    game_data["a) player_name"] = nickname;
    game_data["b) player_health"] = p.player_health;
    game_data["c) monster_type"] = monster_type;
    game_data["d) monster_health"] = m->monster_health;
    game_data["e) player_actions_history"] = action_history;

    std::ofstream outFile("game_summary.json");

    if (outFile.is_open()) {
        outFile << std::setw(4) << game_data << std::endl;
        outFile.close();
        std::cout << "Session complete. History compiled in game_summary.json!\n";
    } else {
        std::cout << "Unable to save game_summary.json\n";
        return 0;
    }

    return 0;
}
