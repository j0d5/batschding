//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Calibrator.h"
#include "cv.h"

Calibrator::Calibrator() {
}

Calibrator::Calibrator(const Calibrator& orig) {
    this->img = orig.img;
}

Calibrator::~Calibrator() {
}

Color* Calibrator::getColorAtPosition(const int x, const int y) const {
    cvCvtColor(img, img, CV_BGR2HSV);
    int** surroundings = calculateSurroundingArea(x, y);
    
    //printf("Mouse %d x %d\n", x, y);
    
    int sumH = 0;
    int sumS = 0;
    int sumV = 0;
    int count = 1;
    int currentX = 0;
    int currentY = 0; 
    int step = img->widthStep;
    int channels = img->nChannels;
    uchar *data = (uchar *)img->imageData;
    
    //printf("Image %d x %d\n", img->width, img->height);
    
    for (int i = 0; i < AREA_PIXEL_COUNT; i++) {
        currentX = surroundings[i][0];
        currentY = surroundings[i][1];
        
        //printf("Check %d x %d ", currentX, currentY);
        
        if (isValidPosition(currentX, currentY)) {
            sumH += data[currentY*step+currentX*channels+0];
            sumS += data[currentY*step+currentX*channels+1];
            sumV += data[currentY*step+currentX*channels+2];
            /*printf("h: %d s: %d v: %d\n", data[currentY*step+currentX*channels+0],
            data[currentY*step+currentX*channels+1],
            data[currentY*step+currentX*channels+2]);*/
            ++count;
        }
    }
    
    //printf("hsum %d ssum %d vsum %d", sumH, sumS, sumV);
    
    delete surroundings;
    
    cvCvtColor(img, img, CV_HSV2BGR);
    return new Color((int) sumH/count, (int) sumS/count, (int) sumV/count);
}

void Calibrator::setCurrentImage(IplImage* img) {
    this->img = img;
}

bool Calibrator::isValidPosition(int x, int y) const {
    return x >= 0 &&  y >= 0
        && x <= img->width - 1 && y <= img->height - 1;    
}

int** Calibrator::calculateSurroundingArea(const int x, const int y) const {
    int** surroundings = new int*[AREA_PIXEL_COUNT];
    
    int k = 0;
    for (int i = -AREA; i <= AREA; i++) {
        for (int j = -AREA; j <= AREA; j++) {
            surroundings[k] = new int[2];
            surroundings[k][0] = x + i;
            surroundings[k][1] = y + j;
            ++k;
        }
    }

    return surroundings;
}
