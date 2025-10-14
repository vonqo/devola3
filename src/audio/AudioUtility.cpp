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
float AudioUtility::getEnergy(int lowFreq, int highFreq, vector<float> fftAmp, int sampleRate, bool rmsNormalization) {
    
    int binSize = fftAmp.size();
    float freqPerBin = (sampleRate / 2.0f) / binSize;  // Nyquist mapping
    
    // Clamp bounds
    lowFreq  = ofClamp(lowFreq, 0, sampleRate / 2.0f);
    highFreq = ofClamp(highFreq, 0, sampleRate / 2.0f);
    
    // Convert frequency range to bin range
    int lowIndex  = floor(lowFreq / freqPerBin);
    int highIndex = ceil(highFreq / freqPerBin);
    lowIndex = ofClamp(lowIndex, 0, binSize - 1);
    highIndex = ofClamp(highIndex, 0, binSize - 1);
    
    float sum = 0.0f;
    int count = 0;
    
    for (int i = lowIndex; i <= highIndex; i++) {
        sum += fftAmp[i] * fftAmp[i];
        count++;
    }
    
    float avgPower = (count > 0) ? sum / count : 0.0f;
    
    float dB;
    if(rmsNormalization) {
        float rms = sqrt(avgPower);  // RMS normalization
        rms *= 0.7071f; // Hanning reduces RMS by ~sqrt(0.5) for some implementations; applying this will lower energy.
        rms = ofClamp(rms, 1e-6f, 1.0f); // avoid log(0) and clamp
        dB = 20.0f * log10f(rms);
    } else {
        dB = 10.0f * log10f(avgPower + 1e-6f);
    }
    
    float energy = ofMap(dB, -90.0f, 0.0f, 0.0f, 255.0f, true);
    return energy;
}

// Smoothing max 1.0
float AudioUtility::smoothValue(float currentValue, float previousValue, float smoothing = 0.9){
    return previousValue * smoothing + currentValue * (1.0f - smoothing);
}

float AudioUtility::safeClamp(float v, float minv = 1e-12f, float maxv = 1.0f) {
    return ofClamp(v, minv, maxv);
}
