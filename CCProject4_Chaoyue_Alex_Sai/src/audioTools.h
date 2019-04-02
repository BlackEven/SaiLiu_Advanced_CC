#ifndef audioTools_h
#define audioTools_h

#include "ofMain.h"
//-------------------------------------------------
class oscillator {

public:
	void setup(float _frequency, double _phase, float _amplitude, int _sampleRate);
	float getSample(string _wavetype);

	void setFrequency(float _freq);
	void setAmplitude(float _amp);

private:
	int sampleRate;
	float frequency;
	double phase;
	double phaseInc;
	float amplitude;
	float currentSample;
};



class parameterSmoother {

public:

	parameterSmoother(float smoothingTimeMS, int sampleRate) {
		//creates a coefficient that will take input milliseconds
		//and give us the coefficient needed to filter out
		//and arrive at our destination or near enough 
		a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * sampleRate));
		b = 1.0 - a;
		z = 0.0;
	}

	void setup(float smoothingTimeMS, int sampleRate) {
		a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * sampleRate));
		b = 1.0 - a;
		z = 0.0;
	}
	
	//inline fuction makes the processor has fast access to it
	inline float process(float input) {
		z = (input * b) + (z * a);
		return z;
	}

private:
	float a;
	float b;
	float z;
};

//use struct to make code clear and clean
struct smoothValue {
	float targetValue;
	float currentValue;
	parameterSmoother* smoother;
};




#endif
