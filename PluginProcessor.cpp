/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//namespace juce

//==============================================================================
BinauralPanner_mscAudioProcessor::BinauralPanner_mscAudioProcessor()
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
    decodes.add("Octahedron");
    decodes.add("Square");
    decodes.add("Icosahedron");
    decodes.add("Dodecahedron");

    addParameter(ISEnable = new AudioParameterBool ("ISEnable","ImageSourceEnable",true,"image source enable"));
    addParameter(FVEnable = new AudioParameterBool("FVEnable","AmbiFreeverbEnable",true,"freeverb enable"));
    addParameter(numReflections = new AudioParameterInt("numRefs","numReflections",0,15,0,"num reflects"));
    addParameter(decodeArray = new AudioParameterChoice("Decode Array","decode array",decodes,0));

    addParameter(Ang = new AudioParameterFloat("Angle","Angle",0,360,0));
    addParameter(Elev = new AudioParameterFloat("Elev","Elev",-90,90,0));
    addParameter(roomsize = new AudioParameterFloat("RoomSize","RoomSize",0,1,0.5));
    addParameter(Damp = new AudioParameterFloat("Damp","Damp",0,1,0.5));
    addParameter(Scatter = new AudioParameterFloat("Scatter","Scatter",0,1,0.5));
    addParameter(Distance = new AudioParameterFloat("Distance","Distance",0,1,0));
}

BinauralPanner_mscAudioProcessor::~BinauralPanner_mscAudioProcessor()
{
}

//==============================================================================
const String BinauralPanner_mscAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BinauralPanner_mscAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BinauralPanner_mscAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BinauralPanner_mscAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BinauralPanner_mscAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BinauralPanner_mscAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BinauralPanner_mscAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BinauralPanner_mscAudioProcessor::setCurrentProgram (int index)
{
}

const String BinauralPanner_mscAudioProcessor::getProgramName (int index)
{
    return {};
}

void BinauralPanner_mscAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BinauralPanner_mscAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BinauralPanner_mscAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BinauralPanner_mscAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

//    if (layouts.getMainInputChannels() < 1
  //  || layouts.getMainOutputChannels() < 20)
  //  return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BinauralPanner_mscAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();



    juce::AudioBuffer<float> AmbiFreeverb, ImageSource, Input,Output;
    Input.clear();
    for (int j = 0; j < buffer.getNumSamples() ; ++j) {
        Input.setSample(0,j,buffer.getSample(0,j));
    }

    AmbiFreeverb = Freeverb.ProcessBlockfromMono(Input);
    ImageSource = Image.ProcessBlock(Input);

    buffer.clear();
    for (int k = 0; k <buffer.getNumSamples() ; ++k) {
        for (int j = 0; j <totalNumOutputChannels ; ++j) {
            float temp =0;
            if (enableFreeverb){ temp +=AmbiFreeverb.getSample(j, k);}
            if (enableImage){ temp +=ImageSource.getSample(j, k);}
            buffer.addSample(j,k,temp);
        }
    }

}

//==============================================================================
bool BinauralPanner_mscAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BinauralPanner_mscAudioProcessor::createEditor()
{
    return new BinauralPanner_mscAudioProcessorEditor (*this);
}

//==============================================================================
void BinauralPanner_mscAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BinauralPanner_mscAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void BinauralPanner_mscAudioProcessor::updateParams() {

    if(*ISEnable != enableImage){enableImage = *ISEnable;}
    if(*FVEnable != enableFreeverb){enableFreeverb = *FVEnable;}

    if(*roomsize != Freeverb.getRoomsize()){Freeverb.setRoomsize(*roomsize);}
    if(*Damp != Freeverb.getDamp()){Freeverb.setDamp(*Damp);}
    if(*Scatter != Freeverb.getScatter()){Freeverb.setScatter(*Scatter);}
    if(*Ang != Freeverb.getAng()){Freeverb.setAngle(*Ang);}
    if(*Elev != Freeverb.getElev()){Freeverb.setElev(*Elev);}

    if(*numReflections != Image.getNumReflections()){Image.generateRoomList(*numReflections);}
    if(*Ang != Image.getAngle()){Image.setAngle(*Ang);}
    if(*Elev != Image.getElev()){Image.setElev(*Ang);}
    if(*Distance != Image.getDistance()){Image.setDistance(*Distance);}

    switch (*decodeArray){

        case 0 :
            if(Image.vbap.getLocation() != MastersLocations::Octahedron) {Image.vbap.setLocation(MastersLocations::Octahedron)}
            break;

        case 1 :
            if(Image.vbap.getLocation() != MastersLocations::Square) {Image.vbap.setLocation(MastersLocations::Square)}
            break;

        case 2 :
            if(Image.vbap.getLocation() != MastersLocations::Icosahedron) {Image.vbap.setLocation(MastersLocations::Icosahedron)}
            break;

        case 3 :
            if(Image.vbap.getLocation() != MastersLocations::Dodecahedron) {Image.vbap.setLocation(MastersLocations::Dodecahedron)}
            break;

    }

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BinauralPanner_mscAudioProcessor();
}
