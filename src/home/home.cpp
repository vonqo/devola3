#include "home.h"
#include "ofxScene.h"
#include "scene/mirror/blmdMirror.h"
#include "scene/debugger/devolaDebugger.h"

//--------------------------------------------------------------
void home::setup(){
    ofBackground(25,25,25);
    
    // GUI
    gui.setup("test panel");
    
    gui.add(screenWidthField.setup("screen width",0));
    gui.add(screenHeightField.setup("screen height",0));
    
    button.addListener(this, &home::changeScene);
    gui.add(button.setup("button"));
    
    carpet.load("images/carpet.jpg");
    shader.load("shaders/mirror.vert", "shaders/mirror.frag");
    
    // SCENE MANAGER
    shared_ptr<devolaDebugger> debugger = make_shared<devolaDebugger>();
    shared_ptr<blmdMirror> mirror = make_shared<blmdMirror>(carpet, shader);
    
    sceneManager.addScene(debugger);
    sceneManager.addScene(mirror);
    
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0.2, 0.2);
    sceneManager.setTransitionMode(ofxSceneTransition::FADE);
    sceneManager.setup(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void home::update(){
    sceneManager.update();
}

//--------------------------------------------------------------
void home::draw() {
    // sceneManager.draw();
    // carpet.draw(0,0,ofGetWidth(),ofGetHeight());
    // gui.draw();
    
    carpet.bind();
    shader.begin();
    
    // shader.setUniform2f("vTexCoord", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("uScale", 1.0, 1.0);
    shader.setUniformTexture("uTexture", carpet.getTexture(), 1);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
    carpet.unbind();
}

//--------------------------------------------------------------
void home::keyPressed(int key){

}

//--------------------------------------------------------------
void home::keyReleased(int key){
    
}

//--------------------------------------------------------------
void home::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void home::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void home::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void home::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void home::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void home::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void home::windowResized(int w, int h){

}

//--------------------------------------------------------------
void home::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void home::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void home::changeScene() {
    ofLog(OF_LOG_NOTICE, "button clicked");
    sceneManager.changeScene(1);
}
