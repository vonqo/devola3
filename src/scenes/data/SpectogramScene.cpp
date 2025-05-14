//
//  SpectogramScene.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.14.
//
#include "SpectogramScene.h"

//--------------------------------------------------------------
void SpectogramScene::start(){
    ofBackground(0,0,0);
    ofEnableAntiAliasing();
    res = ResourceManager::getInstance();
}

//--------------------------------------------------------------
void SpectogramScene::update(){
    
}

//--------------------------------------------------------------
void SpectogramScene::draw(){
    ofBackground(0);
}

//--------------------------------------------------------------
void SpectogramScene::keyPressed(int key){
    
}

//--------------------------------------------------------------
void SpectogramScene::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void SpectogramScene::onAudioInput(ofSoundBuffer & buffer){
    if(!isDrawing()) return;
    ofLogNotice() << "Spectogram";
}

