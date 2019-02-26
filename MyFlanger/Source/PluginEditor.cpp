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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MyFlangerAudioProcessorEditor::MyFlangerAudioProcessorEditor (MyFlangerAudioProcessor& ownerProc)
    : AudioProcessorEditor(ownerProc),
      processor(ownerProc)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    depth_slider.reset (new Slider ("depth_slider"));
    addAndMakeVisible (depth_slider.get());
    depth_slider->setRange (0, 1, 0);
    depth_slider->setSliderStyle (Slider::RotaryVerticalDrag);
    depth_slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    depth_slider->addListener (this);

    depth_slider->setBounds (8, 24, 112, 96);

    rate_slider.reset (new Slider ("rate_slider"));
    addAndMakeVisible (rate_slider.get());
    rate_slider->setRange (0, 5, 0);
    rate_slider->setSliderStyle (Slider::RotaryVerticalDrag);
    rate_slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    rate_slider->addListener (this);

    rate_slider->setBounds (136, 24, 112, 96);

    feedback_slider.reset (new Slider ("feedback_slider"));
    addAndMakeVisible (feedback_slider.get());
    feedback_slider->setRange (0, 0.99, 0);
    feedback_slider->setSliderStyle (Slider::RotaryVerticalDrag);
    feedback_slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    feedback_slider->addListener (this);

    feedback_slider->setBounds (392, 24, 112, 96);

    bypass_toggleButton.reset (new ToggleButton ("bypass_toggleButton"));
    addAndMakeVisible (bypass_toggleButton.get());
    bypass_toggleButton->setButtonText (TRANS("Bypass"));
    bypass_toggleButton->addListener (this);

    bypass_toggleButton->setBounds (224, 160, 80, 24);

    depth_label.reset (new Label ("depth_label",
                                  TRANS("Depth")));
    addAndMakeVisible (depth_label.get());
    depth_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    depth_label->setJustificationType (Justification::centredLeft);
    depth_label->setEditable (false, false, false);
    depth_label->setColour (TextEditor::textColourId, Colours::black);
    depth_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    depth_label->setBounds (41, 120, 47, 24);

    rate_label.reset (new Label ("rate_label",
                                 TRANS("Rate")));
    addAndMakeVisible (rate_label.get());
    rate_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rate_label->setJustificationType (Justification::centredLeft);
    rate_label->setEditable (false, false, false);
    rate_label->setColour (TextEditor::textColourId, Colours::black);
    rate_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rate_label->setBounds (173, 120, 40, 24);

    feedback_label.reset (new Label ("feedback_label",
                                     TRANS("Feedback")));
    addAndMakeVisible (feedback_label.get());
    feedback_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    feedback_label->setJustificationType (Justification::centredLeft);
    feedback_label->setEditable (false, false, false);
    feedback_label->setColour (TextEditor::textColourId, Colours::black);
    feedback_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    feedback_label->setBounds (416, 120, 64, 24);

    width_slider.reset (new Slider ("width_slider"));
    addAndMakeVisible (width_slider.get());
    width_slider->setRange (0, 10, 0);
    width_slider->setSliderStyle (Slider::RotaryVerticalDrag);
    width_slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    width_slider->addListener (this);

    width_slider->setBounds (264, 24, 112, 96);

    width_label.reset (new Label ("width_slider",
                                  TRANS("Width\n")));
    addAndMakeVisible (width_label.get());
    width_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    width_label->setJustificationType (Justification::centredLeft);
    width_label->setEditable (false, false, false);
    width_label->setColour (TextEditor::textColourId, Colours::black);
    width_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    width_label->setBounds (297, 120, 48, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (513, 200);


    //[Constructor] You can add your own custom stuff here..
	bypass_toggleButton->setClickingTogglesState(true);

	mWidthAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_WIDTH, *width_slider);
	mDepthAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_DEPTH, *depth_slider);
	mFeedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FEEDBACK, *feedback_slider);
	mRateAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_RATE, *rate_slider);

	mBypassAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.getState(), PARAM_BYPASS, *bypass_toggleButton);
    startTimer(200);    // Refresh GUI every 200 ms
    //[/Constructor]
}

MyFlangerAudioProcessorEditor::~MyFlangerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	mWidthAttachment = nullptr;
	mDepthAttachment = nullptr;
	mFeedbackAttachment = nullptr;
	mRateAttachment = nullptr;
	mBypassAttachment = nullptr;
    //[/Destructor_pre]

    depth_slider = nullptr;
    rate_slider = nullptr;
    feedback_slider = nullptr;
    bypass_toggleButton = nullptr;
    depth_label = nullptr;
    rate_label = nullptr;
    feedback_label = nullptr;
    width_slider = nullptr;
    width_label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MyFlangerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 156, y = -2, width = 200, height = 30;
        String text (TRANS("Flanger"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (21.20f, Font::plain).withTypefaceStyle ("Bold Italic"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MyFlangerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MyFlangerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == depth_slider.get())
    {
        //[UserSliderCode_depth_slider] -- add your slider handling code here..
        //[/UserSliderCode_depth_slider]
    }
    else if (sliderThatWasMoved == rate_slider.get())
    {
        //[UserSliderCode_rate_slider] -- add your slider handling code here..
        //[/UserSliderCode_rate_slider]
    }
    else if (sliderThatWasMoved == feedback_slider.get())
    {
        //[UserSliderCode_feedback_slider] -- add your slider handling code here..
        //[/UserSliderCode_feedback_slider]
    }
    else if (sliderThatWasMoved == width_slider.get())
    {
        //[UserSliderCode_width_slider] -- add your slider handling code here..
        //[/UserSliderCode_width_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MyFlangerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypass_toggleButton.get())
    {
        //[UserButtonCode_bypass_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_bypass_toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MyFlangerAudioProcessorEditor::timerCallback()
{

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MyFlangerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="MyFlangerAudioProcessor&amp; ownerProc" variableInitialisers="AudioProcessorEditor(ownerProc)&#10;processor(ownerProc)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="513" initialHeight="200">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="156 -2 200 30" fill="solid: ffffffff" hasStroke="0" text="Flanger"
          fontname="Default font" fontsize="21.19999999999999928946" kerning="0.00000000000000000000"
          bold="1" italic="1" justification="36" typefaceStyle="Bold Italic"/>
  </BACKGROUND>
  <SLIDER name="depth_slider" id="af39e8c52c6eaed7" memberName="depth_slider"
          virtualName="" explicitFocusOrder="0" pos="8 24 112 96" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00000000000000000000" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="rate_slider" id="5b25e413a2d5e82b" memberName="rate_slider"
          virtualName="" explicitFocusOrder="0" pos="136 24 112 96" min="0.00000000000000000000"
          max="5.00000000000000000000" int="0.00000000000000000000" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="feedback_slider" id="405d670d61519114" memberName="feedback_slider"
          virtualName="" explicitFocusOrder="0" pos="392 24 112 96" min="0.00000000000000000000"
          max="0.98999999999999999112" int="0.00000000000000000000" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TOGGLEBUTTON name="bypass_toggleButton" id="86e9f4c11ae9419a" memberName="bypass_toggleButton"
                virtualName="" explicitFocusOrder="0" pos="224 160 80 24" buttonText="Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="depth_label" id="ff3671f524883010" memberName="depth_label"
         virtualName="" explicitFocusOrder="0" pos="41 120 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Depth" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="rate_label" id="8c7641a65b39a54c" memberName="rate_label"
         virtualName="" explicitFocusOrder="0" pos="173 120 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rate" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="feedback_label" id="f26b0b49ee19b783" memberName="feedback_label"
         virtualName="" explicitFocusOrder="0" pos="416 120 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <SLIDER name="width_slider" id="34d8a4db2c065cb" memberName="width_slider"
          virtualName="" explicitFocusOrder="0" pos="264 24 112 96" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="width_slider" id="ea8f5822641acd62" memberName="width_label"
         virtualName="" explicitFocusOrder="0" pos="297 120 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Width&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
