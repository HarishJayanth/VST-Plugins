/*
  ==============================================================================

    Flanger.cpp
    Created: 23 Feb 2019 6:08:33pm
    Author:  hjvms

  ==============================================================================
*/

#include "Flanger.h"
#include <assert.h>

Flanger::Flanger(float ff_g, float fb_g, float lfo_freq, float lfo_amp) :
	ff_gain(ff_g),
	fb_gain(fb_g),
	wr_ptr(0)
{
	flangeLFO.reset(new LFO(48000.0f, lfo_freq, lfo_amp));
	delayVal = std::ceil(lfo_amp) + 1;

	if (fb_gain >= 1) 
		fb_gain = 0.99f;
}
Flanger::~Flanger()
{
	delayLine.clear();
}

void Flanger::setFlange_depth(float depth)
{
	ff_gain = std::max(depth, 1.0f);
}

void Flanger::setFlange_rate(float rate)
{
	flangeLFO->setFreq(rate);
}

void Flanger::setFlange_feedback(float fb_g)
{
	fb_gain = std::max(fb_g, 0.99f);
}

void Flanger::setFlange_width(float width)
{
	flangeLFO->setAmp(width);
	delayVal = std::ceil(width) + 1;
}

void Flanger::set_fs(float fs)
{
	flangeLFO->setSampleRate(fs);
	delayLineSize = 2.0*fs; 
	for (int i = 0; i < delayLine.size(); i++)
		delayLine[i].resize(delayLineSize);
}

void Flanger::setDelayLine_numChannels(int numChannels)
{
	delayLine.resize(numChannels);
	delayLineSize = 2.0*flangeLFO->getSampleRate();
	for (int i = 0; i < delayLine.size(); i++)
		delayLine[i].resize(delayLineSize);
	wr_ptr = 0;
}

void Flanger::process(AudioBuffer<float>& inBuf)
{
	int numChannels = inBuf.getNumChannels();
	int numSamps = inBuf.getNumSamples();

	float** buf = inBuf.getArrayOfWritePointers();

	if (delayLine.size() != numChannels)	// check if delayLine has same number of channels
		setDelayLine_numChannels(numChannels);

	float flangeSamp;
	for (int j = 0; j < numSamps; j++)
	{
		double rd_ptr =(double)wr_ptr - (delayVal + flangeLFO->getNextSamp());
		if (rd_ptr < 0) rd_ptr += delayLineSize;
		int prevSamp = (int)std::floor(rd_ptr) % delayLineSize;
		int nextSamp = (prevSamp + 1) % delayLineSize;
		double delta = rd_ptr - prevSamp;
		for (int i = 0; i < numChannels; i++)
		{
			flangeSamp = delta * (delayLine[i][nextSamp] - delayLine[i][prevSamp]) + delayLine[i][prevSamp];
			delayLine[i][wr_ptr] = buf[i][j] + fb_gain*flangeSamp;
			buf[i][j] += (ff_gain*flangeSamp);
		}
		wr_ptr = (wr_ptr + 1) % delayLineSize;
	}
}