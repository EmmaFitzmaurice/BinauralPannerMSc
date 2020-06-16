/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MastersLocations.h"
#include "EF_ImageSourceReverb.h"
#include "EF_AmbiFreeverb.h"
#include "EF_VBAP.h"

//==============================================================================
/**
*/
class BinauralPanner_mscAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BinauralPanner_mscAudioProcessor();
    ~BinauralPanner_mscAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, MidiBuffer&) override;

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




    bool enableFreeverb, enableImage;
    EF_ImageSourceReverb Image;
    EF_AmbiFreeverb Freeverb;

    void updateParams();

    StringArray decodes;
    AudioParameterBool* ISEnable;
    AudioParameterBool* FVEnable;
    AudioParameterInt* numReflections;
    AudioParameterChoice* decodeArray;

    AudioParameterFloat* Ang;
    AudioParameterFloat* Elev;
    AudioParameterFloat* roomsize;
    AudioParameterFloat* Damp;
    AudioParameterFloat* Scatter;
    AudioParameterFloat* Distance;

   // MastersLocations ML;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BinauralPanner_mscAudioProcessor)
};
