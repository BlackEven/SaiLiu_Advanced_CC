#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
		vidGrabber.setup(640,360);
	#else
        vidPlayer.load("earth_venus_tango.mp4");
        vidPlayer.play();
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
	#endif

	colorImg.allocate(640, 360);
	grayImage.allocate(640, 360);
	grayBg.allocate(640, 360);
	grayDiff.allocate(640, 360);
	bLearnBakground = true;
	threshold = 90;

	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update(){
	//ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels());
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels());
        #endif

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (640*360)/3, 10, true);	// find holes
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//display the source video if we don't press 'v'
	if (bShowVideo) {
		colorImg.draw(0, 0);
	}

	//display multiple patterns formed by lines or circles
	float width = 640;
	float height = 360;
	for (int j = 0; j < ofGetWindowWidth(); j += width) {
	for (int i = 0; i < ofGetWindowHeight(); i += height) {
		//use the position of mouse to change the color of lines/circles
		int r = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
		int g = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 255);
		int b = ofMap(ofGetMouseX(), 0, ofGetWidth(), 255, 0);
		if (showLine) {
			drawLines(j, i, r, g, b);
		};
		if (showCircle) {
			drawCenterPoint(j, i, 3, r, g, b);
		};
	}
	}
}

void ofApp::drawLines(float x, float y, int r, int g, int b) {
	ofEnableAlphaBlending();
	ofSetColor(r,g,b,80);
	//draw a line between two planets
	for (int i = contourFinder.nBlobs - 1; i > 0; i--) {
		if (i > 1) {
			ofDrawLine(x + contourFinder.blobs[i].boundingRect.x + contourFinder.blobs[i].boundingRect.width / 2,
				y + contourFinder.blobs[i].boundingRect.y + contourFinder.blobs[i].boundingRect.height / 2,
				x + contourFinder.blobs[i - 1].boundingRect.x + contourFinder.blobs[i - 1].boundingRect.width / 2,
				y + contourFinder.blobs[i - 1].boundingRect.y + contourFinder.blobs[i - 1].boundingRect.height / 2);
		};
	};
	ofDisableAlphaBlending();
}

void ofApp::drawCenterPoint(float x, float y, float w, int r, int g, int b) {
	ofEnableAlphaBlending();
	ofSetColor(r, g, b, 127);
	//draw a circle at the midpoint of the line connecting the two planets
	for (int i = contourFinder.nBlobs - 1; i > 0; i--) {
		if (i > 1) {
			float centerx = ((contourFinder.blobs[i - 1].boundingRect.x + contourFinder.blobs[i - 1].boundingRect.width / 2) +
				(contourFinder.blobs[i].boundingRect.x + contourFinder.blobs[i].boundingRect.width / 2)) / 2  ;
			float centery = ((contourFinder.blobs[i - 1].boundingRect.y + contourFinder.blobs[i - 1].boundingRect.height / 2) +
				( contourFinder.blobs[i].boundingRect.y + contourFinder.blobs[i].boundingRect.height / 2)) / 2 ;
			ofDrawCircle(centerx + x, centery + y, w);
		};
	};
	ofDisableAlphaBlending();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 'v':
			ofBackground(0,0,0);
			bShowVideo = !bShowVideo;
			break;
		case 'l':
			showLine = !showLine;
			break;
		case 'c':
			showCircle = !showCircle;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
