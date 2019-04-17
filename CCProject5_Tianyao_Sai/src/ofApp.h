#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 8800

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

		//heartshape
		void heartshape();
		glm::vec2 make_point(float theta);
		int distance = 20;
		int scale_num = 20;

		//writename
		void writename();
		ofTrueTypeFont font;
		int font_size;

		//pdf render
		bool pdfRendering;
		int isRender;

		void pdf(int x);

		//osc
		ofxOscReceiver receiver;
};
