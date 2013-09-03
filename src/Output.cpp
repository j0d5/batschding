//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Output.h"

Output::Output() {
    rectangle = new Rectangle(0, 0, 50, 50);
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);
}

void Output::drawRectOnRandomPos(IplImage* img) {
    
    srand ( time(NULL) );
    
    rectangle->setPosition(rand() 
                           % (img->width - rectangle->getWidth()), 
                           rand() 
                           % (img->height - rectangle->getHeight()));
    
}

void Output::drawRectangle(IplImage* img, Rectangle* rectangle) {
    cvRectangle(img, 
                cvPoint(rectangle->getPositionX(), rectangle->getPositionY()), 
                cvPoint(rectangle->getPositionX() + rectangle->getWidth(),
                        rectangle->getPositionY() + rectangle->getHeight()),
                cvScalar(255,0,0), 1);
    
}

void Output::printText(IplImage* img, string text, int posX, int posY) {
    cvPutText(img, text.c_str(), cvPoint(posX, posY), &font, cvScalar(0, 255, 0, 0));
}

Rectangle* Output::getRectangle() {
    return this->rectangle;
}
