/*
  ==============================================================================

    Metronome.cpp
    Created: 13 Apr 2019 3:29:47pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{
    mFormatManager.registerBasicFormats();
    
    File myFile { File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory) };
    auto mySamples = myFile.findChildFiles(File::TypesOfFileToFind::findFiles, true, "cowbell.wav");
    
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
    
    pMetronomeSample.reset( new AudioFormatReaderSource (formatReader, true));
}

void Metronome::prepareToPlay (int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(mUpdateInterval);
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        DBG("file loaded");
    }
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    auto bufferSize = bufferToFill.numSamples;
    
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mUpdateInterval;
    
    DBG("Samples Remaining: " << mSamplesRemaining);
    DBG("Update Interval: " << mUpdateInterval);
    
    if ((mSamplesRemaining + bufferSize) >= mUpdateInterval)
    {
        DBG("CLICK");
        DBG("Total Samples: " << mTotalSamples);
    }
    
    //pMetronomeSample->getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
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
