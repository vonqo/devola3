#include "blmdMirror.h"

//--------------------------------------------------------------
void blmdMirror::setup() {
    ofBackground(255,0,0);
}

//--------------------------------------------------------------
void blmdMirror::update(){
    // carpet.update();
}

//--------------------------------------------------------------
void blmdMirror::draw() {
    // ofBackground(255,0,0);
    // carpet.draw(0,0,ofGetWidth(),ofGetHeight());
    
    shader.begin();
    shader.setUniform2f("vTexCoord", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("uScale", 1.0, 1.0);
    shader.setUniformTexture("uTexture", carpet.getTexture(), 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
}

//--------------------------------------------------------------
void blmdMirror::keyPressed(int key){

}

//--------------------------------------------------------------
void blmdMirror::keyReleased(int key){

}

//--------------------------------------------------------------
void blmdMirror::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void blmdMirror::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void blmdMirror::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void blmdMirror::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void blmdMirror::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void blmdMirror::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void blmdMirror::windowResized(int w, int h){

}

//--------------------------------------------------------------
void blmdMirror::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void blmdMirror::dragEvent(ofDragInfo dragInfo){

}
