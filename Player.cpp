#include "Player.h"
#include <iostream>
void Player::heal_player() {
    player_health += 35;
}

void Player::difficulty_player(){
    char difficulty;
    std::cin >> difficulty;

    if(difficulty == 'E' || difficulty == 'e') {
        player_health = 250;
        player_damage = 50;
        player_charge = 70;
    }
    else if ( difficulty == 'M' || difficulty == 'm') {
        player_health = 200;
        player_damage = 35;
        player_charge = 40;
    }
    else if ( difficulty == 'H' || difficulty == 'h') {
        player_health = 120;
        player_damage = 25;
        player_charge = 35;
    }
    else {
        std::cout << "Invalid choice :( " << std::endl;
    }
}