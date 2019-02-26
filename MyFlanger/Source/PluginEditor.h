/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Flanger.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MyFlangerAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Timer,
                                       public Slider::Listener,
                                       public Button::Listener
{
public:
    //==============================================================================
    MyFlangerAudioProcessorEditor (MyFlangerAudioProcessor& ownerProc);
    ~MyFlangerAudioProcessorEditor();

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
    MyFlangerAudioProcessor& processor;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mWidthAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mDepthAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mRateAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mFeedbackAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> mBypassAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> depth_slider;
    std::unique_ptr<Slider> rate_slider;
    std::unique_ptr<Slider> feedback_slider;
    std::unique_ptr<ToggleButton> bypass_toggleButton;
    std::unique_ptr<Label> depth_label;
    std::unique_ptr<Label> rate_label;
    std::unique_ptr<Label> feedback_label;
    std::unique_ptr<Slider> width_slider;
    std::unique_ptr<Label> width_label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyFlangerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
