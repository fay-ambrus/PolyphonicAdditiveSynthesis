/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolyphonicAdditiveSynthesisAudioProcessorEditor::PolyphonicAdditiveSynthesisAudioProcessorEditor (PolyphonicAdditiveSynthesisAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
  addAndMakeVisible(keyboardComponent);
  keyboardState.addListener(&p);
  setSize (400, 300);
}

PolyphonicAdditiveSynthesisAudioProcessorEditor::~PolyphonicAdditiveSynthesisAudioProcessorEditor()
{
}

//==============================================================================
void PolyphonicAdditiveSynthesisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("PolyphonicAdditiveSynthesis!", getLocalBounds(), juce::Justification::centred, 1);
}

void PolyphonicAdditiveSynthesisAudioProcessorEditor::resized()
{
    keyboardComponent.setBounds (10, 200, getWidth() - 20, 80);
}
