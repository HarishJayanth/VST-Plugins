/*
  ==============================================================================

    PingPongDelay.h
    Created: 27 Mar 2018 7:44:16pm
    Author:  hjvms

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PingPongDelay
{
public:
    PingPongDelay(int sr = 44100, int ch = 2);
    ~PingPongDelay();
    
    //Parameters
    void setDelay(int del);
	float getDelay(void) { return pp_delayTime; };
    void setFeedback(float fb);
	float getFeedback() { return pp_fb; };
    void setMix(float mix);
	float getMix() { return pp_mix; };
	void setSampRate(int sr) { sampRate = sr; };
	void setNumOutputChannels(int ch) { numOutputChannels = ch; };
    
    //Use
    void Process(float* leftSamples, float* rightSamples, int numSamp);

private:
    float pp_delayTime, pp_mix, pp_fb;
    int delayWritePointer;
    int maxDelay;

	int sampRate;
	int numOutputChannels;
    
    AudioSampleBuffer delayBuf;
};