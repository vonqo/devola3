//
//  BLMDDatamosh.h
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "resourceManager.h"

class BLMDDatamosh : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;

public:
    
    BLMDDatamosh(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &BLMDDatamosh::onAudioInput);
    }
    
    ~BLMDDatamosh(){
        ofRemoveListener(ev, this, &BLMDDatamosh::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    
    ofShader datamoshShader;
};
