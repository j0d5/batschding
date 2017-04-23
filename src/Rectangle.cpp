//
//  Rectangle.cpp
//  batschding
//
//  Created by Johannes Steudle on 24.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Rectangle.h"

Rectangle::Rectangle(int posX, int posY, int width, int height) {
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
}

void Rectangle::setPosition(int x, int y) {
	this->posX = x;
	this->posY = y;
}


void Rectangle::setSize(int width, int height) {
    this->height = height;
    this->width = width;
}

int Rectangle::getSize() {
    return this->width * this->height;
}

int Rectangle::getWidth() {
    return this->width;
}

int Rectangle::getHeight() {
    return this->height;
}

int Rectangle::getPositionX() {
    return this->posX;
}

int Rectangle::getPositionY() {
    return this->posY;
}
