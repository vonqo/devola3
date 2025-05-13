#pragma once

#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofxDatGui.h"
#include "ofxPostGlitch.h"
#include "ofxMidi.h"
#include "ofxFft.h"
#include "ofxBlur.h"
#include "ResourceManager.h"
#include "ofxOrnament.h"

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
    
    const int camW = 1280;
    const int camH = 720;
    
    float padTop = 0;
    float padBottom = 0;
    float padLeft = 0;
    float padRight = 0;
    
    ofFbo mainBuffer;
    ofxPostGlitch postGlitch;
    ofxSceneManager sceneManager;
    ofEvent<ofSoundBuffer> soundInEv;
    ofEvent<ofPixels> cameraInEv;
    ofSoundStreamSettings soundSettings;
    ofxMidiIn midiIn;
    
    int camWidth;
    int camHeight;
    ofVideoGrabber camGrabber;
    ofPixels camData;
    ofTexture camTex;
    
    ofxDatGui* gui;
    ofxDatGuiToggle* cameraToggle;
    ofxDatGuiToggle* overlayToggle;
    void onCameraToggle(ofxDatGuiToggleEvent ev);
    void onOverlayToggle(ofxDatGuiToggleEvent ev);
    
    ofxDatGuiFolder* gridFolder;
    ofxDatGuiSlider* gridOffset;
    ofxDatGuiSlider* gridSize;
    ofxDatGuiColorPicker* gridColor;
    
    ofxDatGuiFolder* paddingFolder;
    ofxDatGuiTextInput* topPadding;
    ofxDatGuiTextInput* leftPadding;
    ofxDatGuiTextInput* rightPadding;
    ofxDatGuiTextInput* bottomPadding;
    ofxDatGuiSlider* rmsSlider;
    
    vector<string> audioInputOptions;
    vector<string> midiInputOptions;
    vector<string> cameraInputOptions;
    ofxDatGuiDropdown* inputMidiList;
    ofxDatGuiDropdown* inputCameraList;
    ofxDatGuiDropdown* inputAudioList;
    void onInputMidiSelect(ofxDatGuiDropdownEvent ev);
    void onInputCameraSelect(ofxDatGuiDropdownEvent ev);
    void onInputAudioSelect(ofxDatGuiDropdownEvent ev);
    
    float rmsValue = 0;
    vector<float> graphValues;
    void pushGraphValue(float value);
    
    float curtainValue = 0;
    bool isConsoleActive = true;
    bool isCameraShow = false;
    bool isOverlayShow = false;
    
    void toggleConsole(bool isConsoleActive);
    void drawGrid();
    void drawOverlay();
    void drawCurtain();
    void drawCamera();
    void drawAudioAnalysis();
};
