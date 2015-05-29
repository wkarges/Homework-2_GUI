//
//
//Project created by Christopher Coleman
//Commented and edited by William Karges
//
//
//



#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate(w, h, GL_RGB32F_ARB); //set aside a framebuffer with 32bit colors
    
    fbo.begin();
    ofClear(255, 255, 255); //make sure we start with a clean slate in the FBO
    fbo.end();
    
    param.setup(); //param is where we store a bunch of global variables
    history = 0.9; //how quickly the trails fade out
    bornRate = 1500; //particles per second
    bornCount = 0; //keep track of how many particles there are.
    
    forceSlide.addListener(this, &ofApp::forceChanged); //listen for when the gui slider is changed
    lifeSlide.addListener(this, &ofApp::lifeChanged) ;
    rateSlide.addListener(this, &ofApp::rateChanged) ;
    rotationSlide.addListener(this, &ofApp::rotChanged) ;
    //colorSlide.addListener(this, &ofApp::hueChanged) ;
    
    gui.setup();
    gui.add(forceSlide.setup( "Force", 0, -2000, 3000 )); //the slider defaults to 0 and ranges from -2000 to 3000
    gui.add(lifeSlide.setup( "Particle LifeTime", 2, .5, 3)) ;
    gui.add(rateSlide.setup( "ParticlesPerSec", 1500, 350, 3000)) ;
    gui.add(rotationSlide.setup( "Rotation", -200, -400, 200)) ;
    //gui.add(colorSlide.setup("Color", newHue, 0, 255)) ;
    time0 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::forceChanged(float &forceSlide){
        param.force = forceSlide; //when the slider is updated, update the value of force in our instance of Params
}

//--------------------------------------------------------------
void ofApp::lifeChanged(float &lifeSlide) {
    param.lifeTime = lifeSlide ;
}

//--------------------------------------------------------------
void ofApp::rateChanged(float &rateSlide) {
    bornRate = rateSlide ;
}
//--------------------------------------------------------------
void ofApp::rotChanged(float &rotationSlide) {
    param.rotate = rotationSlide ;
}
/*
void ofApp::hueChanged(float &colorSlide) {
    particle.hue = colorSlide ;
}
*/

//--------------------------------------------------------------
void ofApp::update(){
    
    //newHue = particle.hue ;
    
    float time = ofGetElapsedTimef();
    float dt = ofClamp(time - time0, 0, 0.1); //get the elapsed time between frames and make sure it is between 0-0.1
    time0 = time; //reset our time
    
    //This loop erases dead particles from array
    int i=0;
    while(i<p.size()) {  //this while loop is almost like a for loop but it accounts for the erased particles
        if(!p[i].live){ //check to see if the particle is still alive
            p.erase(p.begin()+i); //erase any dead ones
        }
        else {
            ++i; //if the particle is alive, move on to the next one
        }
    }
    
    bornCount += dt*bornRate; //add more particles
    if(bornCount >=1) {
        int bornN = int(bornCount); //truncate any fractions for what we will birth this loop
        bornCount -= bornN; //subtract the ones we will birth, leaving only the fractions
        for (int i=0; i<bornN; ++i) {
            Particle newP; //make a new particle
            newP.setup(&param); //setup the new particle with a reference to the params
            p.push_back(newP); //add the particle to the vector
        }
    }
    for (int i=0; i<p.size(); ++i) {
        p[i].update(dt); //go thru the vector of particles and update them all
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    fbo.begin(); //start the fbo
    ofEnableAlphaBlending();
    float alpha = (1-history)*255; //calculate how trasparent the new background will be
    ofSetColor(255, 255, 255, alpha);
    ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight()); //cover the window in a semi-transparent rectangle
    ofDisableAlphaBlending();
    
    ofFill();
    for (int i=0; i<p.size(); ++i) {
        p[i].draw(); //draw all the particles
    }
    
    fbo.end(); //close the fbo
    
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0); //draw the contents of the fbo
    gui.draw(); //draw the gui
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
