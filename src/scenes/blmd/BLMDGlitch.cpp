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
    float energy = AudioUtility::getEnergy(200, 320, fftAmp, sampleRate, 0.8f);
    
    if(glitcher <= 5.0) {
        audioEnergy = ofMap(energy, 180, 255, 0.0, 1.0, true);
    } else if(glitcher > 5.0 && glitcher < 10.0) {
        audioEnergy = ofMap(energy, 180, 255, 5.0, glitcher, true);
    } else {
        audioEnergy = ofMap(energy, 180, 255, glitcher * 0.7, glitcher * 1.4, true);
    }
    
    if(ofGetKeyPressed(OF_KEY_RIGHT)){
        glitcher += 0.1f;
    }
    if(ofGetKeyPressed(OF_KEY_LEFT)){
        if(glitcher > 0.1) glitcher -= 0.1f;
    }
}

//--------------------------------------------------------------
void BLMDGlitch::draw(){
    glitchShader.begin();
    glitchShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    glitchShader.setUniform1f("uTime", ofGetElapsedTimeMillis() * 0.001);
    glitchShader.setUniform1f("glitcher", glitcher + audioEnergy);
    glitchShader.setUniform1f("uvOffset", uvOffset);
    glitchShader.setUniform1i("samplerNum", 8);
    if(set == 1) {
        glitchShader.setUniformTexture("texture1", res.carpet3.getTexture(), 1);
    } else if(set == 2) {
        glitchShader.setUniformTexture("texture1", res.carpet1.getTexture(), 1);
    } else if(set == 3) {
        // glitchShader.setUniformTexture("texture1", res.carpet8.getTexture(), 1);
    }
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    glitchShader.end();
}

//--------------------------------------------------------------
void BLMDGlitch::keyPressed(int key){
    if(key == OF_KEY_UP) {
        // glitcher += 1.0;
    } else if(key == OF_KEY_DOWN) {
        glitcher = 0.0;
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

