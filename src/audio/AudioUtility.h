//
//  AudioUtility.h
//  devola3
//
//  Created by Vonqo on 2025.05.06.
//
#include "ofApp.h"

class AudioUtility {

public:
    static float rms(const ofSoundBuffer& input);
    static float level(const ofSoundBuffer& input);
    static void normalizeBuffer(vector<float>& buffer);
    static void mixToMono(const ofSoundBuffer& input, vector<float>& outMono);
    static float getEnergy(int l, int h, vector<float> fftAmp, int sampleRate, bool rmsNormalization);
    static float smoothValue(float currentValue, float previousValue, float smoothing);
    static float safeClamp(float v, float minv, float maxv);
};
