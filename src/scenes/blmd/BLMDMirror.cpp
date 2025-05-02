//
//  BLMDMirror.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//

#include "BLMDMirror.h"

void BLMDMirror::start(){
    res = ResourceManager::getInstance();
    ofBackground(255, 0, 0);
}

void BLMDMirror::update(){
    
}

void BLMDMirror::draw(){
    res.carpet.draw(0, 0);
}

void BLMDMirror::windowResized(int w, int h){
    
}

void BLMDMirror::onAudioInput(ofSoundBuffer & input){
    // ofLogNotice() << "Audio MIRROR";
}
