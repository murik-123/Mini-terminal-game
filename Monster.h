#pragma once
#include "Player.h"

class Monster {
public:
    int monster_health = 250;

    virtual ~Monster() = default;

    virtual int monster_damage();

    void attack_monster(Player& p, int damage);
    void damage_player(const Player& p);
    void charge_player(const Player& p);
};

class Goblin : public Monster {
public:
    Goblin();
    int monster_damage() override;
};

class Dragon : public Monster {
public:
    Dragon();
    int monster_damage() override;
};

