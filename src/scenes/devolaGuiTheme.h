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
        font.size = 9;
        font.file = AssetPath + "ofxbraitsch/fonts/JetBrainsMono-Medium.ttf";
        stripe.visible = false;
        color.icons = hex(0x9C9DA1);
        color.background = hex(0x28292E);
        color.guiBackground = hex(0x1E1F24);
        color.inputAreaBackground = hex(0x42424A);
        color.slider.fill = hex(0xF4BF39);
        color.slider.text = hex(0xF4BF39);
        color.textInput.text = hex(0xF4BF39);
        color.textInput.highlight = hex(0x28292E);
        color.colorPicker.border = hex(0xEEEEEE);
        color.textInput.backgroundOnActive = hex(0x1D1E22);
        color.backgroundOnMouseOver = hex(0x42424A);
        color.backgroundOnMouseDown = hex(0x1D1E22);
        color.matrix.hover.button = hex(0x9C9DA1);
        color.graph.fills = hex(0x9C9DA1);
        init();
    }
};
