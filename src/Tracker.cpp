//
//  Tracker.cpp
//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Tracker.h"

inline bool between(int n, int t1, int t2) {
    if (t1 < t2) {
        return t1 <= n && n <= t2;
    } else {
        return (t1 <= n && n <= 180) || (0 <= n && n <= t2);
    }
}

inline bool checkIntervalHSV(int h, int s,  int v, Color* color) {
    return     between(h, color->GetHL(), color->GetHH()) 
            && between(s, color->GetSL(), color->GetSH())
            && between(v, color->GetVL(), color->GetVH());
}

inline double calculateDistance(int xr, int xg, int xb, int yr, int yg, int yb) {
    double maxDistance = 195075;
    return (powf(xr-yr, 2) +
            powf(xg-yg, 2) +
            powf(xb-yb, 2)) / maxDistance;
}

Tracker::Tracker(Color* colorP1, Color* colorP2) {
    this->colorP1 = colorP1;
    this->colorP2 = colorP2;
    colorP1->printHSVInterval();
    colorP2->printHSVInterval();
}



Tracker::~Tracker() {
    
}

void Tracker::imageProcessing(IplImage* image, Rectangle* rectangle) {
    cvCvtColor(image, image, CV_BGR2HSV);

    // retrieve properties
    imageWidth     = image->width;
    imageHeight    = image->height;
    imageChannels  = image->nChannels;
    imageStep      = image->widthStep;
    
    int i, j;
    
    // setup the pointer to access image data
    uchar *data = (uchar*) image->imageData;
    
    int s, k, h, sa, v;
    
    // check colors for the whole image
    for(i = 0; i < imageHeight; i++) { 
        for(j = 0; j < imageWidth; j++) { 
            s = i * imageStep;
            k =  j * imageChannels;
            h = *(data + s + k + 0);
            sa = *(data + s + k + 1);
            v = *(data + s + k + 2);
            
            if (checkIntervalHSV(h, sa, v, colorP1)) {
                *(data + s + k + 0) = 0;
                *(data + s + k + 1) = 0;
                *(data + s + k + 2) = 0;
            } else if (checkIntervalHSV(h, sa, v, colorP2)) {
                *(data + s + k + 0) = 90;
                *(data + s + k + 1) = 0;
                *(data + s + k + 2) = 255;
            } else {
                 /**(data + s + k + 2) = 0;
                 *(data + s + k + 1) = 0;
                 *(data + s + k + 0) = 0; */
            }
        }       
    }
    cvCvtColor(image, image, CV_HSV2BGR);
}

bool Tracker::checkColor(Rectangle* rectangle, int i, int j) {
    if (i > rectangle->getPositionY() && j > rectangle->getPositionX() &&
        i < (rectangle->getPositionY() + rectangle->getHeight()) &&
        j < (rectangle->getPositionX() + rectangle->getWidth())) {
        return true;
    }
    return false;
}

int Tracker::checkRectangle(IplImage* image, Rectangle* rectangle) {
    imageWidth     = image->width;
    imageHeight    = image->height;
    imageChannels  = image->nChannels;
    imageStep      = image->widthStep;
    
    int s, k, h, sa, v, i, j;
    int rectSize = rectangle->getSize();
    int positionY2 = rectangle->getPositionY() + rectangle->getHeight();
    int positionX2 = rectangle->getPositionX() + rectangle->getWidth();
    
    uchar *data = (uchar*)image->imageData;
    cvCvtColor(image, image, CV_BGR2HSV);
    
    // Farbe im Rechteck extrahieren, prozentualen Anteil der Farbe ermitteln
    for (i = rectangle->getPositionY(); i < positionY2; i++) {
        for (j = rectangle->getPositionX(); j < positionX2; j++) {
            s = i * imageStep;
            k =  j * imageChannels;
            h = *(data + s + k + 0);
            sa = *(data + s + k + 1);
            v = *(data + s + k + 2);
            
            if (checkIntervalHSV(h, sa, v, colorP1))
                countP1++;
            if (checkIntervalHSV(h, sa, v, colorP2))
                countP2++;
        }
    }
    
  //  printf("countP1: %d, countP2: %d\n", countP1, countP2);
    
    cvCvtColor(image, image, CV_HSV2BGR);
    
    if (countP1 > countP2 && countP1 >= rectSize) {
        return 1;
    } else if (countP1 < countP2 && countP2 >= rectSize) {
        return 2;
    }
    return 0;
}

int Tracker::getCountP1() {
    return countP1;
}

int Tracker::getCountP2() {
    return countP2;
}

void Tracker::setCountsZero() {
    this->countP1 = 0;
    this->countP2 = 0;
}
