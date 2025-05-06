//
//  BLMDMirror.h
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ResourceManager.h"

class BLMDMirror : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;
    
public:
    
    BLMDMirror(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &BLMDMirror::onAudioInput);
    }
    
    ~BLMDMirror(){
        ofRemoveListener(ev, this, &BLMDMirror::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
//    void keyReleased(int key) override;
//    void mouseMoved(int x, int y) override;
//    void mouseDragged(int x, int y, int button) override;
//    void mousePressed(int x, int y, int button) override;
//    void mouseReleased(int x, int y, int button) override;
//    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
//    void mouseEntered(int x, int y) override;
//    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
//    void dragEvent(ofDragInfo dragInfo) override;
//    void gotMessage(ofMessage msg) override;
    void onAudioInput(ofSoundBuffer & input);
    
    bool nextCarpet = false;
    float audioEnergy = 0;
    float carpetBase = 1;
    ofShader mirrorShader;
    
};
