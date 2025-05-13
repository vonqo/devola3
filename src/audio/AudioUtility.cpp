//
//  AudioUtility.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "AudioUtility.h"

float AudioUtility::rms(ofSoundBuffer & input){
    float rms = input.getRMSAmplitude();
    
//    int bufferSize = input.getBuffer().size();
//    float rms = 0.0;
//    int numCounted = 0;
//
//    for (int i = 0; i < bufferSize; i++){
//        float leftSample = input[i * 2] * 0.5;
//        float rightSample = input[i * 2 + 1] * 0.5;
//        
//        rms += leftSample * leftSample;
//        rms += rightSample * rightSample;
//        numCounted += 2;
//    }
//
//    rms /= (float)numCounted;
//    rms = sqrt(rms);
    
    return ofMap(rms, 0, 1, 0, 1);
}
