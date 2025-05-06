#pragma once

#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofxDatGui.h"
#include "ResourceManager.h"

class ofApp : public ofBaseApp{
    
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
    
    float padTop = 0;
    float padBottom = 0;
    float padLeft = 0;
    float padRight = 0;
    
    ofFbo mainBuffer;
    ofxSceneManager sceneManager;
    ofEvent<ofSoundBuffer> soundInEv;
    ofEvent<ofPixels> cameraInEv;
    
    int camWidth;
    int camHeight;
    ofVideoGrabber camGrabber;
    ofPixels camData;
    
    ofxDatGui* gui;
    ofxDatGuiSlider* gridOffset;
    ofxDatGuiSlider* gridSize;
    ofxDatGuiColorPicker* gridColor;
    ofxDatGuiTextInput* topPadding;
    ofxDatGuiTextInput* leftPadding;
    ofxDatGuiTextInput* rightPadding;
    ofxDatGuiTextInput* bottomPadding;
    ofxDatGuiValuePlotter* rms;
    float rmsValue = 0;
    
    bool isConsoleActive = true;
//    float gridSize = 1;
//    int gridOffset = 25;
    
    void toggleConsole(bool isConsoleActive);
    void drawGrid();
};
