/*
  ==============================================================================

    AdditiveVoice.h
    Created: 22 Nov 2025 3:28:39pm
    Author:  ambru

  ==============================================================================
*/

#pragma once

class AdditiveVoice : public juce::SynthetiserVoice {
private:
    int midiNoteNumber = -1;
    float noteVelocity = 0.0f;
    juce::SynthesiserSound *sound = nullptr;
    float frequency = 0.0f;

public:
    bool canPlaySound(juce::SynthesiserSound* synthetiserSound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
};