/*
  ==============================================================================

    LFO.h
    Created: 23 Feb 2019 6:06:31pm
    Author:  hjvms

  ==============================================================================
*/

#pragma once

#include <vector>
class LFO
{
public:
	LFO(float fs = 48000.0f, float freq = 5.0f, float amp = 1.0f);
	LFO(std::vector<float> sig, float fs = 48000.0f, float freq = 5.0f, float amp = 1.0f);
	~LFO()
	{

	}
	void setSampleRate(float);
	float getSampleRate() { return _fs; }
	void setFreq(float);
	float getFreq() { return _freq; }
	void setAmp(float);
	float getAmp() { return _amp; }
	float getNextSamp();
private:
	std::vector<float> wavetable;
	float _fs;
	float _freq;
	float _amp;
	float rdPtr;
	int wtSize;
	float phase_update;
};