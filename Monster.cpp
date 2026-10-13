#include "Monster.h"
#include <cstdlib>
int Monster::monster_damage() {
    return (std::rand() % 21) + 15;
}

void Monster::attack_monster(Player& p, int damage) {
    p.player_health -= damage;
}

void Monster::damage_player(const Player& p) {
    monster_health -= p.player_damage;
}

void Monster::charge_player(const Player& p) {
    monster_health -= p.player_charge;
}

Goblin::Goblin() {
    monster_health = 180;
}

int Goblin::monster_damage() {
    return (std::rand() % 10) + 10;
}

Dragon::Dragon() {
    monster_health = 350;
}

int Dragon::monster_damage() {
    return (std::rand() % 16) + 25;
}

Bat::Bat() {
    monster_health = 100;
}

int Bat::monster_damage() {
    return (std::rand() % 10) + 5;
}
