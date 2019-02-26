#pragma once

#include "ofMain.h"
class VideoClass{
public:
	void setup(string filepath);
	void play();
	void update();
	void display1();
	void display2(int points);
	void setPosition(float x);
	void setPaused();
	//Add instance variables of type ofVideoPlayer
	ofVideoPlayer video;

};

