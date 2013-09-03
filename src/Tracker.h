//
//  Tracker.h
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef TRACKER_H
#define TRACKER_H

#include <cv.h>
#include <math.h>
#include "Color.h"
#include "Rectangle.h"
using namespace std;


class Tracker {
    Color* colorP1;
    Color* colorP2;
    
    int countP1;
    int countP2;
    
    int imageWidth;
    int imageHeight;
    int imageChannels;
    int imageStep;
    
public:
    Tracker(Color* colorP1, Color* colorP2);
    ~Tracker();
    
    void imageProcessing(IplImage* image, Rectangle* rectangle);
    bool checkColor(Rectangle* rectangle, int i, int j);
    int checkRectangle(IplImage* image, Rectangle* rectangle);
    int getCountP1();
    int getCountP2();
    void setCountsZero();
};

#endif
