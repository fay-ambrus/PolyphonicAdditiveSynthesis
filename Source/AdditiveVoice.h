/*
  ==============================================================================

    AdditiveVoice.h
    Created: 22 Nov 2025 3:28:39pm
    Author:  ambru

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AdditiveSound.h"

class AdditiveVoice : public juce::SynthesiserVoice {
private:
    int midiNoteNumber = -1;
    juce::SynthesiserSound *sound = nullptr;
	static constexpr int numOfOvertones = 16;
	static constexpr int envelopeLength = 20;
	static constexpr float envelopeRate = 100.0;
	float currentTime = 0.0f;
    std::array<std::array<float, envelopeLength>, 20> harmonicsAmplitudesEnvelope = {{
        {1.00f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.01f, 0.49f, 0.25f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.02f, 0.50f, 0.26f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.016f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.01f, 0.49f, 0.25f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.00f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.99f, 0.48f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.98f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.97f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.98f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.99f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.00f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.01f, 0.49f, 0.25f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.02f, 0.50f, 0.26f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.016f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.01f, 0.49f, 0.25f, 0.14f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.00f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.99f, 0.48f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.98f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.97f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {0.98f, 0.47f, 0.24f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f},
        {1.00f, 0.48f, 0.25f, 0.13f, 0.09f, 0.06f, 0.04f, 0.03f, 0.02f, 0.015f, 0.012f, 0.010f, 0.008f, 0.007f, 0.006f, 0.005f}
    }};
	std::array<float, numOfOvertones> harmonicsFrequencies{0.0f};
	std::array<float, numOfOvertones> harmonicsAngles{0.0f};
	std::array<float, numOfOvertones> harmonicsAnglesDeltas{0.0f};
    float sampleRate = 0.0f;

public:
    bool canPlaySound(juce::SynthesiserSound* synthesiserSound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
};