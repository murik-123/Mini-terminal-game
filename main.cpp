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

    class Game {
    public:
        int monster_health = 300;
        int player_health = 150;

        int player_damage = 30;
        int player_charge = 50;
        int monster_damage = 25;
    };
}

int main() {
    json gameData;
    int choice = 0;
    Game game;

    std::vector<std::string> action_history;

    welcome_page();

    std::cout << "Create your nickname: ";
    auto nickname = new std::string;
    std::getline(std::cin, *nickname);

    std::cout << "Hello, " << *nickname << "!\n\n";

    while (game.monster_health > 0 && game.player_health > 0) {
        std::cout << "-----------------------------------\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        if (choice == 1) {
            game.monster_health -= game.player_damage;
            std::cout << "You dealt " << game.player_damage << " hp to the monster.\n";
            std::cout << "Monster health: " << game.monster_health << "\n";

            action_history.emplace_back("Attacked monster for 30 damage");
        }
        else if (choice == 2) {
            game.player_health += 20;
            std::cout << "You healed 20 HP! Player health: " << game.player_health << "\n";

            action_history.emplace_back("Healed 20 HP");
        }
        else if (choice == 3) {
            game.monster_health -= game.player_charge;
            std::cout << "You dealt " << game.player_charge << " hp to the monster.\n";
            std::cout << "Monster health: " << game.monster_health << "\n";

            action_history.emplace_back("Used charge attack for 50 damage");
        }
        else if (choice == 4) {
            std::cout << "See ya!\n";
            action_history.emplace_back("Exited game manually");

            gameData["action_history"] = action_history;

            delete nickname;
            return 0;
        }
        else {
            std::cout << "Please enter a number from 1-4.\n";
            continue;
        }

        if (game.monster_health > 0) {
            game.player_health -= game.monster_damage;
            std::cout << "Monster dealt " << game.monster_damage << " damage to you!\n";
            std::cout << "Your health: " << game.player_health << "\n";

            action_history.emplace_back("Monster counter-attacked for 25 damage");
        }
    }

    if (game.monster_health <= 0) {
        std::cout << "\nCongratulations " << *nickname << ", You won!\n";
        action_history.emplace_back("Won the game");
    }
    else if (game.player_health <= 0) {
        std::cout << "\nGame over " << *nickname << ", You lost!\n";
        action_history.emplace_back("Lost the game");
    }

    gameData["d) player_actions_history"] = action_history;
    gameData["b) player_health"] = game.player_health;
    gameData["c) monster_health"] = game.monster_health;
    gameData["a) player_name"] = *nickname;

    std::ofstream outFile("Save_game.json");

    if (outFile.is_open()) {
        outFile << std::setw(4) << gameData << std::endl;
        outFile.close();
        std::cout << "Game saved successfully with action history!\n";
    } else {
        std::cout << "Unable to save Save_game.json\n";
    }

    delete nickname;
    nickname = nullptr;

    return 0;
}

