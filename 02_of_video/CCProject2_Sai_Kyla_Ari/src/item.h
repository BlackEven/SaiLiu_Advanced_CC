#ifndef _ITEM
#define _ITEM

#include "ofMain.h"
#include "VideoClass.h"

class item {
public:
	void setup();
	void update(VideoClass video);
	void draw();

	float x;
	float y;
	float speedY;
	ofImage fish1;
	string filePath = "fish1.png";
	int f = 0;
	int rotSpeed = ofRandom(1, 3);

	item();

};

#endif