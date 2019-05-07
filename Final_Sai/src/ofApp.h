#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Particle.h"
#include "EnvelopeGenerator.hpp"
#include "audioTools.h"
#include "ofxCvHaarFinder.h"

#define PORT 9000
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		//1-OSC
		//create an osc receiver
		ofxOscReceiver receiver;
		//create an empty vector of keys
		vector<int> keys;


		//2-KeySound
		bool change = false;
		//2.1Piano
		vector<ofSoundPlayer> key_sounds;

		//2.2Generate notes
		//make a new envelope
		EnvelopeGenerator* envelope;
		//control the frequency with a smooth value
		smoothValue frequency;
		//make a oscillator
		oscillator osc;
		//convert MIDI noete number to frequency
		float mtof(float midiVal) {
			//return expr 440*(pow (2, (($f1-69)/12)))
			return 440 * pow(2, (midiVal - 69) / 12.f);
		}
		void audioOut(float* buffer, int bufferSize, int nChannels);
		void playsound(int i);
		void stopsound();
		
		string currentWave = "sine";

		//3-Particles
		vector <Particle> particles;
		ofImage img1;
		ofImage img2;
		void keyeffect(int i);
		float centerx;
		float centery;
		float loc = -100;
		float locy = -100;
		float counter;

		//4-HeadTracker
		ofVideoGrabber video;
		ofxCvHaarFinder finder;
		ofRectangle cur;
};
