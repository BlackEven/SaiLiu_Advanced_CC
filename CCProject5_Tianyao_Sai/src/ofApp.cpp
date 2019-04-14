#include "ofApp.h"
//reference:
//https://junkiyoshi.com/openframeworks20181102/
//https://www.youtube.com/watch?v=BfRXzMDspFI

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	ofNoFill();
	ofBackground(0);
	ofSetLineWidth(1);

	font_size = 72;
	font.loadFont("SF-Pro-Display-Regular.otf", font_size, true, true, true);

	pdfRendering = false;
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	heartshape();
	writename();
}

void ofApp::heartshape() {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (auto scale = 1; scale < 20; scale += 1) {

		vector<glm::vec2> vertices;
		auto param = (ofGetFrameNum() * 2 + scale * 20) % 720;
		ofColor color;
		color.set(ofMap(param, 0, 360, 255, 219), ofMap(param, 0, 360, 255, 24), ofMap(param, 0, 360, 255, 24));
		ofSetColor(color);

		ofLogNotice() << param;

		for (auto deg = 0; deg < 360; deg += 1) {
			if (param < 360) {
				if (deg < param) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
			else {
				if (deg > param - 360) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
			//draw a circle at the end of the line
			if (deg == param % 360) {
				ofFill();
				ofDrawCircle(this->make_point(deg * DEG_TO_RAD) * scale, 3);
			}
		}

		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();
	}
	ofPopMatrix();
}

//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);

}


void ofApp::writename() {
	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);

	int second = sys_time.wSecond;
	int sample_count = 100;
	int step = ofMap(sys_time.wMilliseconds, 0, 1000, 0, sample_count/2);
	bool close = false;

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
