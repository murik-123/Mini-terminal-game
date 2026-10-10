#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <iomanip>

using json = nlohmann::json;

namespace {
    void welcome_page() {
        std::cout << "Welcome to the game!\n"
                  << "Controls:\n"
                  << "Press 1 to attack\n"
                  << "Press 2 to heal\n"
                  << "Press 3 to charge attack\n"
                  << "Press 4 to exit\n";
    }

    class Monster;

    class Player {
    public:
        int player_health = 150;
        int player_damage = 30;
        int player_charge = 50;

        void heal_player() {
            player_health += 20;
        }
    };
    class Monster {
        public:
        int monster_health = 250;
        int monster_damage = 25;

        void attack_monster(Player& p) const {
            p.player_health -= monster_damage;
        }
        void damage_player(const Player& p) {
            monster_health -= p.player_damage;
        }
        void charge_player(const Player& p) {
            monster_health -= p.player_charge;
        }
    };

}

int main() {
    json gameData;
    int choice = 0;
    Player p;
    Monster m;

    std::vector<std::string> action_history;

    welcome_page();

    std::cout << "Create your nickname: ";
    std::string nickname;
    std::getline(std::cin, nickname);

    std::cout << "Hello, " << nickname << "!\n\n";

    while (m.monster_health > 0 && p.player_health > 0) {
        std::cout << "-----------------------------------\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        if (choice == 1) {
            m.damage_player(p);
            std::cout << "You dealt " << p.player_damage << " hp to the monster.\n";
            std::cout << "Monster health: " << m.monster_health << "\n";

            action_history.emplace_back("Attacked monster for 30 damage");
        }
        else if (choice == 2) {
            p.heal_player();
            std::cout << "You healed 20 HP! Player health: " << p.player_health << "\n";

            action_history.emplace_back("Healed 20 HP");
        }
        else if (choice == 3) {
            m.charge_player(p);
            std::cout << "You dealt " << p.player_charge << " hp to the monster.\n";
            std::cout << "Monster health: " << m.monster_health << "\n";

            action_history.emplace_back("Used charge attack for 50 damage");
        }
        else if (choice == 4) {
            std::cout << "See ya!\n";
            action_history.emplace_back("Exited game manually");

            gameData["action_history"] = action_history;

            return 0;
        }
        else {
            std::cout << "Please enter a number from 1-4.\n";
            continue;
        }

        if (m.monster_health > 0) {
            m.attack_monster(p);
            std::cout << "Monster dealt " << m.monster_damage << " damage to you!\n";
            std::cout << "Your health: " << p.player_health << "\n";

            action_history.emplace_back("Monster counter-attacked for 25 damage");
        }
    }

    if (m.monster_health <= 0) {
        std::cout << "\nCongratulations " << nickname << ", You won!\n";
        action_history.emplace_back("Won the game");
    }
    else if (p.player_health <= 0) {
        std::cout << "\nGame over " << nickname << ", You lost!\n";
        action_history.emplace_back("Lost the game");
    }

    gameData["d) player_actions_history"] = action_history;
    gameData["b) player_health"] = p.player_health;
    gameData["c) monster_health"] = m.monster_health;
    gameData["a) player_name"] = nickname;

    std::ofstream outFile("Save_game.json");

    if (outFile.is_open()) {
        outFile << std::setw(4) << gameData << std::endl;
        outFile.close();
        std::cout << "Game saved successfully with action history!\n";
    } else {
        std::cout << "Unable to save Save_game.json\n";
    }

    return 0;
}