//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef COLOR_H
#define	COLOR_H

#include <stdio.h>

class Color {
private:
    int h;
    int s;
    int v;
    int interval[3][2];
public:
    Color(int h, int s, int v);
    Color(Color& orig);
    
    virtual ~Color();
    
    void calcHSVInterval();
    void printHSVInterval() const;
    
    int GetVH() const;
    int GetVL() const;
    int GetSH() const;
    int GetSL() const;
    int GetHH() const;
    int GetHL() const;
    
    int GetV() const;
    int GetS() const;
    int GetH() const;
private:
    
};

#endif	/* COLOR_H */

