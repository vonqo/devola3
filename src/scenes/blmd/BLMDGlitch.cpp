//
//  BLMDGlitch.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//

#include "BLMDGlitch.h"
#include "AudioUtility.h"

//--------------------------------------------------------------
void BLMDGlitch::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofBackground(0,0,0);
    
    res = ResourceManager::getInstance();
    glitchShader = res.blmdGlitch;
    
    bufferSize = 1024;
    sampleRate = 44100;
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HANN);
    fftAmp.resize(fft->getBinSize());
    audioBuffer.assign(fft->getBinSize(), 0);
}

//--------------------------------------------------------------
void BLMDGlitch::update(){
    float energy = AudioUtility::getEnergy(100, 255, fftAmp, sampleRate, 0.8f);
    audioEnergy = energy;
}

//--------------------------------------------------------------
void BLMDGlitch::draw(){
    glitchShader.begin();
    glitchShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    glitchShader.setUniform1f("uTime", ofGetElapsedTimeMillis() * 0.001);
    glitchShader.setUniform1f("glitcher", ofMap(audioEnergy,0,1,0.0,2.5));
    glitchShader.setUniform1i("samplerNum", 8);
    if(set == 1) {
        glitchShader.setUniformTexture("texture1", res.carpet3.getTexture(), 1);
    } else if(set == 2) {
        glitchShader.setUniformTexture("texture1", res.carpet1.getTexture(), 1);
    } else if(set == 3) {
        glitchShader.setUniformTexture("texture1", res.carpet8.getTexture(), 1);
    }
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    glitchShader.end();
}

//--------------------------------------------------------------
void BLMDGlitch::keyPressed(int key){
    if(key == OF_KEY_LEFT) {
        
    } else if(key == OF_KEY_RIGHT) {
        
    }
    if(key == 'a' || key == 'A') set = 1;
    if(key == 's' || key == 'S') set = 2;
    if(key == 'd' || key == 'D') set = 3;
}

//--------------------------------------------------------------
void BLMDGlitch::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDGlitch::onAudioInput(ofSoundBuffer & input){
    if(!isDrawing()) return;
    AudioUtility::mixToMono(input, audioBuffer);
    
    fft->setSignal(audioBuffer.data());
    float* bins = fft->getAmplitude();
    memcpy(&fftAmp[0], bins, sizeof(float) * fft->getBinSize());
}

