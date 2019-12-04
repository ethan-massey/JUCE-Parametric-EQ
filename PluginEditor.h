/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class EthanMp02eqAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    EthanMp02eqAudioProcessorEditor (EthanMp02eqAudioProcessor&);
    ~EthanMp02eqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    // Mu45: add these functions!
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EthanMp02eqAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EthanMp02eqAudioProcessorEditor)
    
    Slider mFilterGainLowSlider;
    Slider mFilterGainPeakSlider;
    Slider mFilterGainHighSlider;
    
    Slider QPeak;
};
