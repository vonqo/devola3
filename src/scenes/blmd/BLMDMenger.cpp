//
//  BLMDMenger.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "BLMDMenger.h"
#include "AudioUtility.h"

//--------------------------------------------------------------
void BLMDMenger::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofBackground(0,0,0);
    
    bufferSize = 1024;
    sampleRate = 44100;
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HANN);
    fftAmp.resize(fft->getBinSize());
    audioBuffer.assign(fft->getBinSize(), 0);
    
    res = ResourceManager::getInstance();
    mengerShader = res.blmdMenger;
}

//--------------------------------------------------------------
void BLMDMenger::update(){
    int fftSize = fft->getBinSize();
    
    float energy = AudioUtility::getEnergy(100, 255, fftAmp, sampleRate, 0.8f);
    iteration = ofMap(energy, 100, 255, 0, 1);
    
    if(ofGetKeyPressed(OF_KEY_LEFT)){
        if(iteration < 0) iteration -= 0.1f;
    }
    if(ofGetKeyPressed(OF_KEY_RIGHT)){
        if(iteration > 1) iteration += 0.1f;
    }
}

//--------------------------------------------------------------
void BLMDMenger::draw(){
    mengerShader.begin();
    mengerShader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    mengerShader.setUniform1f("uTime", ofGetElapsedTimeMillis() * 0.001);
    
    if(set == 1) {
        mengerShader.setUniformTexture("texture1", res.carpet3.getTexture(), 1);
        mengerShader.setUniformTexture("texture2", res.carpet2.getTexture(), 2);
    } else if(set == 2) {
        mengerShader.setUniformTexture("texture1", res.carpetMenger.getTexture(), 1);
        mengerShader.setUniformTexture("texture2", res.carpet2.getTexture(), 2);
    }
    
    mengerShader.setUniform1f("speed", ofMap(audioEnergy,0,1, 0.15, 0.25));
    mengerShader.setUniform1f("iteration", ofMap(iteration,0,1, 4.5, 5.5));
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    mengerShader.end();
}

//--------------------------------------------------------------
void BLMDMenger::keyPressed(int key){
    if(key == 'a' || key == 'A') set = 1;
    if(key == 's' || key == 'S') set = 2;
    
}

//--------------------------------------------------------------
void BLMDMenger::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDMenger::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    AudioUtility::mixToMono(input, audioBuffer);
    
    fft->setSignal(audioBuffer.data());
    float* bins = fft->getAmplitude();
    memcpy(&fftAmp[0], bins, sizeof(float) * fft->getBinSize());
}
