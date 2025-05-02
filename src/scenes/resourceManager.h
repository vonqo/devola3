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
    ofImage carpet;
    ofShader mirrorShader;
    
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }
    
    void load() {
        carpet.load("images/test.jpg");
        // Load images and shaders here
    }
};

#endif
