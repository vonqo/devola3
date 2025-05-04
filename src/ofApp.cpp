#include "ofApp.h"
#include "resourceManager.h"
#include "BLMDBlank.h"
#include "BLMDMirror.h"
#include "BLMDGlitch.h"
#include "BLMDMenger.h"
#include "BLMDDatamosh.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("devola3 by vonqo");
    ResourceManager::getInstance().load();
    ofHideCursor(); // ofShowCursor();
    
    ofSoundStreamSettings soundSettings;
    vector<ofSoundDevice> soundDevices = ofSoundStreamListDevices();
    for(ofSoundDevice dv : soundDevices) {
        if(dv.isDefaultInput) {
            soundSettings.setInDevice(dv);
        }
        if(dv.isDefaultOutput) {
            soundSettings.setOutDevice(dv);
        }
    }
    soundSettings.numInputChannels = 1;  // Mono input
    soundSettings.numOutputChannels = 0; // No output
    soundSettings.bufferSize = 256;
    soundSettings.sampleRate = 44100;
    soundSettings.numBuffers = 4;
    soundSettings.setInListener(this);
    ofSoundStreamSetup(soundSettings);
    
    sceneManager.addScene(std::make_shared<BLMDBlank>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMirror>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDGlitch>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMenger>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDDatamosh>(soundInEv));
    
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0, 0);
    sceneManager.setTransitionMode(ofxSceneTransition::FADE);
    sceneManager.setup(ofGetWidth(), ofGetHeight());
    
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->addTextInput("message", "# open frameworks #");
    gui->addFRM();
    gui->addBreak();
}

//--------------------------------------------------------------
void ofApp::update(){
    sceneManager.update();
    int sceneIndex = sceneManager.getCurrentSceneIndex();
    sceneManager.scenes[sceneIndex];
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    ofNotifyEvent(soundInEv, input);
}

//--------------------------------------------------------------
void ofApp::draw(){
    sceneManager.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamStop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') sceneManager.changeScene(1);
    if(key == '2') sceneManager.changeScene(2);
    if(key == '3') sceneManager.changeScene(3);
    if(key == '4') sceneManager.changeScene(4);
    if(key == '0') sceneManager.changeScene(0);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
