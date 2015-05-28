//
//  Particle.cpp
//  animation1
//
//  Created by Chris Coleman on 4/16/15.
//
//
//Commented by William Karges
#include "Particle.h"



Particle::Particle(){
    live = false; //dont count them until they get setup
}


void Particle::setup(Params *_param) {
    param = _param; //save the params so we can use them locally
    pos = param->eCenter + randomPointInCircle(param->eRad); //generate a random position from the emmiter for the start
    vel = randomPointInCircle(param->velRad); //generate a random direction to go
    time = 0;
    lifeTime = param->lifeTime;
    live = true; //it's alive!!!!
    //hue = 0 ;
    //color = ofColor::blue ;
}


void Particle::update(float dt){
    if (live) {
        vel.rotate(0, 0, param->rotate * dt); //steer the particle over its lifetime
        ofVec3f acc;
        ofVec3f delta = pos - param->eCenter;
        float len = delta.length(); //figure out how far from the center the particle is
        if (ofInRange(len, 0, param->eRad)) { //if distance is below a certain threshhold
            delta.normalize();
            acc += delta * param->force; //add an outward force
            acc.x += -delta.y * param->spinning; //as it moves outward, steer the particle in a counter clockwise direction
            acc.y += delta.x * param->spinning;
        }
        vel += acc * dt; //add the acceleration to the velocity
        vel *= (1-param->friction); //slow the particle down with friction
        
        pos += vel * dt; //change the position with the final velocity
        time += dt; //update the current age of the particle
        if(time >= lifeTime){ //if it is too old, kill the particle
            live = false;
        }
    }
}




void Particle::draw(){
    if(live){
        float size = ofMap(fabs(time-lifeTime/2), 0, lifeTime/2, 3, 1); //make it smaller the older it gets
        ofColor color = ofColor::red; //base color is red (whose hue = 0)
        float hue = ofMap(time, 0, lifeTime, 128, 255); //shift the hue according to the age of the particle
        //hue = time ;
        color.setHue(hue);
        ofSetColor(color);
        ofCircle(pos, size); //draw the particle
    }
}


ofVec3f Particle::randomPointInCircle( float maxRad){ //this function makes random positions inside of a radius
    ofVec3f pnt; //the key is the resulting random positions form a circle rather than a square
    float rad = ofRandom(maxRad);
    float angle = ofRandom(M_TWO_PI);
    pnt.x = cos(angle)*rad;
    pnt.y = sin(angle)*rad;
    pnt.z = 0;
    return pnt;
}