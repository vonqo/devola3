//
//  SpectogramScene.h
//  devola3
//
//  Created by Vonqo on 2025.05.14.
//
#include "ofMain.h"
#include "ofxScene.h"
#include "ResourceManager.h"
#include "ofxFft.h"

class SpectogramScene : public ofxScene {
    
private:
    ofEvent<ofSoundBuffer> ev;
    ResourceManager res;

public:
    
    SpectogramScene(ofEvent<ofSoundBuffer> & soundInEv) {
        ev = soundInEv;
        ofAddListener(soundInEv, this, &SpectogramScene::onAudioInput);
    }
    
    ~SpectogramScene(){
        ofRemoveListener(ev, this, &SpectogramScene::onAudioInput);
    }
    
    void start() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
    void onAudioInput(ofSoundBuffer & input);
    
    int sampleRate;
    int bufferSize;
    int plotHeight;
    int spectrogramOffset;
    
    ofxFft* fft;
    ofMutex soundMutex;
    vector<float> drawBuffer, middleBuffer, audioBuffer;
    vector<vector<float>> spectogramData;
    ofImage spectrogram;
    
    void pushSpectogram(vector<float> buffer);
};
