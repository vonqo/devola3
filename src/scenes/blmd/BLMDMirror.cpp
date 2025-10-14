//
//  BLMDMirror.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//

#include "BLMDMirror.h"
#include "AudioUtility.h"

//--------------------------------------------------------------
void BLMDMirror::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    bufferSize = 1024;
    sampleRate = 44100;
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    fftAmp.resize(fft->getBinSize());
    audioBuffer.assign(bufferSize, 0.0f);
    
    res = ResourceManager::getInstance();
    mirrorShader = res.blmdMirror;
}

//--------------------------------------------------------------
void BLMDMirror::update(){
    float energy = AudioUtility::getEnergy(100, 255, fftAmp, sampleRate, false);
    
    audioEnergySmoothed = AudioUtility::smoothValue(energy, audioEnergySmoothed, 0.8f);
    ofLog() << audioEnergySmoothed;
    
    audioEnergy = ofMap(audioEnergySmoothed, 100, 255, 0, 25, true);
    // ofLog() << audioEnergy;
    
    if(ofGetKeyPressed(OF_KEY_RIGHT)){
        carpetBase += 0.5f;
    }
    if(ofGetKeyPressed(OF_KEY_LEFT)){
        if(carpetBase > 1) carpetBase -= 0.5f;
    }
}

//--------------------------------------------------------------
void BLMDMirror::draw(){
    float cx = audioEnergy * 1.5 + carpetBase;
    float cy = audioEnergy + carpetBase;
    
    mirrorShader.begin();
    mirrorShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    mirrorShader.setUniform2f("scale", cx, cy);
    
    if(set == 1) {
        mirrorShader.setUniformTexture("texture1", res.carpet1.getTexture(), 1);
    } else if(set == 2) {
        mirrorShader.setUniformTexture("texture1", res.carpet2.getTexture(), 1);
    } else if(set == 3) {
        mirrorShader.setUniformTexture("texture1", res.carpet4.getTexture(), 1);
    }
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    mirrorShader.end();
}

//--------------------------------------------------------------
void BLMDMirror::keyPressed(int key){
    if(key == OF_KEY_UP) {
        carpetBase += 100;
    }
    if(key == OF_KEY_DOWN) {
        carpetBase = 0;
    }
    
    if(key == 'a' || key == 'A') set = 1;
    if(key == 's' || key == 'S') set = 2;
    if(key == 'd' || key == 'D') set = 3;
    
}

//--------------------------------------------------------------
void BLMDMirror::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDMirror::onAudioInput(ofSoundBuffer & input){
    if(!isDrawing()) return;
    
    AudioUtility::mixToMono(input, audioBuffer);
    AudioUtility::normalizeBuffer(audioBuffer);
    
    fft->setSignal(audioBuffer.data());
    float* bins = fft->getAmplitude();
    memcpy(&fftAmp[0], bins, sizeof(float) * fft->getBinSize());
}
