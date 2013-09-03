//
//  Gamelogic.h
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "Player.h"
#include "Tracker.h"
#include "Calibrator.h"
#include "Output.h"

using namespace std;

class Gamelogic {
    Player* player1;
    Player* player2;
    Color* colorP1;
    Color* colorP2;
    
    Tracker* tracker;
    Calibrator* calibrator;
    Output* output;
    
    int state;
    int mouseX;
    int mouseY;
    int mouseClicked;
    int rectTimer;

    void play();
    
public:
    Gamelogic();
    ~Gamelogic(void);
    
    bool processImage(IplImage* image);
    void setMousePointer(int x, int y);
};

#endif
