//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>

#include "Color.h"

Color::Color(int h, int s, int v) {
    this->h = h;
    this->s = s;
    this->v = v;
    this->calcHSVInterval();
}

Color::Color(Color& orig) {
    this->h = orig.h;
    this->s = orig.s;
    this->v = orig.v;
    this->calcHSVInterval();
}

Color::~Color() {
}

void Color::calcHSVInterval() {
    if (h - 10 > 0 || h + 10 < 180) {
        interval[0][0] = std::max(0, h - 10);
        interval[0][1] = std::min(180, h + 10);
    } else {
        interval[0][0] = std::min(180, h - 10);
        interval[0][1] = std::max(0, h + 10);
    }
    
    interval[1][0] = std::max(0,s - 30);
    interval[1][1] = std::min(255, s + 30);
    
    interval[2][0] = std::max(0,v - 80);
    interval[2][1] = std::min(255, v + 80);
}

void Color::printHSVInterval() const {
     printf("h: [%d,%d] s: [%d,%d] v: [%d,%d]\n",
            interval[0][0],
            interval[0][1],
            interval[1][0],
            interval[1][1],
            interval[2][0],
            interval[2][1]);   
}

int Color::GetHL() const {
    return interval[0][0];
}

int Color::GetHH() const {
    return interval[0][1];
}

int Color::GetSL() const {
    return interval[1][0];
}

int Color::GetSH() const {
    return interval[1][1];
}

int Color::GetVL() const {
    return interval[2][0];
}

int Color::GetVH() const {
    return interval[2][1];
}

int Color::GetV() const {
    return v;
}

int Color::GetS() const {
    return s;
}

int Color::GetH() const {
    return h;
}

