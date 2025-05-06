//
//  AudioUtility.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "AudioUtility.h"

float AudioUtility::rms(ofSoundBuffer & input){
    float rms = input.getRMSAmplitude();
    return ofMap(rms, 0, 1.5, 0, 1);
}

float AudioUtility::fft(ofSoundBuffer & input){
    //TODO implement
    return 0;
}
