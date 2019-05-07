#include "audioTools.h"


//----------------------------------------------oscillator
void oscillator::setup(float _frequency, double _phase, float _amplitude, int _sampleRate) {
	frequency = _frequency;
	phase = _phase;
	amplitude = _amplitude;
	sampleRate = _sampleRate;
	phaseInc = (TWO_PI*frequency) / (double)sampleRate;
	currentSample = 0;
}

float oscillator::getSample(string _wavetype) {
	if (_wavetype == "sine") {
		currentSample = sin(phase) * amplitude;
		phase += (TWO_PI*frequency) / (double)sampleRate;
		if (phase > TWO_PI) {
			phase -= TWO_PI;
		}
		return currentSample;
	}
	else if (_wavetype == "tri") {
		if (phase < PI) {
			currentSample = -amplitude + (2 * amplitude / PI)*phase;
		}
		else {
			currentSample = 3 * amplitude - (2 * amplitude / PI)*phase;
		}
		phase += TWO_PI * frequency / sampleRate;
		if (phase > TWO_PI) {
			phase -= TWO_PI;
		}
		return currentSample;
	}
	else if (_wavetype == "saw") {
		currentSample = amplitude - (amplitude / PI * phase);
		phase += ((TWO_PI*frequency) / sampleRate);
		if (phase > TWO_PI) {
			phase -= TWO_PI;
		}
		return currentSample;
	}
	else if (_wavetype == "square") {
		if (phase < PI) {
			currentSample = amplitude;
		}
		else {
			currentSample = -amplitude;
		}
		phase += (TWO_PI*frequency) / sampleRate;
		if (phase > TWO_PI) {
			phase -= TWO_PI;
		}
		return currentSample;

	}
}

void oscillator::setFrequency(float _freq) {
	frequency = _freq;
	phaseInc = (TWO_PI*frequency) / (double)sampleRate;
}

void oscillator::setAmplitude(float _amp) {
	amplitude = _amp;
}




