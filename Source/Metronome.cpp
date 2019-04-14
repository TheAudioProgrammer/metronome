/*
  ==============================================================================

    Metronome.cpp
    Created: 13 Apr 2019 3:29:47pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "Metronome.h"

void Metronome::prepareToPlay (double sampleRate)
{
    mSampleRate = sampleRate;
}

void Metronome::countSamples (int bufferSize)
{
    mTotalSamples+=bufferSize;
    DBG(mTotalSamples);
}

void Metronome::reset()
{
    mTotalSamples = 0;
}
