#include "VideoClass.h"



void VideoClass::setup(string filepath){
	//load videos
	video.load(filepath);
}
void VideoClass::setPaused() {
	//pause the loop so we can play frame by frame
	video.setPaused(true);
}
void VideoClass::play() {
	//play videos
	video.play();
}
void VideoClass::update() {
	//get all the new frames
	video.update();
}

void VideoClass::setPosition(float x) {
	//sets the position of the playhead to a given percentage through the movie
	video.setPosition(x);
}
void VideoClass::display1() {
	//display the video and resize the video in order to fill it with the screen
	if (video.isLoaded()) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		float aspectRatio = video.getWidth() / video.getHeight();
		video.draw(0.0f, 0.0f, ofGetWidth(), ofGetWidth() / aspectRatio);
	}	
}

void VideoClass::display2(int points) {
	//display and zoom in the video when the player wins 
	if (video.isLoaded()) {
		if (points == 9) {
			ofResetElapsedTimeCounter();
		}
		//isolate our translation matrix
		ofPushMatrix();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		//scale the video as time goes by
		if ((ofGetElapsedTimeMillis() *0.002) < 2) {
			ofScale(ofGetElapsedTimeMillis() *0.002, ofGetElapsedTimeMillis() *0.002, 1);
		}
		else {
			ofScale(2, 2, 1);
			//Rotate the video as time goes by
			ofRotateYDeg(ofGetElapsedTimeMillis() *0.125);

		}
		video.draw(0, 0, 480, 274);

		if (points >= 9) {
			video.play();
		}
		ofPopMatrix();
	}
}