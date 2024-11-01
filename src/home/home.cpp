#include "home.h"

//--------------------------------------------------------------
void home::setup(){
    gui.setup("test panel");
    
    gui.add(screenWidthField.setup("screen width",0));
    gui.add(screenHeightField.setup("screen height",0));
    
    gui.add(button.setup("button"));
}

//--------------------------------------------------------------
void home::update(){
    
}

//--------------------------------------------------------------
void home::draw(){
    gui.draw();
    if(button) {
        
    }
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
