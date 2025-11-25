/*
  ==============================================================================

    AdditiveVoice.cpp
    Created: 22 Nov 2025 4:15:48pm
    Author:  ambru

  ==============================================================================
*/

#include "AdditiveVoice.h"

bool AdditiveVoice::canPlaySound(juce::SynthesiserSound* synthesiserSound) {
    return dynamic_cast<AdditiveSound*> (synthesiserSound) != nullptr;
}

void AdditiveVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    this->midiNoteNumber = midiNoteNumber;
    this->sound = sound;
    this->currentTime = 0.0f;

    sampleRate = static_cast<float>(getSampleRate());
    DBG("Sample rate: " << sampleRate);

	float baseFrequency = 440.0f * std::pow(2.0f, (midiNoteNumber - 69) / 12.0f);

    for (int i = 0; i < numOfOvertones; i++) {
        // set initial angle
		harmonicsAngles[i] = 0.0f;

        // set angle deltas
		harmonicsAnglesDeltas[i] = juce::MathConstants<float>::twoPi * baseFrequency * (i + 1) / sampleRate;
    }

    DBG("Note On: " << midiNoteNumber <<  " sample rate: " << sampleRate);
}

void AdditiveVoice::stopNote(float velocity, bool allowTailOff) {
    clearCurrentNote();
	midiNoteNumber = -1;
    DBG("Note Off");
}

void AdditiveVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    if (midiNoteNumber < 0)
        return;

    auto* leftBuffer = outputBuffer.getWritePointer(0, startSample);
    auto* rightBuffer = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;

    for (int sample = 0; sample < numSamples; ++sample)
    {
		// calculate curent smple value
        auto currentSample = 0.0f;

        for (int i = 0; i < numOfOvertones; ++i) {
			// calculate the correct amplitude value from the envelope
            int envelopeIdxBefore = static_cast<int>(std::floor(currentTime * envelopeRate));
			int envelopeIdxAfter = envelopeIdxBefore + 1;
            float envelopeFraction = (currentTime * envelopeRate) - envelopeIdxBefore;

            if (envelopeIdxBefore >= harmonicsAmplitudesEnvelope.size()) {
                envelopeIdxBefore = envelopeIdxBefore % harmonicsAmplitudesEnvelope.size();
            }

            if (envelopeIdxBefore == harmonicsAmplitudesEnvelope.size() - 1)
            {
                envelopeIdxAfter = 0;
			}

            if (envelopeIdxBefore >= 20 && envelopeIdxAfter >= 20) {
				DBG("Envelope index out of bounds: " << envelopeIdxBefore << ", " << envelopeIdxAfter);
            }

            float harmonicAmplitude = (1.0f - envelopeFraction) * harmonicsAmplitudesEnvelope[envelopeIdxBefore][i] + envelopeFraction * harmonicsAmplitudesEnvelope[envelopeIdxAfter][i];

            currentSample += std::sin(harmonicsAngles[i]) * harmonicAmplitude;
		}

        leftBuffer[sample] += currentSample;

        if (rightBuffer != nullptr)
            rightBuffer[sample] += currentSample;

		// update angles
        for (int i = 0; i < numOfOvertones; ++i) {
            harmonicsAngles[i] += harmonicsAnglesDeltas[i];

            if (harmonicsAngles[i] > juce::MathConstants<float>::twoPi)
                harmonicsAngles[i] -= juce::MathConstants<float>::twoPi;
		}

        // update delta time
		currentTime += 1.0f / sampleRate;
        if (currentTime >= envelopeLength * (1.0f / envelopeRate)) {
			currentTime -= (envelopeLength * (1.0f / envelopeRate));
        }
    }
}

void AdditiveVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    // TODO: Handle MIDI controller changes
}

void AdditiveVoice::pitchWheelMoved(int newPitchWheelValue) {
    // TODO: Handle MIDI pitch wheel changes
}