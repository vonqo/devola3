//
//  AudioUtility.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "AudioUtility.h"

float AudioUtility::rms(ofSoundBuffer & input){
    float rms = input.getRMSAmplitude();
    return ofMap(rms, 0, 0.5f, 0, 1);
}
