//
//  Rectangle.h
//  batschding
//
//  Created by Johannes Steudle on 24.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    int posX;
    int posY;
    int width;
    int height;
    
public:
    Rectangle(int posX = 0, int posY = 0, int width = 10, int height = 10);
    ~Rectangle();
    
    void setPosition(int x, int y);
    void setSize(int height, int width);
    int getSize();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
};

#endif
