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
    ofEnableAntiAliasing();
    res = ResourceManager::getInstance();
    videoIntensity = res.intensityScope;
    cameraTexture.allocate(ofGetWidth(),ofGetHeight(),GL_RGB);
    ornament.setup(ofGetWidth(),ofGetHeight());
    ornament.loadTexture(res.carpet2.getTexture());
    ornament.setTileSize(150);
    ornament.setWallpaperGroup(12);
    ornament.setAngle(30);
}

//--------------------------------------------------------------
void BLMDOrnament::update(){
    
}

//--------------------------------------------------------------
void BLMDOrnament::draw(){
    ofBackground(0,0,0);
    videoIntensity.begin();
    videoIntensity.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    videoIntensity.setUniformTexture("texture1", cameraTexture, 1);
    videoIntensity.setUniform1f("noiser", audioEnergy);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    videoIntensity.end();
    
//    ornament.draw(0,0);
//    ornament.drawDebug(0, 300,400,300);
}

//--------------------------------------------------------------/
void BLMDOrnament::keyPressed(int key){
//    if (key == 'm'){
//        ornament.setCellStructure(ornament.getCellStructure()+1);
//    }
//    if (key == 'n'){
//        ornament.setCellStructure(ornament.getCellStructure()-1);
//    }
//    if (key == 'c'){
//        ornament.setWallpaperGroup(ornament.getWallpaperGroupAsInt()+1);
//    }
//    if (key == 'v'){
//        ornament.setWallpaperGroup(ornament.getWallpaperGroupAsInt()-1);
//    }
}

//--------------------------------------------------------------
void BLMDOrnament::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void BLMDOrnament::onCameraInput(ofPixels &input) {
    if(!isDrawing()) return;
    cameraTexture.loadData(input);
    // ornament.update();
}

//--------------------------------------------------------------
void BLMDOrnament::onAudioInput(ofSoundBuffer &input){
    if(!isDrawing()) return;
    audioEnergy = AudioUtility::rms(input);
}

//--------------------------------------------------------------
void BLMDOrnament::newMidiMessage(ofxMidiMessage &input) {
    
}
