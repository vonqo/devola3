//
//  BLMDMenger.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "BLMDMenger.h"

void BLMDMenger::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    
    res = ResourceManager::getInstance();
    ofBackground(255,100,100);
    mengerShader = res.blmdMenger;
}

void BLMDMenger::update(){
    
}

void BLMDMenger::draw(){
    mengerShader.begin();
    mengerShader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    mengerShader.setUniform1f("uTime", ofTime().getAsMilliseconds() * 0.001);
    mengerShader.setUniformTexture("texture1", res.carpet2.getTexture(), 1);
    mengerShader.setUniformTexture("texture2", res.carpet3.getTexture(), 2);
    mengerShader.setUniform1f("speed", 1);
    mengerShader.setUniform1f("iteration", 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    mengerShader.end();
}

void BLMDMenger::keyPressed(int key){
    
}

void BLMDMenger::windowResized(int w, int h){
    
}

void BLMDMenger::onAudioInput(ofSoundBuffer &input){
    
}
