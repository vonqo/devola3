#include "ofApp.h"
#include "resourceManager.h"
#include "BLMDMirror.h"
#include "BLMDGlitch.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("devola3 by vonqo");
    ResourceManager::getInstance().load();
    
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
    soundSettings.bufferSize = 512;
    soundSettings.sampleRate = 44100;
    soundSettings.numBuffers = 4;
    soundSettings.setInListener(this);
    ofSoundStreamSetup(soundSettings);
    
    sceneManager.addScene(std::make_shared<BLMDMirror>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDGlitch>(soundInEv));
    
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0, 0);
    sceneManager.setTransitionMode(ofxSceneTransition::FADE);
    sceneManager.setup(ofGetWidth(), ofGetHeight());
    
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->addTextInput("message", "# open frameworks #");
    gui->addFRM();
    gui->addBreak();
    gui->addSlider("position X", 0, 120, 75);
    gui->addSlider("position Y", -40, 240, 200);
    gui->addSlider("position Z", -80, 120, -40);
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
    if(key == 'a') sceneManager.changeScene(0);
    if(key == 'b') sceneManager.changeScene(1);
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
