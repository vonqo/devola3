//
//  BLMDGlitch.h
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ofxFft.h"
#include "ResourceManager.h"

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
    
    int set = 1;
    float audioEnergy = 0;
    ofShader glitchShader;
    
    ofxFft* fft;
    int bufferSize;
    int sampleRate;
    vector<float> audioBuffer;
    vector<float> fftAmp;
    
};
