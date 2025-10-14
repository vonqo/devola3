//
//  resourceManager.h
//  devola3
//
//  Created by Vonqo on 2025.05.02.
//

#ifndef RESOURCE_MAN_H
#define RESOURCE_MAN_H

#include "ofMain.h"

class ResourceManager {

public:
    int camWidth;
    int camHeight;
    
    ofImage blmdLogo;
    ofImage carpet0;
    ofImage carpet1;
    ofImage carpet2;
    ofImage carpet3;
    ofImage carpet4;
    ofImage carpet8;
    ofImage carpetMenger;
    ofImage carpetTear;
    ofImage textureNoise1;
    ofImage textureTest1;
    ofImage textureUVMap;
    ofImage textureCellular;
    ofImage borderBlue;
    
    ofShader blmdMirror;
    ofShader blmdGlitch;
    ofShader blmdMenger;
    ofShader blmdDatamosh;
    ofShader blmdGoldenSilk;
    ofShader intensityScope;
    
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }
    
    void load(int cw, int ch) {
        camWidth = cw;
        camHeight = ch;
        
        blmdLogo.load("images/blmd_logo.png");
        carpet0.load("images/carpet0.jpg");
        carpet1.load("images/carpet1.jpg");
        carpet2.load("images/carpet2.png");
        carpet3.load("images/carpet3.jpg");
        carpet4.load("images/carpet4.png");
        carpet8.load("images/carpet8.png");
        carpetMenger.load("images/menger.png");
        carpetTear.load("images/tear_rug_white.png");
        
        borderBlue.load("images/blue_border.png");
        
        textureNoise1.load("images/texture_noise1.png");
        textureTest1.load("images/texture_test1.png");
        textureUVMap.load("images/texture_uv_map.jpg");
        textureCellular.load("images/cellular_texture.png");
        
        blmdMirror.load("shaders/blmd_mirror/mirror.vert", "shaders/blmd_mirror/mirror.frag");
        blmdGlitch.load("shaders/blmd_glitch/glitch.vert", "shaders/blmd_glitch/glitch.frag");
        blmdMenger.load("shaders/blmd_menger/menger.vert", "shaders/blmd_menger/menger.frag");
        blmdDatamosh.load("shaders/blmd_datamosh/datamosh.vert", "shaders/blmd_datamosh/datamosh.frag");
        intensityScope.load("shaders/vid_int_scp/intensity_scope.vert", "shaders/vid_int_scp/intensity_scope.frag");
        blmdGoldenSilk.load("shaders/blmd_goldensilk/silk.vert", "shaders/blmd_goldensilk/silk.frag");
    }
};

#endif
