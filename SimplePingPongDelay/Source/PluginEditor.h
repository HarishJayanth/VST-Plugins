/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SimplePingPongDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                                 public Timer,
                                                 public Slider::Listener,
                                                 public Button::Listener
{
public:
    //==============================================================================
    SimplePingPongDelayAudioProcessorEditor (SimplePingPongDelayAudioProcessor& ownerProc);
    ~SimplePingPongDelayAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimplePingPongDelayAudioProcessor& processor;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<Slider> mixSlider;
    ScopedPointer<Slider> feedbackSlider;
    ScopedPointer<Label> delaySliderLabel;
    ScopedPointer<Label> mixSliderLabel;
    ScopedPointer<Label> feedbackSliderLabel;
    ScopedPointer<ToggleButton> bypassButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplePingPongDelayAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
