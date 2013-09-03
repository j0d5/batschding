//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef OUTPUT_H
#define OUTPUT_H

#include <math.h>
#include <string>
#include "cv.h"
#include "cxcore.h"
#include "Rectangle.h"

using namespace std;

class Output {
    Rectangle* rectangle;
    
private:
    CvFont font;
    
public:
    Output();
    
    void drawRectOnRandomPos(IplImage* image);
    void drawRectangle(IplImage* image, Rectangle* rectangle);
    void printText(IplImage* img, string text, int posX, int posY);
    Rectangle* getRectangle();
};
#endif
