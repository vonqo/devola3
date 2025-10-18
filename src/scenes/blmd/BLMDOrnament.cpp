//
//  BLMDOrnament.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.09.
//
#include "BLMDOrnament.h"
#include "AudioUtility.h"

//--------------------------------------------------------------
void BLMDOrnament::start(){
    ofBackground(0,0,0);
    ofDisableAntiAliasing();
    ornament.setup(ofGetWidth(),ofGetHeight());
    res = ResourceManager::getInstance();
    videoIntensity = res.intensityScope;
    buffer.allocate(res.camWidth, res.camHeight);
    cameraTexture.allocate(res.camWidth,res.camHeight,GL_RGB);
    
    //assign video input to ornament
    ornament.loadTexture(cameraTexture);
}

//--------------------------------------------------------------
void BLMDOrnament::update(){
    buffer.begin();
    videoIntensity.begin();
    videoIntensity.setUniform2f("resolution", res.camWidth, res.camHeight);
    videoIntensity.setUniformTexture("texture1", cameraTexture, 1);
    videoIntensity.setUniform1f("noiser", audioEnergy);
    ofDrawRectangle(0, 0, res.camWidth, res.camHeight);
    videoIntensity.end();
    buffer.end();
}

//--------------------------------------------------------------
void BLMDOrnament::draw(){
    buffer.draw(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------/
void BLMDOrnament::keyPressed(int key){
    
}

//--------------------------------------------------------------
void BLMDOrnament::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDOrnament::onCameraInput(ofPixels &input) {
    if(!isDrawing()) return;
    cameraTexture.loadData(input);
}

//--------------------------------------------------------------
void BLMDOrnament::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}

//--------------------------------------------------------------
void BLMDOrnament::newMidiMessage(ofxMidiMessage &input) {
    
}
