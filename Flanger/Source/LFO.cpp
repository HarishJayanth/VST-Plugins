/*
  ==============================================================================

    LFO.cpp
    Created: 23 Feb 2019 6:06:31pm
    Author:  hjvms

  ==============================================================================
*/

#include "LFO.h"
#define _USE_MATH_DEFINES
#include <math.h>

LFO::LFO(float fs, float freq, float amp) :
	_fs(fs),
	_freq(freq),
	_amp(amp)
{
	// Generate default sine wavetable of 1024 samples
	wtSize = 1024;
	wavetable.resize(wtSize);
	for (int i = 0; i < wtSize; i++)
	{
		wavetable[i] = std::sinf(2 * M_PI * i / wtSize);
	}
	rdPtr = 0;
	phase_update = wtSize * _freq / _fs;
}

LFO::LFO(std::vector<float> sig, float fs, float freq, float amp):
	wavetable(sig),
	_fs(fs),
	_freq(freq),
	_amp(amp)
{
	wtSize = wavetable.size();
	rdPtr = 0;
	phase_update = wtSize * _freq / _fs;
}

void LFO::setAmp(float amp)
{
	_amp = amp;
}

void LFO::setFreq(float freq)
{
	_freq = freq;
	phase_update = wtSize * _freq / _fs;
}

void LFO::setSampleRate(float fs)
{
	_fs = fs;
	phase_update = wtSize * _freq / _fs;
}

float LFO::getNextSamp()
{
	float nextSamp;

	rdPtr += phase_update;
	int prevInd = (int)std::floor(rdPtr);
	int nextInd = prevInd + 1;
	float delta_n = rdPtr - prevInd;

	rdPtr = std::fmodf(rdPtr, wtSize-1);
	prevInd %= wtSize;
	nextInd %= wtSize;

	nextSamp = _amp * (delta_n * (wavetable[nextInd] - wavetable[prevInd]) + wavetable[prevInd]);

	return nextSamp;
}