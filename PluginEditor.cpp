/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

//==============================================================================
EthanMp02eqAudioProcessorEditor::EthanMp02eqAudioProcessorEditor (EthanMp02eqAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
    // Setup your sliders and other gui components - - - -
    auto& params = processor.getParameters();
    // Cuttoff Freq Slider
    AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(0);
    mFilterGainLowSlider.setBounds(0, 0, 100, 160);
    mFilterGainLowSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mFilterGainLowSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    mFilterGainLowSlider.setRange(audioParam->range.start, audioParam->range.end);
    mFilterGainLowSlider.setValue(*audioParam);
    mFilterGainLowSlider.addListener(this);
    addAndMakeVisible(mFilterGainLowSlider);
    
    

    
        // ------------
    
        // Cuttoff Freq Slider
        audioParam = (AudioParameterFloat*)params.getUnchecked(1);
        mFilterGainPeakSlider.setBounds(100, 0, 100, 160);
        mFilterGainPeakSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        mFilterGainPeakSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
        mFilterGainPeakSlider.setRange(audioParam->range.start, audioParam->range.end);
        mFilterGainPeakSlider.setValue(*audioParam);
        mFilterGainPeakSlider.addListener(this);
        addAndMakeVisible(mFilterGainPeakSlider);
    

    
        // Cuttoff Freq Slider
        audioParam = (AudioParameterFloat*)params.getUnchecked(2);
        mFilterGainHighSlider.setBounds(200, 0, 100, 160);
        mFilterGainHighSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        mFilterGainHighSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
        mFilterGainHighSlider.setRange(audioParam->range.start, audioParam->range.end);
        mFilterGainHighSlider.setValue(*audioParam);
        mFilterGainHighSlider.addListener(this);
        addAndMakeVisible(mFilterGainHighSlider);
    
        // Q slider
        audioParam = (AudioParameterFloat*)params.getUnchecked(3);
        QPeak.setBounds(200, 190, 100, 80);
        QPeak.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
        //mFilterQSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        QPeak.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
        QPeak.setRange(audioParam->range.start, audioParam->range.end);
        QPeak.setValue(*audioParam);
        QPeak.addListener(this);
        addAndMakeVisible(QPeak);
}

EthanMp02eqAudioProcessorEditor::~EthanMp02eqAudioProcessorEditor()
{
}

void EthanMp02eqAudioProcessorEditor::sliderValueChanged(Slider * slider){
    auto& params = processor.getParameters();

    if (slider == &mFilterGainLowSlider) {
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(0);
        *audioParam = mFilterGainLowSlider.getValue(); // set the AudioParameter
        DBG("Fc Slider Changed");
    }else if(slider == &mFilterGainPeakSlider){
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = mFilterGainPeakSlider.getValue(); // set the param
        DBG("Q Slider Changed");
    }else if(slider == &mFilterGainHighSlider){
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = mFilterGainHighSlider.getValue(); // set the param
        DBG("Q Slider Changed");
    }else if(slider == &QPeak){
        AudioParameterFloat* audioParam = (AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = QPeak.getValue(); // set the param
        DBG("Q Slider Changed");
    }
    
}

//==============================================================================
void EthanMp02eqAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::darkolivegreen);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawSingleLineText ("Gain Low", 50, 175, Justification::centred);
    g.drawSingleLineText ("Gain Peak", 150, 175, Justification::centred);
    g.drawSingleLineText ("Gain High", 250, 175, Justification::centred);
    
    g.drawSingleLineText ("Peak Q", 180, 265, Justification::centred);
    
    
    
}

void EthanMp02eqAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
