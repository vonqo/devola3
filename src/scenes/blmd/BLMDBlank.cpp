//
//  BLMDBlank.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "BLMDBlank.h"

void BLMDBlank::start(){
    ofBackground(0,0,0);
    ofEnableAntiAliasing();
    res = ResourceManager::getInstance();
}

void BLMDBlank::update(){
    
}

void BLMDBlank::draw(){
    res.carpet0.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void BLMDBlank::keyPressed(int key){
    
}

void BLMDBlank::windowResized(int w, int h){
    
}

void BLMDBlank::onAudioInput(ofSoundBuffer &input){
    
}
