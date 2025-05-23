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
    
    res = ResourceManager::getInstance();
    mengerShader = res.blmdMenger;
}

//--------------------------------------------------------------
void BLMDMenger::update(){
    
}

//--------------------------------------------------------------
void BLMDMenger::draw(){
    mengerShader.begin();
    mengerShader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    mengerShader.setUniform1f("uTime", ofGetElapsedTimeMillis() * 0.001);
    
    mengerShader.setUniformTexture("texture1", res.carpet3.getTexture(), 1);
    mengerShader.setUniformTexture("texture2", res.carpet2.getTexture(), 2);
    
    mengerShader.setUniform1f("speed", ofMap(audioEnergy,0,1, 0.05, 0.5));
    mengerShader.setUniform1f("iteration", ofMap(audioEnergy,0,1, 4, 8));
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    mengerShader.end();
}

//--------------------------------------------------------------
void BLMDMenger::keyPressed(int key){
    if(key == 'a' || key == 'A') set = 1;
    if(key == 's' || key == 'S') set = 2;
    if(key == 'd' || key == 'D') set = 3;
}

//--------------------------------------------------------------
void BLMDMenger::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDMenger::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}
