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
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(mUpdateInterval);
}

void Metronome::countSamples (int bufferSize)
{
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mUpdateInterval;
    
    DBG("Samples Remaining: " << mSamplesRemaining);
    DBG("Update Interval: " << mUpdateInterval);
    
    if ((mSamplesRemaining + bufferSize) >= mUpdateInterval)
    {
        DBG("CLICK");
        DBG("Total Samples: " << mTotalSamples);
    }
}

void Metronome::reset()
{
    HighResolutionTimer::stopTimer();
    mTotalSamples = 0;
}

void Metronome::hiResTimerCallback()
{
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
}
