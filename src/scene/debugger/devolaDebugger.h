//
//  debugger.h
//  devola3
//
//  Created by Vonqo on 2024.11.01.
//

#ifndef devolaDebugger_h
#define devolaDebugger_h


#pragma once

#include "ofxScene.h"

class devolaDebugger : public ofxScene {

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
        
};



#endif /* devolaDebugger_h */
