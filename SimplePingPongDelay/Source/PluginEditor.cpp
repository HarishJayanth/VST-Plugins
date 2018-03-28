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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SimplePingPongDelayAudioProcessorEditor::SimplePingPongDelayAudioProcessorEditor (SimplePingPongDelayAudioProcessor& ownerProc)
    : AudioProcessorEditor(ownerProc), processor(ownerProc)
{
    //[Constructor_pre] You can add your own custom stuff here..
	//startTimer(200); //refresh once every 200ms
    //[/Constructor_pre]

    addAndMakeVisible (delaySlider = new Slider ("delay"));
    delaySlider->setRange (60, 240, 1);
    delaySlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    delaySlider->addListener (this);
    delaySlider->setSkewFactor (2);

    delaySlider->setBounds (16, 8, 160, 152);

    addAndMakeVisible (mixSlider = new Slider ("mix"));
    mixSlider->setRange (0, 1, 0.01);
    mixSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    mixSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    mixSlider->addListener (this);

    mixSlider->setBounds (216, 8, 152, 152);

    addAndMakeVisible (feedbackSlider = new Slider ("feedback"));
    feedbackSlider->setRange (0, 1, 0.01);
    feedbackSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    feedbackSlider->addListener (this);

    feedbackSlider->setBounds (416, 8, 152, 152);

    addAndMakeVisible (delaySliderLabel = new Label ("delayLabel",
                                                     TRANS("DELAY")));
    delaySliderLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    delaySliderLabel->setJustificationType (Justification::centredLeft);
    delaySliderLabel->setEditable (false, false, false);
    delaySliderLabel->setColour (TextEditor::textColourId, Colours::black);
    delaySliderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    delaySliderLabel->setBounds (72, 62, 48, 24);

    addAndMakeVisible (mixSliderLabel = new Label ("mixLabel",
                                                   TRANS("MIX")));
    mixSliderLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    mixSliderLabel->setJustificationType (Justification::centredLeft);
    mixSliderLabel->setEditable (false, false, false);
    mixSliderLabel->setColour (TextEditor::textColourId, Colours::black);
    mixSliderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    mixSliderLabel->setBounds (274, 62, 39, 24);

    addAndMakeVisible (feedbackSliderLabel = new Label ("feedbackLabel",
                                                        TRANS("FEEDBACK")));
    feedbackSliderLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    feedbackSliderLabel->setJustificationType (Justification::centredLeft);
    feedbackSliderLabel->setEditable (false, false, false);
    feedbackSliderLabel->setColour (TextEditor::textColourId, Colours::black);
    feedbackSliderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    feedbackSliderLabel->setBounds (453, 62, 80, 24);

    addAndMakeVisible (bypassButton = new ToggleButton ("bypass"));
    bypassButton->setButtonText (TRANS("BYPASS"));
    bypassButton->addListener (this);

    bypassButton->setBounds (251, 168, 88, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 200);


    //[Constructor] You can add your own custom stuff here..
	delayAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_DELAY, *delaySlider);
	mixAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_MIX, *mixSlider);
	feedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FEEDBACK, *feedbackSlider);
	bypassAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.getState(), PARAM_BYPASS, *bypassButton);

	startTimer(200); // refresh once every 200ms
    //[/Constructor]
}

SimplePingPongDelayAudioProcessorEditor::~SimplePingPongDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	delayAttachment = nullptr;
	mixAttachment = nullptr;
	feedbackAttachment = nullptr;
	bypassAttachment = nullptr;
    //[/Destructor_pre]

    delaySlider = nullptr;
    mixSlider = nullptr;
    feedbackSlider = nullptr;
    delaySliderLabel = nullptr;
    mixSliderLabel = nullptr;
    feedbackSliderLabel = nullptr;
    bypassButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SimplePingPongDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SimplePingPongDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SimplePingPongDelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == mixSlider)
    {
        //[UserSliderCode_mixSlider] -- add your slider handling code here..
        //[/UserSliderCode_mixSlider]
    }
    else if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        //[/UserSliderCode_feedbackSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SimplePingPongDelayAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        //[/UserButtonCode_bypassButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimplePingPongDelayAudioProcessorEditor::timerCallback()
{
	// Do nothing for now.
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimplePingPongDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="SimplePingPongDelayAudioProcessor&amp; ownerProc"
                 variableInitialisers="AudioProcessorEditor(ownerProc), processor(ownerProc)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="200">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="delay" id="ed3c731212a723f3" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="16 8 160 152" min="60.00000000000000000000"
          max="240.00000000000000000000" int="1.00000000000000000000" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="2.00000000000000000000" needsCallback="1"/>
  <SLIDER name="mix" id="4a2d83326217f4d3" memberName="mixSlider" virtualName=""
          explicitFocusOrder="0" pos="216 8 152 152" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="feedback" id="ff3f0db0a2429cde" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="416 8 152 152" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="delayLabel" id="bc026b237a8af89b" memberName="delaySliderLabel"
         virtualName="" explicitFocusOrder="0" pos="72 62 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="DELAY" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="1" italic="0" justification="33"
         typefaceStyle="Bold"/>
  <LABEL name="mixLabel" id="685731689c3cf16c" memberName="mixSliderLabel"
         virtualName="" explicitFocusOrder="0" pos="274 62 39 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIX" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="1" italic="0" justification="33"
         typefaceStyle="Bold"/>
  <LABEL name="feedbackLabel" id="2a8d49e240d0368b" memberName="feedbackSliderLabel"
         virtualName="" explicitFocusOrder="0" pos="453 62 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="FEEDBACK" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="1" italic="0" justification="33"
         typefaceStyle="Bold"/>
  <TOGGLEBUTTON name="bypass" id="a441829f40fc6379" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="251 168 88 24" buttonText="BYPASS"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
