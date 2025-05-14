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
    // ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    res = ResourceManager::getInstance();
    glitchShader = res.blmdGlitch;
}

//--------------------------------------------------------------
void BLMDGlitch::update(){
    
}

//--------------------------------------------------------------
void BLMDGlitch::draw(){
    glitchShader.begin();
    glitchShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    glitchShader.setUniform1f("uTime", ofGetElapsedTimeMillis() * 0.001);
    glitchShader.setUniform1f("glitcher", audioEnergy);
    glitchShader.setUniform1i("samplerNum", 5);
    glitchShader.setUniformTexture("texture1", res.carpet3.getTexture(), 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    glitchShader.end();
    // res.carpet2.draw(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void BLMDGlitch::keyPressed(int key){
    if(key == OF_KEY_LEFT) {
        
    } else if(key == OF_KEY_RIGHT) {
        
    }
}

//--------------------------------------------------------------
void BLMDGlitch::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDGlitch::onAudioInput(ofSoundBuffer & input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}

