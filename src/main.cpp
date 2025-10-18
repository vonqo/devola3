#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
    settings.setGLVersion(3, 3);
    
    settings.setSize(1280, 720);
    settings.windowMode = OF_WINDOW;
    settings.title="devola3 by vonqo";
    
//	settings.setSize(1920, 1080);
//    settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN / OF_WINDOW
    
	auto window = ofCreateWindow(settings);
    
	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();
    
}
