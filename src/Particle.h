//
//  Particle.h
//  animation1
//
//  Created by Chris Coleman on 4/16/15.
//
//

#ifndef __animation1__Particle__
#define __animation1__Particle__

#include "ofMain.h"
#include "Params.h"


class Particle {

public:
    Particle();
    
    void setup(Params *_param);
    void update(float dt);
    void draw();
    
    ofVec3f randomPointInCircle(float maxRad);
    
    ofVec3f pos, vel;
    float time, lifeTime;
    //float hue ;
    bool live;
    Params *param;
    
    
};

#endif /* defined(__animation1__Particle__) */
