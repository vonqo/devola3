//
//  BLMDDatamosh.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.04.
//
#include "BLMDDatamosh.h"
#include "AudioUtility.h"

//--------------------------------------------------------------
void BLMDDatamosh::start(){
    ofDisableArbTex();
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    res = ResourceManager::getInstance();
    datamoshBuffer.allocate(ofGetWidth(), ofGetHeight());
    cameraTexture.allocate(res.camWidth, res.camHeight, GL_RGB);
    prev.allocate(ofGetWidth(), ofGetHeight());
    curr.allocate(ofGetWidth(), ofGetHeight());
    
    datamoshShader = res.blmdDatamosh;
}

//--------------------------------------------------------------
void BLMDDatamosh::update(){
    curr.begin();
    cameraTexture.draw(0,0,curr.getWidth(),curr.getHeight());
    curr.end();
    
    prev.begin();
    datamoshBuffer.draw(0,ofGetHeight(),ofGetWidth(),-ofGetHeight());
    prev.end();
}

//--------------------------------------------------------------
void BLMDDatamosh::draw(){
    datamoshBuffer.begin();
    datamoshShader.begin();
    datamoshShader.setUniform1f("time", ofGetElapsedTimeMillis() * 0.001);
    datamoshShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    datamoshShader.setUniformTexture("textureCur", curr.getTexture(), 1);
    datamoshShader.setUniformTexture("texturePre", prev.getTexture(), 2);
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
    datamoshBuffer.end();
    
    datamoshBuffer.draw(0,0);
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    res.carpetTear.draw(0,0,ofGetWidth(),ofGetHeight());
    ofDisableBlendMode();
}

//--------------------------------------------------------------
void BLMDDatamosh::keyPressed(int key){
    
}

//--------------------------------------------------------------
void BLMDDatamosh::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDDatamosh::onCameraInput(ofPixels &input) {
    if(!isDrawing()) return;
    cameraTexture.loadData(input);
}

//--------------------------------------------------------------
void BLMDDatamosh::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}
