//
//  Params.cpp
//  animation1
//
//  Created by Chris Coleman on 4/16/15.
//
//

#include "Params.h"

void Params::setup(){
    eCenter = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 10);
    eRad = 100;
    velRad = 0;
    lifeTime = 2.0;
    rotate = -200;
    force = 1000;
    spinning = 1000;
    friction = 0.05;
}
