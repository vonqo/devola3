//
//  home.h
//  devola3
//
//  Created by Vonqo on 2024.11.01.
//

#ifndef home_h
#define home_h

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSceneManager.h"

class home : public ofBaseApp{

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
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    private:
        void changeScene();
        
        ofxSceneManager sceneManager;
        ofImage carpet;
        
        ofxPanel gui;
        ofxButton button;
        
        ofxIntField screenWidthField;
        ofxIntField screenHeightField;
        ofShader shader;
        
};


#endif /* home_h */
