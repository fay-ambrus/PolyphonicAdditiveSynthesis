/*
  ==============================================================================

    AdditiveVoice.cpp
    Created: 22 Nov 2025 4:15:48pm
    Author:  ambru

  ==============================================================================
*/

#include "AdditiveVoice.h"

bool AdditiveVoice::canPlaySound(juce::SynthesiserSound* synthetiserSound) {
    return true;
}

void AdditiveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
    this->midiNoteNumber = midiNoteNumber;
    noteVelocity = velocity;
    this->sound = sound;

    float frequency = 440.0f * (2.0f ^ (midiNoteNumber - 69) / 12.0f);

    // Compute phase increment per sample
    auto sampleRate = getSampleRate();
    angleDelta = juce::MathConstants<float>::twoPi * cyclesPerSecond / sampleRate;

    currentAngle = 0.0f;
}

void AdditiveVoice::stopNote(float velocity, bool allowTailOff) {
    midiNoteNumber = -1;
    noteVelocity = 0.0f;
}

void AdditiveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    if (currentNote < 0)
        return;

    auto* leftBuffer = outputBuffer.getWritePointer(0, startSample);
    //auto* rightBuffer = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        auto currentSample = std::sin(currentAngle) * level;

        leftBuffer[sample] += currentSample;

        /*if (rightBuffer != nullptr)
            rightBuffer[sample] += currentSample;*/

        currentAngle += angleDelta;

        // wrap phase to [0, 2π] to avoid floating-point drift
        if (currentAngle > juce::MathConstants<float>::twoPi)
            currentAngle -= juce::MathConstants<float>::twoPi;
    }
}