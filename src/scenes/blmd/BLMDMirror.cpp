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
        carpetBase++;
    }
    if(ofGetKeyPressed(OF_KEY_RIGHT)){
        if(carpetBase > 1) carpetBase--;
    }
}

//--------------------------------------------------------------
void BLMDMirror::draw(){
    float cx = (audioEnergy * 25) * 1.5 + carpetBase;
    float cy = (audioEnergy * 25) + carpetBase;
    
    mirrorShader.begin();
    mirrorShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    mirrorShader.setUniform2f("scale", cx, cy);
    if(nextCarpet) {
        mirrorShader.setUniformTexture("texture1", res.carpet1.getTexture(), 1);
    } else {
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
    if(key == OF_KEY_RETURN) {
        nextCarpet = !nextCarpet;
    }
}

//--------------------------------------------------------------
void BLMDMirror::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDMirror::onAudioInput(ofSoundBuffer & input){
    audioEnergy = AudioUtility::rms(input);
}
