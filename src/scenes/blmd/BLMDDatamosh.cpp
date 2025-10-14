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
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    res = ResourceManager::getInstance();
    datamoshBuffer.allocate(ofGetWidth(), ofGetHeight());
    tintBuffer.allocate(ofGetWidth(), ofGetHeight());
    cameraTexture.allocate(res.camWidth, res.camHeight, GL_RGB);
    prev.allocate(ofGetWidth(), ofGetHeight());
    curr.allocate(ofGetWidth(), ofGetHeight());
    
    datamoshShader = res.blmdDatamosh;
    goldensilkShader = res.blmdGoldenSilk;
}

//--------------------------------------------------------------
void BLMDDatamosh::update(){
    curr.begin();
    cameraTexture.draw(0,0,curr.getWidth(),curr.getHeight());
    curr.end();
    
    prev.begin();
    datamoshBuffer.draw(0,ofGetHeight(),ofGetWidth(),-ofGetHeight());
    prev.end();
    
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
    datamoshShader.setUniform1f("lambda", 1.2);
    datamoshShader.setUniform2f("scale", 1.5, 1.5);
    datamoshShader.setUniform1f("intensity", 7.5);
    datamoshShader.setUniform1f("threshold", 0.25);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    datamoshShader.end();
    datamoshBuffer.end();
}

//--------------------------------------------------------------
void BLMDDatamosh::draw(){
    tintBuffer.begin();
    ofSetColor(255,25,50,255);
    // ofSetColor(255,215,0,255);
    datamoshBuffer.draw(0,0);
    tintBuffer.end();
    
    goldensilkShader.begin();
    goldensilkShader.setUniform1f("time", ofGetElapsedTimeMillis() * 0.001);
    goldensilkShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    goldensilkShader.setUniformTexture("texture1", tintBuffer.getTexture(), 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    goldensilkShader.end();
    
    drawBorder();
}

//--------------------------------------------------------------
void BLMDDatamosh::drawBorder(){
    // res.borderBlue.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void BLMDDatamosh::keyPressed(int key){
    if(key == OF_KEY_UP) {
        isFlip = true;
    }
    if(key == OF_KEY_DOWN) {
        isFlip = false;
    }
}

//--------------------------------------------------------------
void BLMDDatamosh::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDDatamosh::onCameraInput(ofPixels &input) {
    if(!isDrawing()) return;
    input.mirror(isFlip, false);
    cameraTexture.loadData(input);
}

//--------------------------------------------------------------
void BLMDDatamosh::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}
