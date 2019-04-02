#pragma once

#include "ofMain.h"

#include "EnvelopeGenerator.hpp"
#include "audioTools.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
        void audioOut(float* buffer, int bufferSize, int nChannels);

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

    //SOUND
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

	void playsound(int i);
	void stopsound();

	string currentWave = "sine";


	//IMAGE
	ofImage img;
	vector<int> rectLoc;
	vector< vector<int> > mArray;
	vector< vector< vector<int> > > tArray;
	vector<ofImage> mImages;

	void drawpic(int n);

	int xs = 0;
	int ys = 0;
	int col_num;

	//for change pics
	int pic = 0;
	int threshold = 230;

	//variables of line
	float lx = 0;
	float speed;

	vector<int> transparency;

	int n = 0;
	
};
