/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EthanMp02eqAudioProcessor::EthanMp02eqAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Instantiate your AudioParameters - - - -

    addParameter(mFilterGainLowParam = new AudioParameterFloat("Gain Low", // parameterID,
                                                          "Gain Low", // parameterName,
                                                          -6.0f,    // minValue,
                                                          12.0f, // maxValue,
                                                          1.0f)); // defaultValue

    addParameter(mFilterGainPeakParam = new AudioParameterFloat("Gain Peak", // parameterID,
                                                         "Gain Peak",   // parameterName,
                                                         -6.0f,      // minValue,
                                                         12.0f,     // maxValue,
                                                         1.0f));    // defaultValue

    addParameter(mFilterGainHighParam = new AudioParameterFloat("Gain High", // parameterID,
                                                               "Gain High", // parameterName,
                                                               -6.0f,    // minValue,
                                                               12.0f, // maxValue,
                                                               1.0f)); // defaultValue
    
    addParameter(QPeakParam = new AudioParameterFloat("Peak Q", // parameterID,
                                                                "Peak Q", // parameterName,
                                                                -6.0f,    // minValue,
                                                                10.0f, // maxValue,
                                                                1.0f)); // defaultValue
    
    

    
    
}

EthanMp02eqAudioProcessor::~EthanMp02eqAudioProcessor()
{
}

//==============================================================================
const String EthanMp02eqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EthanMp02eqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EthanMp02eqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EthanMp02eqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EthanMp02eqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EthanMp02eqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EthanMp02eqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EthanMp02eqAudioProcessor::setCurrentProgram (int index)
{
}

const String EthanMp02eqAudioProcessor::getProgramName (int index)
{
    return {};
}

void EthanMp02eqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EthanMp02eqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback initialisation
    mFs = sampleRate;
}

void EthanMp02eqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EthanMp02eqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EthanMp02eqAudioProcessor::calcAlgorithmParams(){
    // Calc filter coefficients
    float coeffsL[5]; // an array of 5 floats for filter coeffs
    float coeffsP[5];
    float coeffsH[5];
    
    float GainLow = mFilterGainLowParam->get();
    
    float GainPeak = mFilterGainPeakParam->get();
    
    float GainHigh = mFilterGainHighParam->get();
    
    float QPeak = QPeakParam->get();

    
    Mu45FilterCalc::calcCoeffsLowShelf(coeffsL, 200, GainLow, mFs);
    
    Mu45FilterCalc::calcCoeffsPeak(coeffsP, 2000, GainPeak, QPeak, mFs);
    
    Mu45FilterCalc::calcCoeffsHighShelf(coeffsH, 20000, GainHigh, mFs);
    
    // Set the coefficients for each filter
    // low
    mFilterLowL.setCoefficients(coeffsL[0], coeffsL[1], coeffsL[2], coeffsL[3], coeffsL[4]);
    mFilterLowR.setCoefficients(coeffsL[0], coeffsL[1], coeffsL[2], coeffsL[3], coeffsL[4]);
    // peak
    mFilterPeakL.setCoefficients(coeffsP[0], coeffsP[1], coeffsP[2], coeffsP[3], coeffsP[4]);
    mFilterPeakR.setCoefficients(coeffsP[0], coeffsP[1], coeffsP[2], coeffsP[3], coeffsP[4]);
    // high
    mFilterHighL.setCoefficients(coeffsH[0], coeffsH[1], coeffsH[2], coeffsH[3], coeffsH[4]);
    mFilterHighR.setCoefficients(coeffsH[0], coeffsH[1], coeffsH[2], coeffsH[3], coeffsH[4]);
    
}

void EthanMp02eqAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // JUCE stuff to make sure there's no bad data in the output buffers
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Update the parameter values
    calcAlgorithmParams();
    
    // Process each audio sample
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++) {

        // Pass through low
        channelDataLeft[samp] = mFilterLowL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = mFilterLowR.tick(channelDataRight[samp]);
////        // then peak
        channelDataLeft[samp] = mFilterPeakL.tick(channelDataLeft[samp]);
        channelDataRight[samp] = mFilterPeakR.tick(channelDataRight[samp]);
////        // then high
        channelDataLeft[samp] = mFilterHighL.tick(channelDataLeft[samp]) ;
        channelDataRight[samp] = mFilterHighR.tick(channelDataRight[samp]);
        
        
//
    }
}

//==============================================================================
bool EthanMp02eqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EthanMp02eqAudioProcessor::createEditor()
{
    return new EthanMp02eqAudioProcessorEditor (*this);
}

//==============================================================================
void EthanMp02eqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EthanMp02eqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EthanMp02eqAudioProcessor();
}
