/*
  ==============================================================================

    AdditiveVoice.h
    Created: 22 Nov 2025 3:28:39pm
    Author:  ambru

  ==============================================================================
*/

#pragma once

class AdditiveVoice : public SynthetiserVoice {
private:
    int midiNoteNumber = -1;
    float noteVelocity = 0.0f;
    SynthesiserSound *sound = nullptr;
    float frequency = 0.0f;

public:
    bool canPlaySound(SynthesiserSound* synthetiserSound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void renderNextBlock override (AudioBuffer<float>& outputBuffer, int startSample, int numSamples);
}