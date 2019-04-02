

#ifndef EnvelopeGenerator_hpp
#define EnvelopeGenerator_hpp

#include <stdio.h>
#include "ofMain.h"

class EnvelopeGenerator{
    
public:
    //Constructor
	//declare the initial attack time, decay time, sustain level and release time
	//unit is milliseconds
    EnvelopeGenerator(float initAttack = 2, float initDecay = 100, float initSustain = 0.6, float initRelease = 300, float SR = 48000){
        attackTime = initAttack;
        decayTime = initDecay;
        sustainLevel = initSustain;
        releaseTime = initRelease;
        sampleRate = SR;
        calculateInc(ATTACK);
        calculateInc(DECAY);
        calculateInc(RELEASE);
        //start with 0.
        currentValue = 0.0;
        
        
        state = OFF;
        gate = 0;
    }
    //process the envelope generator every sample
    void process();
    
	//get the envelope value back
    float getValue(){
		//current amplitude value
        return currentValue;
    }
    
	//gate from 0 to 1 : note on
	//gete from 1 to 0 : note off
	//if we play multiple notes and the envelope is already on
	//we don't need to restart the envelope only for the new one
    void setGate(int newGate){
        int prevGate = gate;
        gate = newGate;
        if(prevGate == 0 && gate == 1){state = ATTACK;}
        if(prevGate == 1 && gate == 0){state = RELEASE;}
    }
    
    
private:
    
    float attackTime, decayTime, sustainLevel, releaseTime;
    double attackInc, decayInc, releaseInc;
    float currentValue;
    int gate;
    double sampleRate;
    //use this variable to keep track which state we are in
    int state;
	//use enumerator to store our states in a readable way
    enum states{
		//off: not in any off the states
        OFF,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE
    };
    
	//calculate increment
    void calculateInc(int whichState){
        switch(whichState){
            case ATTACK:
				//find the incremental value to go from 0 to 1
				//over a certain amount of samples
                attackInc = 1/(sampleRate * (attackTime * 0.001));
                break;
            case DECAY:
				//find the incremental value to go from 1 to sustain level
				//over a certain amount of samples
                decayInc = (1-sustainLevel)/(sampleRate * (decayTime * 0.001));
                break;
            case RELEASE:
				//find the incremental value to go from sustain level to 0
				//over a certain amount of samples
                releaseInc = sustainLevel/(sampleRate * (releaseTime * 0.001));
                break;
        }
    }
    
    
};

#endif /* EnvelopeGenerator_hpp */
