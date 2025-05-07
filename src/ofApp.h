#pragma once

#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofxDatGui.h"
#include "ofxPostGlitch.h"
#include "ofxMidi.h"
#include "ofxFft.h"
#include "ResourceManager.h"

class ofApp : public ofBaseApp, public ofxMidiListener{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    void audioIn(ofSoundBuffer & input) override;
    void newMidiMessage(ofxMidiMessage & input) override;
    
    float padTop = 0;
    float padBottom = 0;
    float padLeft = 0;
    float padRight = 0;
    
    ofFbo mainBuffer;
    ofxPostGlitch postGlitch;
    ofxSceneManager sceneManager;
    ofEvent<ofSoundBuffer> soundInEv;
    ofEvent<ofPixels> cameraInEv;
    
    int camWidth;
    int camHeight;
    ofVideoGrabber camGrabber;
    ofPixels camData;
    ofTexture camTex;
    
    ofxDatGui* gui;
    ofxDatGuiToggle* cameraToggle;
    ofxDatGuiToggle* audioToggle;
    void onCameraToggle(ofxDatGuiToggleEvent ev);
    void onAudioToggle(ofxDatGuiToggleEvent ev);
    
    ofxDatGuiSlider* gridOffset;
    ofxDatGuiSlider* gridSize;
    ofxDatGuiColorPicker* gridColor;
    ofxDatGuiTextInput* topPadding;
    ofxDatGuiTextInput* leftPadding;
    ofxDatGuiTextInput* rightPadding;
    ofxDatGuiTextInput* bottomPadding;
    ofxDatGuiSlider* rms;
    float rmsValue = 0;
    
    float curtainValue = 0;
    bool isConsoleActive = true;
    bool isCameraShow = false;
    bool isAudioShow = false;
    
    ofxFft* fft;
    ofFbo audioSpectogram;
    
    void toggleConsole(bool isConsoleActive);
    void drawGrid();
    void drawCurtain();
    void drawCamera();
    void drawAudioAnalysis();
};
