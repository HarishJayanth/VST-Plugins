/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Flanger.h"

//==============================================================================
/**
*/
class MyFlangerAudioProcessor  : public AudioProcessor,
								 public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    MyFlangerAudioProcessor();
    ~MyFlangerAudioProcessor();

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

	// Parameters
#define PARAM_SETNAME "MyFlanger"
#define PARAM_DEPTH "Depth"
#define PARAM_RATE "Rate"
#define PARAM_FEEDBACK "Feedback"
#define PARAM_WIDTH "Width"
#define PARAM_BYPASS "Bypass"
	
	AudioProcessorValueTreeState& getState() { return *mState; };
	void parameterChanged(const String& parameterID, float newValue)

	{
		MajorParamChange = true;
	};
private:
    //==============================================================================
	//Private Data, helper methods etc.

	bool MajorParamChange;
	ScopedPointer<AudioProcessorValueTreeState> mState;
	ScopedPointer<UndoManager> mUndoManager;

	//DSP

	Flanger mFlanger;	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyFlangerAudioProcessor)
};
