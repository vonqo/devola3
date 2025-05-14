//
//  AudioUtility.h
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "ofApp.h"

class AudioUtility {

public:
    static float rms(ofSoundBuffer & input);
    static float level(ofSoundBuffer & input);
    
};
