//
//  devolaGuiTheme.h
//  devola3
//
//  Created by Vonqo on 2025.05.05.
//
#include "ofMain.h"
#include "ofxDatGui.h"

class devolaGuiTheme : public ofxDatGuiTheme{
public:
    devolaGuiTheme()
    {
        font.size = 8;
        font.file = AssetPath + "ofxbraitsch/fonts/JetBrainsMono-Medium.ttf";
        stripe.visible = false;
        init();
    }
};
