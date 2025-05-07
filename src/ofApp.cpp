#include "ofApp.h"
#include "ResourceManager.h"
#include "devolaGuiTheme.h"
#include "AudioUtility.h"
#include "BLMDBlank.h"
#include "BLMDMirror.h"
#include "BLMDGlitch.h"
#include "BLMDMenger.h"
#include "BLMDDatamosh.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("devola3 by vonqo");
    
    // --- LOAD RESOURCE AND SET CAMERA RESOLUTION -- //
    int camW = 1280;
    int camH = 720;
    
    ResourceManager::getInstance().load(camW, camH);
    mainBuffer.allocate(ofGetWidth(), ofGetHeight());
    audioSpectogram.allocate(ofGetWidth(), ofGetHeight());
    postGlitch.setup(&mainBuffer);
    
    // --- SOUND SETUP --- //
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
    fft = ofxFft::create(512, OF_FFT_WINDOW_HAMMING);
    
    // --- CAMERA SETUP --- //
    ResourceManager res = ResourceManager::getInstance();
    camWidth = res.camWidth;
    camHeight = res.camHeight;
    
    int deviceid = -1;
    vector<ofVideoDevice> devices = camGrabber.listDevices();
    
    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
            deviceid = devices[i].id;
            break;
        } else {
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    if(deviceid != -1) {
        camGrabber.setDeviceID(deviceid);
        camGrabber.setDesiredFrameRate(30);
        camGrabber.setup(camWidth, camHeight);
        camData.allocate(camWidth, camHeight, OF_PIXELS_RGB);
        camTex.allocate(camWidth, camHeight, GL_RGB);
    }
    
    // --- SCENE MANAGER SETUP --- //
    sceneManager.addScene(std::make_shared<BLMDBlank>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMirror>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDGlitch>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMenger>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDDatamosh>(soundInEv, cameraInEv));
    
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0, 0);
    sceneManager.setTransitionMode(ofxSceneTransition::FADE);
    sceneManager.setup(ofGetWidth(), ofGetHeight());
    
    // --- GUI SETUP --- //
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->setTheme(new devolaGuiTheme());
    gui->addFRM();
    cameraToggle    = gui->addToggle("Show Camera"); cameraToggle->setChecked(isCameraShow);
    audioToggle     = gui->addToggle("Show Audio");  audioToggle->setChecked(isAudioShow);
    cameraToggle->onToggleEvent(this, &ofApp::onCameraToggle);
    audioToggle->onToggleEvent(this, &ofApp::onAudioToggle);
    
    gui->addBreak();
    gui->addLabel("--> Grid");
    gridOffset  = gui->addSlider("Offset", 1, 250);     gridOffset->setValue(50);
    gridSize    = gui->addSlider("Line size", 1, 20);   gridSize->setValue(1);
    gridColor   = gui->addColorPicker("Line color", ofColor(244,191,57));
    
    gui->addBreak();
    gui->addLabel("--> Padding");
    topPadding    = gui->addTextInput("Top");    topPadding->setText("0");
    leftPadding   = gui->addTextInput("Left");   leftPadding->setText("0");
    rightPadding  = gui->addTextInput("Right");  rightPadding->setText("0");
    bottomPadding = gui->addTextInput("Bottom"); bottomPadding->setText("0");
    
    gui->addBreak();
    gui->addLabel("--> Audio");
    
    rms = gui->addSlider("RMS", 0, 1); rms->setValue(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    sceneManager.update();
    camGrabber.update();
    
    if(ofGetKeyPressed('q')){
        if(curtainValue > 0) curtainValue -= 0.01;
    }
    if(ofGetKeyPressed('w')){
        if(curtainValue < 1) curtainValue += 0.01;
    }
    
    if(camGrabber.isFrameNew()){
        ofPixels & pixels = camGrabber.getPixels();
        ofNotifyEvent(cameraInEv, pixels);
        if(isCameraShow && isConsoleActive) {
            camTex.loadData(pixels);
        }
    }
    if(isConsoleActive) {
        rms->setValue(rmsValue);
    }
    
    try {
        padTop      = std::stof(topPadding->getText());
        padBottom   = std::stof(bottomPadding->getText());
        padLeft     = std::stof(leftPadding->getText());
        padRight    = std::stof(rightPadding->getText());
    } catch(const std::exception& e) {
        ofLogVerbose() << "Parse Error";
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    ofNotifyEvent(soundInEv, input);
    if(isConsoleActive) {
        rmsValue = AudioUtility::rms(input);
        if(isAudioShow) {
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(isCameraShow && isConsoleActive) {
        drawCamera();
    } else if(isAudioShow && isConsoleActive) {
        drawAudioAnalysis();
    } else {
        mainBuffer.begin();
        sceneManager.draw();
        mainBuffer.end();
        
        postGlitch.generateFx();
        mainBuffer.draw(
            padLeft,
            padTop,
            ofGetWidth()-padLeft-padRight,
            ofGetHeight()-padTop-padBottom
        );
    }
    
    drawCurtain();
    drawGrid();
}

//--------------------------------------------------------------
void ofApp::drawGrid(){
    if(!isConsoleActive) return;
    
    int ww = ofGetWidth();
    int hh = ofGetHeight();
    float offset = gridOffset->getValue();
    float lineWidth = gridSize->getValue();
    
    ofSetColor(gridColor->getColor());
    ofFill();
    
    for(int x = 0; x <= ww; x+=offset) {
        ofDrawRectangle(x,0,lineWidth,hh);
    }
    
    for(int y = 0; y <= hh; y+=offset) {
        ofDrawRectangle(0,y,ww,lineWidth);
    }
    
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::drawCurtain(){
    ofSetColor(0,0,0,curtainValue*255);
    ofFill();
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::drawCamera(){
    camTex.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawAudioAnalysis(){
    audioSpectogram.begin();
    ofBackground(0,0,0);
    
    audioSpectogram.end();
    audioSpectogram.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamStop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // toggle console
    if(key == 47) {
        isConsoleActive = !isConsoleActive;
        toggleConsole(isConsoleActive);
    }
    
    if(topPadding->getFocused() || bottomPadding->getFocused() || leftPadding->getFocused() || rightPadding->getFocused()) {
        
    } else {
        if(key == '1') sceneManager.changeScene(1);
        if(key == '2') sceneManager.changeScene(2);
        if(key == '3') sceneManager.changeScene(3);
        if(key == '4') sceneManager.changeScene(4);
        if(key == '0') sceneManager.changeScene(0);
    }
}

//--------------------------------------------------------------
void ofApp::toggleConsole(bool isConsoleActive) {
    if(isConsoleActive) {
        ofShowCursor();
        gui->setVisible(true);
    } else {
        ofHideCursor();
        gui->setVisible(false);
    }
}

//--------------------------------------------------------------
void ofApp::onCameraToggle(ofxDatGuiToggleEvent ev){
    isCameraShow = ev.checked;
}

//--------------------------------------------------------------
void ofApp::onAudioToggle(ofxDatGuiToggleEvent ev){
    isAudioShow = ev.checked;
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage &input) {
    // TODO: midi implementation
    
    postGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
    postGlitch.setFx(OFXPOSTGLITCH_NOISE,       false);
    postGlitch.setFx(OFXPOSTGLITCH_SWELL,       false);
    postGlitch.setFx(OFXPOSTGLITCH_SHAKER,      false);
    postGlitch.setFx(OFXPOSTGLITCH_TWIST,       false);
    postGlitch.setFx(OFXPOSTGLITCH_GLOW,        false);
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
    mainBuffer.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
