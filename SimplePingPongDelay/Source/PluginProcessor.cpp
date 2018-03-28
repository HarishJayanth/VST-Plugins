/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String GetStrValue(float v) { return String(v); };
static String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed" : "Enabled"; };

//==============================================================================
SimplePingPongDelayAudioProcessor::SimplePingPongDelayAudioProcessor()
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
	//set the sample rate and number of output channels in the ppDelay DSP object
	//ppDelay.setSampRate(getSampleRate());
	//ppDelay.setNumOutputChannels(getTotalNumOutputChannels());

	//create your state manager and give your current parameter set a name
	mUndoManager = new UndoManager;
	mState = new AudioProcessorValueTreeState(*this, mUndoManager);

	//add each of your parameters
	mState->createAndAddParameter(PARAM_BYPASS, "Bypass", "", NormalisableRange<float>(0, 1, 1), 0, GetBypassStr, nullptr);
	mState->createAndAddParameter(PARAM_DELAY, "Delay", "", NormalisableRange<float>(60, 240, 1), ppDelay.getDelay(), GetStrValue, nullptr);
	mState->createAndAddParameter(PARAM_MIX, "Mix", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), ppDelay.getMix(), GetStrValue, nullptr);
	mState->createAndAddParameter(PARAM_FEEDBACK, "Feedback", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), ppDelay.getFeedback(), GetStrValue, nullptr);

	//Once all parameters are added, it is safe to create the actual ValueTree
	mState->state = ValueTree(PARAM_SETNAME);

	//add any controls you want to trigger a deeper update timed with the call to process
	mState->addParameterListener(PARAM_DELAY, this);
	mState->addParameterListener(PARAM_MIX, this);
	mState->addParameterListener(PARAM_FEEDBACK, this);

	//start it off with deep updates regardless
	majorParamChange = true;
}

SimplePingPongDelayAudioProcessor::~SimplePingPongDelayAudioProcessor()
{
	mState = nullptr;
	mUndoManager = nullptr;
}

//==============================================================================
const String SimplePingPongDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimplePingPongDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimplePingPongDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimplePingPongDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimplePingPongDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimplePingPongDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimplePingPongDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimplePingPongDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String SimplePingPongDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimplePingPongDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimplePingPongDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimplePingPongDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimplePingPongDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SimplePingPongDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
	ppDelay.setSampRate(getSampleRate());
	if (majorParamChange)
	{
		//this is just an example (not really major), but this is where you would put code to reconfigure buffers or other major changes.
		ppDelay.setDelay((*mState->getRawParameterValue(PARAM_DELAY)));
		printf("%f", ppDelay.getDelay());
		ppDelay.setMix((*mState->getRawParameterValue(PARAM_MIX)));
		ppDelay.setFeedback((*mState->getRawParameterValue(PARAM_FEEDBACK)));
		majorParamChange = false;
	}

	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	if (totalNumInputChannels != 2 || totalNumOutputChannels != 2
		|| (*mState->getRawParameterValue(PARAM_BYPASS)) != 0.0f)
	{
	}/*Nothing to do here - processing is in-place, so doing nothing is pass-through (for NumInputs=NumOutputs)*/
	else
	{//Not bypassed - do processing!
		float** pChannelData = buffer.getArrayOfWritePointers();
		ppDelay.Process(pChannelData[0], pChannelData[1], buffer.getNumSamples());
	}
}

//==============================================================================
bool SimplePingPongDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimplePingPongDelayAudioProcessor::createEditor()
{
    return new SimplePingPongDelayAudioProcessorEditor (*this);
}

//==============================================================================
void SimplePingPongDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	
	//Save UserParams/Data to file
	MemoryOutputStream stream(destData, false);
	mState->state.writeToStream(stream);
}

void SimplePingPongDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	
	//Load UserParams/Data from file
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
	if (tree.isValid())
	{
		if (tree.hasType(PARAM_SETNAME))
		{
			mState->state = tree;
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimplePingPongDelayAudioProcessor();
}
