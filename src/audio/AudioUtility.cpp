//
//  AudioUtility.cpp
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "AudioUtility.h"

float AudioUtility::rms(const ofSoundBuffer & input){
    float rms = input.getRMSAmplitude();
    return ofMap(rms, 0.15, 1.0, 0, 1);
}

// @deprecated
void AudioUtility::normalizeBuffer(vector<float>& buffer) {
    float maxAmp = 0.0f;
    for (float s : buffer) {
        maxAmp = std::max(maxAmp, fabs(s));
    }
    if (maxAmp > 0.0f) {
        for (auto& s : buffer) {
            s /= maxAmp;
        }
    }
}

void AudioUtility::mixToMono(const ofSoundBuffer& input, vector<float>& outMono) {
    int frames = input.getNumFrames();
    int channels = input.getNumChannels();
    outMono.resize(frames);

    for (int i = 0; i < frames; i++) {
        float sample = 0.0f;
        for (int ch = 0; ch < channels; ch++) {
            sample += input[i * channels + ch];
        }
        outMono[i] = sample / (float)channels;
    }
}

/**
 bass:      20 - 140
 lowMid:    140 - 400
 mid:       400 - 2600
 highMid:   2600 - 5200
 treble:    5200 - 14000
 */

#define MAX_DECIBELS -30.0
#define MIN_DECIBELS -100.0

float AudioUtility::getEnergy(int lowFreq, int highFreq, vector<float>& fftAmp, int sampleRate, float smoothing = 0.8f) {
    
    int binSize = fftAmp.size();
    float nyquist = sampleRate / 2.0f;
    float binWidth = nyquist / binSize;
    
    vector<float> db(binSize);
    vector<unsigned char> byteVals(binSize);
    
    float range = MAX_DECIBELS - MIN_DECIBELS;
    
    for (int i = 0; i < binSize; i++) {
        float amp = fftAmp[i];
        if (amp < 1e-12f) amp = 1e-12f; // avoid log(0)
        db[i] = 20.0f * log10(amp);
        
        if (db[i] < MIN_DECIBELS) db[i] = MIN_DECIBELS;
        if (db[i] > MAX_DECIBELS) db[i] = MAX_DECIBELS;
        
        float norm = (db[i] - MIN_DECIBELS) / range;
        byteVals[i] = static_cast<unsigned char>(ofClamp(norm * 255.0f, 0, 255));
    }
    
    int lowIndex = round(lowFreq / nyquist * binSize);
    int highIndex = round(highFreq / nyquist * binSize);
    
    float sum = 0.0f;
    int count = 0;
    
    for (int i = lowIndex; i <= highIndex; i++) {
        sum += byteVals[i];
        count++;
    }
    
    float avgPower = (count > 0) ? sum / count : 0.0f;
    static float smoothedEnergy = 0;
    smoothedEnergy = ofLerp(smoothedEnergy, avgPower, 1.0f - smoothing);
    return smoothedEnergy;
}

// Smoothing max 1.0
float AudioUtility::smoothValue(float currentValue, float previousValue, float smoothing = 0.9){
    return previousValue * smoothing + currentValue * (1.0f - smoothing);
}
