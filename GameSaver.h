#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "Player.h"
#include "Monster.h"

void saveGameJSON(const Player& p, const Monster& m, const std::string& name, const std::vector<std::string>& history, const std::string& monster_type);

void loadGameJSON(Player& p, std::unique_ptr<Monster>& m, std::string& name, std::vector<std::string>& history, std::string& monster_type);

