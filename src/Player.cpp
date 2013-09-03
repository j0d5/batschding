//
//  Player.cpp
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "Player.h"

Player::Player(int number, Color* color) {
    this->number = number;
    // this->color = color;
		this->score = 0;
}

Player::~Player(void) {
    
}

Color* Player::getColor() {
    return this->color;
}

int Player::getScore() {
    return this->score;
}

void Player::increaseScore(int points) {
    this->score += points;
}
