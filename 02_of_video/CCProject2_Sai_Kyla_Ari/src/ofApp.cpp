#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//load font
	myFont.load("Font.otf", 24);

	//load images for score
	for (int i = 0; i < 10; i++)
	{
		ofImage tempImage;
		tempImage.load(ofToString(i) + ".png");
		numbers.push_back(tempImage);
	}
	points = 0;

	//load player items
	npc.load(filePath1);
	npc1.load(filePath2);
	npc2.load(filePath5);

	x = ofGetWidth() / 2;
	y = ofGetHeight() - 150;

	//load falling items
	numItems = 3;

	for (int i = 0; i < numItems; i++)
	{
		item tempItem;
		tempItem.setup();
		allItems.push_back(tempItem);
	}

	//load videos
	video.setup("bgVideo.mp4");
	video.play();
	video.setPaused();
	winVideo.setup("victory.mp4");
}

//--------------------------------------------------------------
void ofApp::update() {
	//update falling items
	for (int i = 0; i < numItems; i++)
	{
		allItems[i].update(video);
	}
	collide();

	//get all the new frames
	video.update();
	winVideo.update();
}


void ofApp::collide() {

	//Check for collision for falling objects
	for (int i = 0; i < numItems; i++) {
		float tempX = allItems[i].x;
		float tempY = allItems[i].y;

		// Long conditional for position checking
		if ((x < tempX + 50) && (x > tempX - 50) && (tempY >= y - 90) && (tempY <= y + 100)) {
			ofLog(OF_LOG_NOTICE, "ITEM COLLISION!!!");

			// Reset item to random position at top (looks like is disappears)
			allItems[i].x = ofRandom(75, ofGetWidth() - 75);
			allItems[i].y = -80;
			allItems[i].rotSpeed = ofRandom(1, 3);

			//Add point
			points += 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (level == 0) {
		intro();
	}
	else {
		game();
	}
}

void ofApp::intro() {
	//sets the background color
	ofBackground(203, 203, 203);
	ofSetRectMode(OF_RECTMODE_CENTER);

	//display player items
	ofPushMatrix();
	ofScale(npc1Size, npc1Size, 1);
	npc.draw(ofGetWidth() / 2 - 300, ofGetHeight() / 2, 200, 200);
	ofPopMatrix();

	ofPushMatrix();
	ofScale(npc2Size, npc2Size, 1);
	npc1.draw(ofGetWidth() / 2, ofGetHeight() / 2, 200, 200);
	ofPopMatrix();

	ofPushMatrix();
	ofScale(npc3Size, npc3Size, 1);
	npc2.draw(ofGetWidth() / 2 + 300, ofGetHeight() / 2, 200, 200);
	ofPopMatrix();

	//display intro scripts
	ofPushStyle();
	ofSetColor(0, 0, 0);
	string npc = "1            2           3";
	string selNpc = "Using '1' '2' '3' to chose your player";
	string introScript = "press 'SPACEBAR' to start";
	myFont.drawString(npc, ofGetWidth() / 2 - 330, ofGetHeight() / 2 - 160);
	myFont.drawString(selNpc, ofGetWidth() / 2 - 410, ofGetHeight() - 280);
	myFont.drawString(introScript, ofGetWidth() / 2 - 250, ofGetHeight() - 200);
	ofPopStyle();
}

void ofApp::game() {
	//sets the background color
	ofBackground(0);

	//display background video
	video.display1();

	//display the player choosed in intro level
	ofSetRectMode(OF_RECTMODE_CORNER);
	playerSel.load(filePathPlayer);
	playerSel.draw(x - 75, y - 75, 150, 150);

	//display falling items
	for (int i = 0; i < numItems; i++)
		{
			allItems[i].draw();
		}
	
	//display victory video
	winVideo.display2(points);
	
	//display socres
	drawScore(points);
}

void ofApp::drawScore(int score) {
	if (score < 10) {
		numbers[score].draw(100, 100, 125, 160);
	} if (score >= 10) {
		float firstDig = (score - (score % 10)) / 10;
		int secDig = score % 10;
		numbers[firstDig].draw(100, 100, 125, 160);
		numbers[secDig].draw(225, 100, 125, 160);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case ' ':
		level = 1;
		break;
	case('w'):
		if (y > 0) {
			y -= step;
		}
		break;
	case('s'):
		break;
	case('a'):
		if (x > 0) {
			x -= step;
		}
		break;
	case('d'):
		if (x < ofGetWidth() - 1) {
			x += step;
		}
		break;
	case('1'):
		filePathPlayer = filePath1;
		npc1Size = 1.1;
		npc2Size = 1;
		npc3Size = 1;
		break;
	case('2'):
		filePathPlayer = filePath2;
		npc1Size = 1;
		npc2Size = 1.1;
		npc3Size = 1;
		break;
	case('3'):
		filePathPlayer = filePath5;
		npc1Size = 1;
		npc2Size = 1;
		npc3Size = 1.1;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case('w'):
		if (y > 0) {
			y = ofGetHeight() - 150;

		}
		break;

	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}