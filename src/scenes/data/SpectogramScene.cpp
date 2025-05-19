//
//  SpectogramScene.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.14.
//
#include "SpectogramScene.h"

//--------------------------------------------------------------
void SpectogramScene::start(){
    ofClear(0,0,0);
    ofEnableAntiAliasing();
    res = ResourceManager::getInstance();
    
    bufferSize = 1024;
    sampleRate = 44100;
    spectrogramOffset = 0;
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    audioBuffer.resize(fft->getBinSize());
    middleBuffer.resize(fft->getBinSize());
    drawBuffer.resize(fft->getBinSize());
    
    spectogramData.resize(600);
    spectrogram.allocate(600, fft->getBinSize(), OF_IMAGE_COLOR);
    spectrogram.setColor(ofColor::black);
}

//--------------------------------------------------------------
void SpectogramScene::update(){
    pushSpectogram(middleBuffer);
}

//--------------------------------------------------------------
void SpectogramScene::draw(){
    for(int i = 0; i < spectogramData.size(); i++) {
        for(int e = 0; e < spectogramData[i].size(); e++) {
            float val = spectogramData[i][e] * 10;
            spectrogram.setColor(i,e,ofColor(0,255*val,0));
        }
    }
    spectrogram.update();
    spectrogram.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void SpectogramScene::pushSpectogram(vector<float> buffer){
    spectogramData.push_back(buffer);
    spectogramData.erase(spectogramData.begin());
}

//--------------------------------------------------------------
void SpectogramScene::keyPressed(int key){
    
}

//--------------------------------------------------------------
void SpectogramScene::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void SpectogramScene::onAudioInput(ofSoundBuffer & input){
    if(!isDrawing()) return;
    
    fft->setSignal(input.getBuffer());
    float* curFft = fft->getAmplitude();
    memcpy(&audioBuffer[0], curFft, sizeof(float) * fft->getBinSize());
    
    soundMutex.lock();
    middleBuffer = audioBuffer;
    soundMutex.unlock();
}
