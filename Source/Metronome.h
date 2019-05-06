/*
  ==============================================================================

    Metronome.h
    Created: 13 Apr 2019 3:29:47pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Metronome : public HighResolutionTimer
{
public:
    Metronome();
    
    // public methods
    void prepareToPlay (int samplesPerBlock, double sampleRate);
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    void reset();
    
    //High Resolution Timer
    void hiResTimerCallback() override;
  
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    double mBpm { 60.0 };
    int mUpdateInterval { 0 };
    int mSamplesRemaining { 0 };
    
    AudioFormatManager mFormatManager;
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample { nullptr };
};

