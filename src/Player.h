//
//  Player.h
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "Color.h"


class Player {
    int score;
    int number;
    Color* color;
    
public:
    Player(int number, Color* color);
    ~Player(void);
    
    Color* getColor(void);
    int getScore(void);
    void increaseScore(int points);
};