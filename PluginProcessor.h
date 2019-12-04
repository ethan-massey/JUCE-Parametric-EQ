/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mu45FilterCalc/Mu45FilterCalc.h"
#include "StkLite-4.6.1/BiQuad.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class EthanMp02eqAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EthanMp02eqAudioProcessor();
    ~EthanMp02eqAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EthanMp02eqAudioProcessor)
    
    void calcAlgorithmParams();
    
    // User Parameters
    AudioParameterFloat *mFilterGainLowParam;
    AudioParameterFloat *mFilterGainPeakParam;
    AudioParameterFloat *mFilterGainHighParam;
    
    AudioParameterFloat *QPeakParam;
    
    
    
    
    // Member objects we need
    // The filters
    stk::BiQuad mFilterLowL, mFilterLowR;
    stk::BiQuad mFilterPeakL, mFilterPeakR;
    stk::BiQuad mFilterHighL, mFilterHighR;
    
    float mFs;                      // Sampling rate
    
    
};
