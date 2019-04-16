#include "ofApp.h"
//reference:
//https://junkiyoshi.com/openframeworks20181102/
//https://www.youtube.com/watch?v=BfRXzMDspFI

//--------------------------------------------------------------
void ofApp::setup() {
	//set framerate
	ofSetFrameRate(60);

	//setup osc receiver
	receiver.setup(PORT);

	//set background and line width
	ofNoFill();
	ofBackground(0);
	ofSetLineWidth(3);

	//set font
	font_size = 72;
	font.loadFont("SF-Pro-Display-Regular.otf", font_size, true, true, true);

	//set pdf render
	pdfRendering = false;
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		if (receiver.getNextMessage(m)) {
			if (m.getAddress() == "/1/fader5") {
				float x = m.getArgAsFloat(0);
				//ofLogNotice() << "m" << m;
				distance = ofMap(x, 0., 1., 0, 20, true);
				//ofLogNotice() << "distance " << distance << endl;
				scale_num = ofMap(x, 0., 1., 0, 20, true);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	heartshape();
	writename();
}

void ofApp::heartshape() {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	//draw several heart shapes
	for (auto scale = 1; scale < scale_num; scale += 1) {

		vector<glm::vec2> vertices;
		//calculate the position of the circle of each heart shape
		auto param = (ofGetFrameNum() * 2 + scale * distance) % 720;
		
		//set color - red to white
		ofColor color;
		color.set(ofMap(param, 0, 360, 255, 219), ofMap(param, 0, 360, 255, 24), ofMap(param, 0, 360, 255, 24));
		ofSetColor(color);

		//debug
		//ofLogNotice() << "framenum " << ofGetFrameNum() << endl;
		//ofLogNotice() << "param " << param;

		for (auto deg = 0; deg < 360; deg += 1) {
			//draw a heart shape
			//and the circle is at the front end of the line
			if (param < 360) {
				if (deg < param) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
			else {
				//erase a heart shape
				//the circle is at the back end of the line
				if (deg > param - 360) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
			//draw a circle 
			if (deg == param % 360) {
				ofFill();
				ofDrawCircle(this->make_point(deg * DEG_TO_RAD) * scale, 3);
			}
		}

		//use vertices to draw shapes
		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();
	}
	ofPopMatrix();
}

//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {
	//get the x and y value of the points in a heart shape
	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);

}


void ofApp::writename() {
	//get system time
	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);
	int second = sys_time.wSecond;

	//set the sample count for drawing the shape of character
	int sample_count = 100;
	//calculate the step to draw the character
	int step = ofMap(sys_time.wMilliseconds, 0, 1000, 0, sample_count/2);
	//the character shape won't close until it finished
	bool close = false;

	//set the word to be drawn
	string word = "Sai & Tianyao";
	char charactors[13];
	word.copy(charactors, 13);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 - font_size * 6, ofGetHeight() / 2 + font_size * 6);

	for (int charactor_index = 0; charactor_index < 13; charactor_index++) {
		//get charactors as paths (no fill)
		ofPath path = font.getCharacterAsPoints(charactors[charactor_index], true, false);
		// for every character break it out to polylines
		vector<ofPolyline> outline = path.getOutline();
		// for every polyline, draw every point
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {
			//resamples the line based on the spacing passed in
			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			//Gets a vector of vertices that the line contains
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			ofPushStyle();
			ofSetColor(239);
			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {
				ofVec2f point(vertices[vertices_index].x, vertices[vertices_index].y);
				close = false;

				//redraw the shape every 3 seconds
				if (second % 3 != 0) {
					ofVertex(point);
					close = true;
				}
				else {
					if (step < sample_count) {
						//draw characters without closing the shape
						if (vertices_index / 2 < step % sample_count) {
							ofVertex(point);
						}
						//draw a circle at the end of the line
						if (vertices_index / 2 == step % sample_count) {
							ofDrawCircle(point, 3);
						}
					}
					else {
						ofVertex(point);
						close = true;
					}
				}
			}
			ofEndShape(close);
			ofPopStyle();
		}
		ofTranslate(font_size, 0);
	}
	ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		pdfRendering = !pdfRendering;
		if (pdfRendering) {
			ofSetFrameRate(12);  // so it doesn't generate tons of pages
			ofBeginSaveScreenAsPDF("recording-" + ofGetTimestampString() + ".pdf", true);
		}
		else {
			ofSetFrameRate(60);
			ofEndSaveScreenAsPDF();
		}
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
