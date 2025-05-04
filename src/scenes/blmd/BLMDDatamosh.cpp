//
//  BLMDDatamosh.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "BLMDDatamosh.h"

void BLMDDatamosh::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    
    res = ResourceManager::getInstance();
    ofBackground(0,10,255);
    datamoshShader = res.blmdDatamosh;
}

void BLMDDatamosh::update(){
    
}

void BLMDDatamosh::draw(){
    datamoshShader.begin();
    datamoshShader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    datamoshShader.setUniform1f("uTime", ofTime().getAsMilliseconds() * 0.001);
    datamoshShader.setUniformTexture("textureCur", res.carpet2.getTexture(), 1);
    datamoshShader.setUniformTexture("texturePre", res.carpet3.getTexture(), 2);
    datamoshShader.setUniform1f("minVel", 0.01);
    datamoshShader.setUniform1f("maxVel", 0.5);
    datamoshShader.setUniform1f("offsetInc", 0.1);
    datamoshShader.setUniform2f("offset", 1.0, 1.0);
    datamoshShader.setUniform1f("lambda", 1.0);
    datamoshShader.setUniform2f("scale", 1.5, 1.5);
    datamoshShader.setUniform1f("intensity", 6.0);
    datamoshShader.setUniform1f("threshold", 0.5);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    datamoshShader.end();
}

void BLMDDatamosh::keyPressed(int key){
    
}

void BLMDDatamosh::windowResized(int w, int h){
    
}

void BLMDDatamosh::onAudioInput(ofSoundBuffer &input){
    
}
