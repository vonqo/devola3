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
    
    res = ResourceManager::getInstance();
    mirrorShader = res.blmdMirror;
}

//--------------------------------------------------------------
void BLMDMirror::update(){
    if(ofGetKeyPressed(OF_KEY_LEFT)){
        carpetBase += 0.5f;
    }
    if(ofGetKeyPressed(OF_KEY_RIGHT)){
        if(carpetBase > 1) carpetBase -= 0.5f;
    }
}

//--------------------------------------------------------------
void BLMDMirror::draw(){
    float cx = (audioEnergy * 25) * 2.5 + carpetBase;
    float cy = (audioEnergy * 25) + carpetBase;
    
    mirrorShader.begin();
    mirrorShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    mirrorShader.setUniform2f("scale", cx, cy);
    
    if(set == 1) {
        mirrorShader.setUniformTexture("texture1", res.carpet1.getTexture(), 1);
    } else if(set == 2) {
        mirrorShader.setUniformTexture("texture1", res.carpet2.getTexture(), 1);
    } else if(set == 3) {
        mirrorShader.setUniformTexture("texture1", res.carpet2.getTexture(), 1);
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
    audioEnergy = AudioUtility::rms(input);
}
