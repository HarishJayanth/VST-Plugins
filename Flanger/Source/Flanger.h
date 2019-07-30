/*
  ==============================================================================

    Flanger.h
    Created: 23 Feb 2019 6:08:33pm
    Author:  hjvms

  ==============================================================================
*/

#pragma once

#include "LFO.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <memory>
#include  <vector>

class Flanger
{
public:
	Flanger(float ff_g = 0.5f, float fb_g = 0.5f, float lfo_freq = 0.2f, float lfo_amp = 0.2);
	~Flanger();
	void process(AudioBuffer<float>&);
	void setFlange_rate(float);
	float getFlange_rate() { return flangeLFO->getFreq(); }
	void setFlange_width(float);
	float getFlange_width() { return flangeLFO->getAmp(); }
	void setFlange_depth(float);
	float getFlange_depth() { return ff_gain; }
	void setFlange_feedback(float);
	float getFlange_feedback() { return fb_gain; }
	void set_fs(float);
	void setDelayLine_numChannels(int);

private:
	std::unique_ptr<LFO> flangeLFO;
	std::vector<std::vector<float>> delayLine;
	float ff_gain;
	float fb_gain;
	int delayLineSize;
	int delayVal;
	int wr_ptr;
};
