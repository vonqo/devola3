//
//  BLMDGlitch.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//

#include "BLMDGlitch.h"

void BLMDGlitch::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    
    res = ResourceManager::getInstance();
    ofBackground(255, 255, 0);
    glitchShader = res.blmdGlitch;
}

void BLMDGlitch::update(){
    
}

void BLMDGlitch::draw(){
    glitchShader.begin();
    glitchShader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
    glitchShader.setUniform1f("uTime", ofTime().getAsMilliseconds() * 0.001);
    glitchShader.setUniform1f("glitcher", 0.1f);
    glitchShader.setUniform1i("samplerNum", 10);
    glitchShader.setUniformTexture("texture1", res.carpet2.getTexture(), 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    glitchShader.end();
    // res.carpet2.draw(0,0,ofGetWidth(),ofGetHeight());
}

void BLMDGlitch::keyPressed(int key){
    if(key == OF_KEY_LEFT) {
        
    } else if(key == OF_KEY_RIGHT) {
        
    }
}

void BLMDGlitch::windowResized(int w, int h){
    
}

void BLMDGlitch::onAudioInput(ofSoundBuffer & input){
    
}

