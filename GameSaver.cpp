#include "GameSaver.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void saveGameJSON(const Player& p, const Monster& m, const std::string& name, const std::vector<std::string>& history, const std::string& monster_type) {
    std::ofstream outFile("save_game.json");

    if (outFile.is_open()) {
        json saveData;
        saveData["player_name"] = name;
        saveData["player_health"] = p.player_health;
        saveData["monster_type"] = monster_type;
        saveData["monster_health"] = m.monster_health;
        saveData["action_history"] = history;

        outFile << saveData.dump(4);
        outFile.close();
        std::cout << "\n[SUCCESS] Game and history saved to save_game.json!\n";
    } else {
        std::cerr << "\n[ERROR] Could not create JSON save file.\n";
    }
}

void loadGameJSON(Player& p, std::unique_ptr<Monster>& m, std::string& name, std::vector<std::string>& history, std::string& monster_type) {
    std::ifstream inFile("save_game.json");

    if (inFile.is_open()) {
        json saveData;
        inFile >> saveData;

        name = saveData["player_name"].get<std::string>();
        p.player_health = saveData["player_health"].get<int>();
        monster_type = saveData["monster_type"].get<std::string>();

        if (monster_type == "Goblin") {
            m = std::make_unique<Goblin>();
        } else {
            m = std::make_unique<Dragon>();
        }

        m->monster_health = saveData["monster_health"].get<int>();
        history = saveData["action_history"].get<std::vector<std::string>>();

        inFile.close();
        std::cout << "\n[SUCCESS] Game state and action history loaded successfully!\n";
    } else {
        std::cout << "\n[WARNING] No save file found. Continuing current state.\n";
    }
}

