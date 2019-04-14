/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    playButton.setRadioGroupId(1);
    playButton.setToggleState(false, NotificationType::dontSendNotification);
    playButton.onClick = [this]() { play(); };
    addAndMakeVisible(playButton);
    
    stopButton.setRadioGroupId(1);
    playButton.setToggleState(true, NotificationType::dontSendNotification);
    stopButton.onClick = [this]() { stop(); };
    addAndMakeVisible(stopButton);
    
    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::play()
{
    playState = PlayState::Playing;
}

void MainComponent::stop()
{
    playState = PlayState::Stopped;
    metronome.reset();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    metronome.prepareToPlay(sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    auto buffer = bufferToFill.numSamples;
    
    if (playState == PlayState::Playing)
    {
        metronome.countSamples (buffer);
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    FlexBox flexBox;
    flexBox.items.add(FlexItem(100, 100, playButton));
    flexBox.items.add(FlexItem(100, 100, stopButton));
    flexBox.performLayout(bounds);
}
