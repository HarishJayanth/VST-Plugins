/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String GetStrValue(float v) { return String(v); };
static String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed": "Enabled"; };
//==============================================================================
MyFlangerAudioProcessor::MyFlangerAudioProcessor()
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
	//create your state manager and give your current parameter set a name

	mUndoManager = new UndoManager();
	mState = new AudioProcessorValueTreeState(*this, mUndoManager);

	//add each of your parameters

	mState->createAndAddParameter(PARAM_BYPASS, "Bypass", "", NormalisableRange<float>(0, 1, 1), 0, GetBypassStr, nullptr);
	mState->createAndAddParameter(PARAM_DEPTH, "Flanger Depth", "", NormalisableRange<float>(0.0f, 1.0f, 0.0f), mFlanger.getFlange_depth(), GetStrValue, nullptr);
	mState->createAndAddParameter(PARAM_FEEDBACK, "Flanger Feedback", "", NormalisableRange<float>(0.0f, 1.0f, 0.0f), mFlanger.getFlange_feedback(), GetStrValue, nullptr);
	mState->createAndAddParameter(PARAM_RATE, "Flanger Rate", "", NormalisableRange<float>(0.0f, 5.0f, 0.0f), mFlanger.getFlange_rate(), GetStrValue, nullptr);
	mState->createAndAddParameter(PARAM_WIDTH, "Flanger Width", "", NormalisableRange<float>(0.0f, 10.0f, 0.0f), mFlanger.getFlange_width(), GetStrValue, nullptr);

	//Once all parameters are added, it is safe to create the actual ValueTree

	mState->state = ValueTree(PARAM_SETNAME);

	//add any controls you want to trigger a deeper update timed with the call to process

	mState->addParameterListener(PARAM_DEPTH, this);
	mState->addParameterListener(PARAM_FEEDBACK, this);
	mState->addParameterListener(PARAM_RATE, this);
	mState->addParameterListener(PARAM_WIDTH, this);

	//start it off with deep updates regardless

	MajorParamChange = true;
}

MyFlangerAudioProcessor::~MyFlangerAudioProcessor()
{
	mState = nullptr;
	mUndoManager = nullptr;
}

//==============================================================================
const String MyFlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyFlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyFlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyFlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyFlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyFlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyFlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyFlangerAudioProcessor::setCurrentProgram (int index)
{
}

const String MyFlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyFlangerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MyFlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	mFlanger.set_fs(sampleRate);

}

void MyFlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyFlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MyFlangerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	if (MajorParamChange)
	{

		//this is just an example (not really major), but this is where you would put code to reconfigure buffers or other major changes.

		mFlanger.setFlange_width((*mState->getRawParameterValue(PARAM_WIDTH)));
		mFlanger.setFlange_rate((*mState->getRawParameterValue(PARAM_RATE)));
		mFlanger.setFlange_feedback((*mState->getRawParameterValue(PARAM_FEEDBACK)));
		mFlanger.setFlange_depth((*mState->getRawParameterValue(PARAM_DEPTH)));
		MajorParamChange = false;
	}

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	if (*mState->getRawParameterValue(PARAM_BYPASS) == 0.0f)
		mFlanger.process(buffer);

}

//==============================================================================
bool MyFlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MyFlangerAudioProcessor::createEditor()
{
    return new MyFlangerAudioProcessorEditor (*this);
}

//==============================================================================
void MyFlangerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream(destData, false);
	mState->state.writeToStream(stream);
}

void MyFlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
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
    return new MyFlangerAudioProcessor();
}
