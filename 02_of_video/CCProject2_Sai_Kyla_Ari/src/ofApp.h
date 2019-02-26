#pragma once

#include "ofMain.h"
#include <string>
#include "item.h"
#include "VideoClass.h"

class ofApp : public ofBaseApp {

public:
	//game levels
	int level = 0;

	//Score display
	vector <ofImage> numbers;
	ofImage one, two, three, four, five, six, seven, eight, nine, zero;
	int points = 0;

	//Falling items variables
	item myItem;
	vector <item> allItems;
	int numItems;

	//player item variables
	ofImage npc;
	ofImage npc1;
	ofImage npc2;
	ofImage playerSel;

	int x, y;
	int step = 20;

	float npc1Size = 1.1;
	float npc2Size = 1;
	float npc3Size = 1;

	string filePath1 = "player_1.png";
	string filePath2 = "player_2.png";
	string filePath5 = "player_5.png";
	string filePathPlayer = "player_1.png";

	//video variables
	VideoClass video;
	VideoClass winVideo;

	//font variable
	ofTrueTypeFont myFont;

	//functions
	void setup();
	void update();
	void draw();
	void intro();
	void game();
	void collide();
	void drawScore(int score);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	
};
