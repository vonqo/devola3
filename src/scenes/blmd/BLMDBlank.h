//
//  BLMDBlank.h
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ResourceManager.h"

class BLMDBlank : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;

public:
    
    BLMDBlank(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &BLMDBlank::onAudioInput);
    }
    
    ~BLMDBlank(){
        ofRemoveListener(ev, this, &BLMDBlank::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
};
