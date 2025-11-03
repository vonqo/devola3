//
//  BLMDDatamosh.h
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ResourceManager.h"

class BLMDDatamosh : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> evSound;
    ofEvent<ofPixels> evCamera;
    ResourceManager res;

public:
    
    BLMDDatamosh(ofEvent<ofSoundBuffer> & soundInEv, ofEvent<ofPixels> & camereInEv) {
        evSound = soundInEv;
        evCamera = camereInEv;
        ofAddListener(soundInEv, this, &BLMDDatamosh::onAudioInput);
        ofAddListener(camereInEv, this, &BLMDDatamosh::onCameraInput);
    }
    
    ~BLMDDatamosh(){
        ofRemoveListener(evSound, this, &BLMDDatamosh::onAudioInput);
        ofRemoveListener(evCamera, this, &BLMDDatamosh::onCameraInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    void onCameraInput(ofPixels & input);
    void drawBorder();
    
    int set = 1;
    float iteration = 4.5;
    float audioEnergy = 0;
    bool isFlip = false;
    
    ofShader datamoshShader;
    ofShader goldensilkShader;
    ofFbo datamoshBuffer;
    ofFbo tintBuffer;
    ofPixels cameraData;
    ofTexture cameraTexture;
    
    ofFbo prev;
    ofFbo curr;
};
