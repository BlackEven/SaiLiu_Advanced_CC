#include "item.h"


item::item() {

}

void item::setup() {
	fish1.load(filePath);
	x = ofRandom(75, ofGetWidth() - 75);
	y = 0;

	speedY = ofRandom(3, 8);
}

void item::update(VideoClass video) {
	if (y > ofGetHeight() + 50) {
		y = -50;
		x = ofRandom(75, ofGetWidth() - 75);
		//the position of video is adjusted by the x position of new falling items
		float mappedPosition = ofMap(x, 0.0f, ofGetWidth(), 0.0f, 1.0f);
		video.setPosition(mappedPosition);
		speedY = ofRandom(3, 8);
	}

	y += speedY;
}

void item::draw() {
	f += rotSpeed;

	ofPushMatrix();
	ofTranslate(x, y, 0);
	fish1.setAnchorPercent(0.5, 0.5);
	ofRotateDeg(f);
	fish1.draw(0, 0, 150, 100);
	ofPopMatrix();
	

}