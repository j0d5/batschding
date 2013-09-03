//
//  Gamelogic.cpp
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Gamelogic.h"

#define STATUS_INIT   0
#define STATUS_INIT_P1 1
#define STATUS_INIT_P2 2
#define STATUS_START_GAME 3
#define STATUS_END_GAME 4
#define MAX_SCORE 1000
#define RECT_REFRESH_TIME 30

Gamelogic::Gamelogic() {
    this->colorP1 = NULL;
    this->colorP2 = NULL;
    this->player1 = NULL;
    this->player2 = NULL;
    this->tracker = NULL;
    this->calibrator = new Calibrator();
    this->mouseClicked = false;
    this->mouseX = 0;
    this->mouseY = 0;
    this->rectTimer = 0;
    this->state = STATUS_INIT;
    this->output = new Output();
}

Gamelogic::~Gamelogic(void) {
    if (this->colorP1 != NULL)
        delete this->colorP1;
    if (this->colorP2 != NULL)
        delete this->colorP2;
    if (this->player1 != NULL)
        delete this->player1;
    if (this->player2 != NULL)
        delete this->player2;
    if (this->tracker != NULL)
        delete this->tracker;
    if (this->calibrator != NULL)
        delete this->calibrator;
    delete this->output;
}

bool Gamelogic::processImage(IplImage* image) {
    if (state == STATUS_INIT) {
        state = STATUS_INIT_P1;
    }
    if (state == STATUS_INIT_P1) {
        // Output message for initializing player 1
        output->printText(image, "Initialize player one", 100, 50);
        
        // wait for mouseclick
        if (mouseClicked) {
            mouseClicked = false;
            calibrator->setCurrentImage(image);
            // Frame an calibrator
            // if (colorP1 == NULL)
                colorP1 = calibrator->getColorAtPosition(mouseX, mouseY);
            printf("h: %d, s: %d, v: %d\n", colorP1->GetH(), 
                   colorP1->GetS(), colorP1->GetV());
            player1 = new Player(0, colorP1);
            state = STATUS_INIT_P2;
        }
    } else if (state == STATUS_INIT_P2) {
        // Output message for initializing player 2
        output->printText(image, "Initialize player two", 100, 50);
        
        // wait for mouseclick
        if (mouseClicked) {
            mouseClicked = false;
            calibrator->setCurrentImage(image);
            // Frame an calibrator
            // if (colorP2 == NULL)
                colorP2 = calibrator->getColorAtPosition(mouseX, mouseY);
            printf("h: %d, s: %d, v: %d\n", colorP2->GetH(), 
                   colorP2->GetS(), colorP2->GetV());
            player2 = new Player(1, colorP2);
            tracker = new Tracker(colorP1, colorP2);
            state = STATUS_START_GAME;
        }
    } else if (state == STATUS_START_GAME) {
        char str_temp[100];
        
        sprintf(str_temp, "Spieler 1: %d", player1->getScore());
        output->printText(image, str_temp, 20, 430);
        sprintf(str_temp, "Spieler 2: %d", player2->getScore());
        output->printText(image, str_temp, 20, 460);
        if (rectTimer == RECT_REFRESH_TIME) {
            output->drawRectOnRandomPos(image);
            rectTimer = 0;
            //printf("Score P1: %d, Score P2: %d\n", tracker->getCountP1(), tracker->getCountP2());
	    //					printf("New round\n");
            tracker->setCountsZero();
        } else
            rectTimer++;
        
        output->drawRectangle(image, output->getRectangle());
        
        int winner = tracker->checkRectangle(image, output->getRectangle());
       // tracker->imageProcessing(image, output->getRectangle());
        if (winner == 1) {
            player1->increaseScore(10);
        } else if (winner == 2) {
            player2->increaseScore(10);
        }
        
        if (player1->getScore() > MAX_SCORE || player2->getScore() > MAX_SCORE) {
            state = STATUS_END_GAME;
        }
        
    } else if (state == STATUS_END_GAME) {
        output->printText(image, "Game ended", 100, 50);
        return false;
    }
    return true;
}

void Gamelogic::setMousePointer(int x, int y) {
    this->mouseX = x;
    this->mouseY = y;
    this->mouseClicked = true;
}

void Gamelogic::play() {
    while (state != STATUS_END_GAME) {
        // wenn spielerfarbe in rechteck addiere punktzahl
        // player1->increaseScore(10);
    }
}

