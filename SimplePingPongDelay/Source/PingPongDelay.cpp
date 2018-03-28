/*
  ==============================================================================

    PingPongDelay.cpp
    Created: 27 Mar 2018 7:44:04pm
    Author:  hjvms

  ==============================================================================
*/

#include "PingPongDelay.h"
#include "../JuceLibraryCode/JuceHeader.h"

PingPongDelay::PingPongDelay(int sr, int ch)
{
	sampRate = sr;
	numOutputChannels = ch;
    maxDelay = 5.0 * (float)sampRate;
    delayBuf.setSize(numOutputChannels, maxDelay);
	delayBuf.clear();
	delayWritePointer = 0;
	
    setDelay(120);
    setFeedback(0.5);
    setMix(0.5);
}

PingPongDelay::~PingPongDelay(){}

void PingPongDelay::setDelay(int del)
{
    pp_delayTime = (60.0 / (float)del) * (float)sampRate;
}

void PingPongDelay::setMix(float mix)
{
    pp_mix = mix;
}

void PingPongDelay::setFeedback(float fb)
{
    pp_fb = fb;
}

void PingPongDelay::Process(float* leftSamples, float* rightSamples, int numSamp)
{
    float currentDelayTime = pp_delayTime;
	float currentFeedback = pp_fb;
	float currentMix = pp_mix;
	
	float* delayDataL = delayBuf.getWritePointer(0);
	float* delayDataR = delayBuf.getWritePointer(1);

	int localWritePointer = delayWritePointer;
	
	for (int i = 0; i < numSamp; ++i)
	{
		float outL, outR;
		float readPosition = fmodf((float)localWritePointer - currentDelayTime + (float)maxDelay, (float)maxDelay);
		int localReadPosition = floorf(readPosition);

		float frac = readPosition - (float)localReadPosition;
		outL = delayDataL[localReadPosition] + frac * (delayDataL[(localReadPosition + 1) % maxDelay] - delayDataL[localReadPosition]);
		outR = delayDataR[localReadPosition] + frac * (delayDataR[(localReadPosition + 1) % maxDelay] - delayDataR[localReadPosition]);

		delayDataL[localWritePointer] = leftSamples[i] + currentFeedback * outR;
		delayDataR[localWritePointer] = currentFeedback * outL;
		leftSamples[i] = leftSamples[i] + currentMix * outL;
		rightSamples[i] = rightSamples[i] + currentMix * outR;
		

		localWritePointer = (localWritePointer + 1) % maxDelay;
	}
	delayWritePointer = localWritePointer;
}