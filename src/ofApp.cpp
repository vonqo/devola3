#include "ofApp.h"
#include "ResourceManager.h"
#include "devolaGuiTheme.h"
#include "AudioUtility.h"
#include "BLMDBlank.h"
#include "BLMDMirror.h"
#include "BLMDGlitch.h"
#include "BLMDMenger.h"
#include "BLMDDatamosh.h"
#include "BLMDOrnament.h"
#include "SpectogramScene.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("devola3 by vonqo");
    
    // --- LOAD RESOURCE AND SET CAMERA RESOLUTION -- //
    ResourceManager::getInstance().load(camWidth, camHeight);
    mainBuffer.allocate(ofGetWidth(), ofGetHeight());
    postGlitch.setup(&mainBuffer);
    
    // --- SOUND SETUP --- //
    vector<ofSoundDevice> soundDevices = ofSoundStreamListDevices();
    for(ofSoundDevice dv : soundDevices) {
        audioInputOptions.push_back(dv.name);
        if(dv.isDefaultInput) {
            soundSettings.setInDevice(dv);
        }
        if(dv.isDefaultOutput) {
            soundSettings.setOutDevice(dv);
        }
    }
    soundSettings.numInputChannels = 1;   // Mono input
    soundSettings.numOutputChannels = 0;  // No output
    soundSettings.bufferSize = 512;
    soundSettings.sampleRate = 44100;
    soundSettings.numBuffers = 4;
    soundSettings.setInListener(this);
    ofSoundStreamSetup(soundSettings);
    
    // --- MIDI SETUP --- //
    for(string midiPort : midiIn.getInPortList()) {
        midiInputOptions.push_back(midiPort);
    }
    midiIn.addListener(this);
    midiIn.setVerbose(false);
    
    // --- CAMERA SETUP --- //
    int deviceid = -1;
    vector<ofVideoDevice> devices = camGrabber.listDevices();
    
    for(ofVideoDevice dv : devices) {
        if(dv.bAvailable) {
            cameraInputOptions.push_back(dv.deviceName);
        }
    }
    
    camData.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    camTex.allocate(camWidth, camHeight, GL_RGB);
    
    // --- SCENE MANAGER SETUP --- //
    sceneManager.addScene(std::make_shared<BLMDBlank>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMirror>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDGlitch>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDMenger>(soundInEv));
    sceneManager.addScene(std::make_shared<BLMDDatamosh>(soundInEv, cameraInEv));
    sceneManager.addScene(std::make_shared<BLMDOrnament>(soundInEv, cameraInEv));
    sceneManager.addScene(std::make_shared<SpectogramScene>(soundInEv));
    
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0, 0);
    sceneManager.setTransitionMode(ofxSceneTransition::FADE);
    sceneManager.setup(ofGetWidth(), ofGetHeight());
    
    // --- GUI SETUP --- //
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->setTheme(new devolaGuiTheme());
    gui->addFRM();
    overlayToggle   = gui->addToggle("Show Overlay"); overlayToggle->setChecked(isOverlayShow);
    cameraToggle    = gui->addToggle("Show Camera");  cameraToggle->setChecked(isCameraShow);
    cameraToggle->onToggleEvent(this, &ofApp::onCameraToggle);
    overlayToggle->onToggleEvent(this, &ofApp::onOverlayToggle);
    
    gridFolder  = gui->addFolder("#==> Grid");
    gridOffset  = gridFolder->addSlider("Offset", 1, 250);     gridOffset->setValue(50);
    gridSize    = gridFolder->addSlider("Line size", 1, 20);   gridSize->setValue(1);
    gridColor   = gridFolder->addColorPicker("Line color", ofColor(244,191,57));
    
    paddingFolder = gui->addFolder("#==> Padding");
    topPadding    = paddingFolder->addTextInput("Top", "0");
    leftPadding   = paddingFolder->addTextInput("Left", "0");
    rightPadding  = paddingFolder->addTextInput("Right", "0");
    bottomPadding = paddingFolder->addTextInput("Bottom", "0");
    
    gui->addBreak();
    gui->addLabel("#==> Audio Input:");
    inputAudioList = gui->addDropdown("- audio -", audioInputOptions);
    inputAudioList->onDropdownEvent(this, &ofApp::onInputAudioSelect);
    
    gui->addBreak();
    gui->addLabel("#==> Midi Input:");
    inputMidiList = gui->addDropdown("- midi -", midiInputOptions);
    inputMidiList->onDropdownEvent(this, &ofApp::onInputMidiSelect);
    
    gui->addBreak();
    gui->addLabel("#==> Camera Input:");
    inputCameraList = gui->addDropdown("- camera -", cameraInputOptions);
    inputCameraList->onDropdownEvent(this, &ofApp::onInputCameraSelect);
    
    gui->addBreak();
    rmsSlider = gui->addSlider("rms", 0, 1); rmsSlider->setValue(0);
    ofxDatGuiLog::quiet();
    
    graphValues.assign(700, 0.0);
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
    if(isConsoleActive){
        rmsSlider->setValue(rmsValue);
        pushGraphValue(rmsValue);
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
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(isCameraShow && isConsoleActive) {
        drawCamera();
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
    
    drawOverlay();
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
    
    float dx = (float)ww/(float)graphValues.size();
    float gh = (float)hh * 0.2f;
    float topPad = hh-gh;
    
    ofBeginShape();
    ofVertex(0, hh);
    for(int p = 0; p < graphValues.size(); p++){
        float value = graphValues[p];
        ofVertex(p * dx, topPad+(gh-value*gh));
    }
    ofVertex(ww, hh);
    ofEndShape();
    
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::pushGraphValue(float value){
    graphValues.push_back(value);
    graphValues.erase(graphValues.begin());
}

//--------------------------------------------------------------
void ofApp::drawCurtain(){
    ofSetColor(0,0,0,curtainValue*255);
    ofFill();
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::drawOverlay(){
    if(!isOverlayShow) return;
    ResourceManager::getInstance().blmdLogo.draw(100, 100, 200, 100);
}

//--------------------------------------------------------------
void ofApp::drawCamera(){
    camTex.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamStop();
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // toggle console '/'
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
        if(key == '5') sceneManager.changeScene(5);
        
        if(key == '9') sceneManager.changeScene(6);
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
void ofApp::onOverlayToggle(ofxDatGuiToggleEvent ev){
    isOverlayShow = ev.checked;
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage &input) {
    
    ofLogNotice() << input.toString();
    ofLogNotice() << input.pitch << " " << input.velocity << " " << input.status;
    
    // pitch 40 - PAD 5
    // pitch 38 - PAD 6
    // pitch 46 - PAD 7
    // pitch 37 - PAD 1
    // pitch 36 - PAD 2
    // ptich 42 - PAD 3
    
    // pitch 54 - black 1
    // ptich 56 - black 2
    // pitch 58 - black 3
    // pitch 61 - black 4
    // pitch 63 - black 5
    
    // ------ PADS
    if(input.pitch == 40) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 38) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 46) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 37) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 36) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 42) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT,input.status == 144 ? 1:0);
    } else
        
    if(input.pitch == 44) {
        postGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST,input.status == 144 ? 1:0);
    } else
    if(input.pitch == 82) {
        postGlitch.setFx(OFXPOSTGLITCH_OUTLINE,input.status == 144 ? 1:0);
    } else
    
    // ------ KEYS
    {
        float vel = ofMap(input.velocity, 0, 127, 0, 1);
        
        if(input.pitch == 54) {
            postGlitch.setFx(OFXPOSTGLITCH_GLOW,input.status == 144 ? vel : 0);
        } else
        if(input.pitch == 56) {
            postGlitch.setFx(OFXPOSTGLITCH_NOISE,input.status == 144 ? vel : 0);
        } else
        if(input.pitch == 58) {
            postGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE,input.status == 144 ? vel : 0);
        } else
        if(input.pitch == 61) {
            postGlitch.setFx(OFXPOSTGLITCH_SWELL,input.status == 144 ? vel : 0);
            // postGlitch.setFx(OFXPOSTGLITCH_SHAKER,input.status == 144 ? vel : 0);
        } else
        if(input.pitch == 63) {
            postGlitch.setFx(OFXPOSTGLITCH_TWIST,input.status == 144 ? vel : 0);
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::onInputMidiSelect(ofxDatGuiDropdownEvent ev){
    string choice = midiInputOptions[ev.child];
    midiIn.closePort();
    midiIn.openPort(choice);
}

//--------------------------------------------------------------
void ofApp::onInputCameraSelect(ofxDatGuiDropdownEvent ev){
    if(camGrabber.isInitialized()) return;
    
    string choice = cameraInputOptions[ev.child];
    vector<ofVideoDevice> cameraDevices = camGrabber.listDevices();
    
    int deviceid = -1;
    for(ofVideoDevice dv : cameraDevices) {
        if(dv.bAvailable && dv.deviceName == choice) {
            deviceid = dv.id;
        }
    }
    
    if(deviceid != -1) {
        camGrabber.setDeviceID(deviceid);
        camGrabber.setDesiredFrameRate(30);
        camGrabber.setup(camWidth, camHeight);
    }
}

//--------------------------------------------------------------
void ofApp::onInputAudioSelect(ofxDatGuiDropdownEvent ev){
    string choice = audioInputOptions[ev.child];
    
    vector<ofSoundDevice> soundDevices = ofSoundStreamListDevices();
    for(ofSoundDevice dv : soundDevices) {
        if(dv.name == choice) {
            soundSettings.setInDevice(dv);
            ofSoundStreamSetup(soundSettings);
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    mainBuffer.allocate(w, h);
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
