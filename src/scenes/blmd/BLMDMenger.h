//
//  BLMDMenger.h
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ResourceManager.h"

class BLMDMenger : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;

public:
    
    BLMDMenger(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &BLMDMenger::onAudioInput);
    }
    
    ~BLMDMenger(){
        ofRemoveListener(ev, this, &BLMDMenger::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    
    int set = 0;
    float audioEnergy = 0;
    ofShader mengerShader;
};
