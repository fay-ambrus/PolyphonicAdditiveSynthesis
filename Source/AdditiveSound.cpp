/*
  ==============================================================================

    AdditiveVoice.cpp
    Created: 24 Nov 2025 3:54:48pm
    Author:  ambru

  ==============================================================================
*/

#include "AdditiveSound.h"

bool AdditiveSound::appliesToNote(int midiNoteNumber)
{
    return true;
}

bool AdditiveSound::appliesToChannel(int midiChannel)
{
    return true;
}