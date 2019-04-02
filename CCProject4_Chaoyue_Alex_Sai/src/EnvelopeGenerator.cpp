//reference: https://www.youtube.com/watch?v=ivyr2O0orQg&list=PLNURizt7mHsJ9EasygZJl7M3e-kAOV9Pa&index=14

#include "EnvelopeGenerator.hpp"

//change current amplitude value depending on 
//what part of the envelope we are on
//attack: increase the value to a certain amount
//decay: reduce the value by a certain amount
//sustain: keep the vlaue same
//release: reduce the value to 0.
void EnvelopeGenerator::process(){
    //do something different depending on which state we are in
    switch(state){
        case OFF:
            currentValue = 0.0;
            break;
        case ATTACK:
			//add sttack increment to our current value each sample 
            currentValue += attackInc;
			//if the current value equals 1, move to decay state
            if(currentValue >= 1.0){
                currentValue = 1.0;
                state = DECAY;
            }
            break;
        case DECAY:
			//deduct decay increment each sample
            currentValue -= decayInc;
			//if the current value equals sustain level
			//move to sustain state
            if(currentValue <= sustainLevel){
                currentValue = sustainLevel;
                state = SUSTAIN;
            }
            break;
        case SUSTAIN:
			//keep the current value equal to sustain level
            currentValue = sustainLevel;
            break;
        case RELEASE:
			//deduct release increment each sample
            currentValue -= releaseInc;
			//if the current value equals 0, move to off state
            if(currentValue <= 0.0){
                currentValue = 0.0;
                state = OFF;
            }
            break;
        default:
            cout << "no such state, EG" << endl;
    }
    
    
}
