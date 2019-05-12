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
    
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    
    pMetronomeSample->setNextReadPosition(0);
}

void Metronome::prepareToPlay (int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        DBG("file loaded");
    }
    
    pMetronomeSample->setNextReadPosition(0);
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const auto bufferSize = bufferToFill.numSamples;
    
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mUpdateInterval;
    
    if ((mSamplesRemaining + bufferSize) >= mUpdateInterval)
    {
        const auto timeToStartPlaying = mUpdateInterval - mSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);
        
        for (auto sample = 0; sample < bufferSize; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                pMetronomeSample->getNextAudioBlock (bufferToFill);
            }
        }
    }
    
    if (pMetronomeSample->getNextReadPosition() != 0)
    {
        pMetronomeSample->getNextAudioBlock (bufferToFill);
    }
}

void Metronome::reset()
{
    mTotalSamples = 0;
    pMetronomeSample->setNextReadPosition(0);
}
