/*
  ==============================================================================

    Metronome.h
    Created: 13 Apr 2019 3:29:47pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Metronome
{
public:
    void prepareToPlay (double sampleRate);
    void countSamples (int bufferSize);
    void reset();
  
  
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
};

