//
//  BLMDGlitch.h
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "resourceManager.h"

class BLMDGlitch : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;
    
public:
    
    BLMDGlitch(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &BLMDGlitch::onAudioInput);
    }
    
    ~BLMDGlitch(){
        ofRemoveListener(ev, this, &BLMDGlitch::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    
    ofShader glitchShader;
    
};
