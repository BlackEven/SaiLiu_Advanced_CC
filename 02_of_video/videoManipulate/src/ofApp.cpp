#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//load a video
	bgVideo.load("bgvideo.avi");
	//play the video
	bgVideo.play();
	//pause the loop so we can play frame by frame
	bgVideo.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	//get all the new frames
	bgVideo.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//sets the background color
	ofBackground(0);

	//display the video and resize the video in order to fill it with the screen
	if (bgVideo.isLoaded()) {
		float aspectRatio = bgVideo.getWidth() / bgVideo.getHeight();
		bgVideo.draw(0.0f, 0.0f, ofGetWidth(), ofGetWidth() / aspectRatio);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//set the position of the playhead to a given percentage through the movie according to mouse position
	float mappedPosition = ofMap(float(x), 0.0f, ofGetWidth(), 0.0f, 1.0f);
	bgVideo.setPosition(mappedPosition);


	//another way to do it 
	//int width = ofGetWidth();
	//float pct = (float)x / (float)width;
	//bgVideo.setPosition(pct);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
