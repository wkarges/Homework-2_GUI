#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Params.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    Params param;
    vector<Particle> p;
    Particle particle ;
    ofFbo fbo;
    float history, time0, bornRate, bornCount;
    //float newHue ;
    ofxPanel gui;
    ofxFloatSlider forceSlide;
    ofxFloatSlider lifeSlide ;
    ofxFloatSlider rateSlide ;
    ofxFloatSlider rotationSlide ;
    ofxFloatSlider colorSlide ;
    
    void hueChanged(float & colorSlide) ;
    void rotChanged(float & rotationSlide) ;
    void rateChanged(float & rateSlide) ;
    void lifeChanged(float & lifeSlide) ;
    void forceChanged(float & forceSlide);
		
};
