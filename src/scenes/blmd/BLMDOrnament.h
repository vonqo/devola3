//
//  BLMDOrnament.h
//  devola3
//
//  Created by Vonqo on 2025.05.09.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ofxMidi.h"
#include "ofxOrnament.h"
#include "ResourceManager.h"

class BLMDOrnament : public ofxScene, public ofxMidiListener{
    
private:
    ofEvent<ofSoundBuffer> evSound;
    ofEvent<ofPixels> evCamera;
    ResourceManager res;

public:
    
    BLMDOrnament(ofEvent<ofSoundBuffer> & soundInEv, ofEvent<ofPixels> & camereInEv) {
        evSound = soundInEv;
        evCamera = camereInEv;
        ofAddListener(soundInEv, this, &BLMDOrnament::onAudioInput);
        ofAddListener(camereInEv, this, &BLMDOrnament::onCameraInput);
    }
    
    ~BLMDOrnament(){
        ofRemoveListener(evSound, this, &BLMDOrnament::onAudioInput);
        ofRemoveListener(evCamera, this, &BLMDOrnament::onCameraInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    void onCameraInput(ofPixels & input);
    void newMidiMessage(ofxMidiMessage & input) override;

    ofShader videoIntensity;
    ofTexture cameraTexture;
    Ornament ornament;
    
    float audioEnergy = 0;
};
