//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CALIBRATOR_H
#define	CALIBRATOR_H

#include <sys/types.h>
#include <stdio.h>
#include "cv.h"
#include "Color.h"
#include "stdio.h"

class Calibrator {
private:
    IplImage* img;
    
    /*
     * Pixels considered in the surrounding of x/y coordinates.
     */
    static const int AREA = 1;
    static const int AREA_DIMENSION = AREA*2+1;
    static const int AREA_PIXEL_COUNT = AREA_DIMENSION * AREA_DIMENSION;
    
    bool isValidPosition(int x, int y) const;
    int** calculateSurroundingArea(const int x, const int y) const;
    
public:
    Calibrator();
    Calibrator(const Calibrator& orig);
    
    void setCurrentImage(IplImage* img);
    Color* getColorAtPosition(const int x, const int y) const;
    
    virtual ~Calibrator();
};

#endif	/* CALIBRATOR_H */

