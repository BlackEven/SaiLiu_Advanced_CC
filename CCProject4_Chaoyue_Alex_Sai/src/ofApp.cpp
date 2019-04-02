#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//Framerate
	ofSetFrameRate(60);

	//SOUND
	//set up oscillator: 440 frequency, 0 phase, 1.0 amplitude
	//48000 sample rate
    osc.setup(440, 0, 1.0, 48000);
    //set up an envelope with default value
    envelope = new EnvelopeGenerator();
    //set up the frequency
    frequency.currentValue = frequency.targetValue = 440;
	//smooth the frequency to remove unwanted clicks
    frequency.smoother = new parameterSmoother(100, 48000);
    //set up sound stream: 2 output channels, 0 input channel, 
	//48000 sample rate, 512 buffersize, 4 buffers
    ofSoundStreamSetup(2, 0, 48000, 512, 4);

	//IMAGE
	 //load image file
	mImages.resize(3);
	mImages[0].load("ghostchair.jpeg");
	mImages[1].load("trump.jpg");
	mImages[2].load("bradpitt.jpg");
	
	// resize the canvas according to the image
	ofSetWindowShape(mImages[1].getWidth(), mImages[1].getHeight());

	for (int i = 0; i < mImages.size(); i++) {
		//getting the image's pixels
		ofPixels &pixels = mImages[i].getPixels();

		//define variables w,h equal to frame width and height
		int w = pixels.getWidth();
		int h = pixels.getHeight();
		int step = 20;

		for (int x = 0; x < w; x = x + step) {
			for (int y = 0; y < h; y = y + step) {
				ofColor color = pixels.getColor(x, y);
				float saturation = color.getSaturation();
				if (saturation > threshold) {
					int pos = xs + w / 20 * ys;
					rectLoc.push_back(ys);
				}
				ys++;
			}
			mArray.push_back(rectLoc);

			rectLoc.clear();
			ys = 0;
			xs++;

		}
		tArray.push_back(mArray);
		mArray.clear();
	}

	col_num = tArray[0].size();
	ofLogNotice() << col_num << endl;
	transparency.resize(col_num);


	for (int i = 0; i < transparency.size(); i++) {
		transparency[i] = 255;
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw the image
	drawpic(pic);
}

void ofApp::drawpic(int n) {
	//draw the image
	mImages[n].draw(0, 0);

	//getting the video's pixels
	ofPixels &pixels = mImages[n].getPixels();

	//define variables w,h equal to frame width and height
	int w = pixels.getWidth();
	int h = pixels.getHeight();

	//define rectangles' variables
	int step = 20;
	int l = 20;


	//draw rectangles
	for (int x = 0; x < w; x = x + step) {
		for (int y = 0; y < h; y = y + step) {
			ofColor color = pixels.getColor(x, y);
			ofSetColor(color);
			ofDrawRectangle(x, y, l, l);

		}
	}

	//draw the moving line

	ofSetColor(255, 255, 255);
	ofSetLineWidth(2);
	ofDrawLine(lx, 0, lx, h);
	lx = lx + speed;
	if (lx > w) {
		lx = 0;
		for (int i = 0; i < col_num; i++) {
			transparency[i] = 255;
		}

	}

	//line
	for (int j = 0; j < tArray[n].size(); j++) {

		if (lx >= j * l && lx <= (j + 1)*l) {
			for (int i = 0; i < tArray[n][j].size(); i++) {
				if (lx <= j * l + 10) {
					playsound(tArray[n][j][i]);
				}
				else {
					stopsound();
				}
				ofSetColor(255, 255, 255, transparency[j]);
				ofDrawRectangle(l*j, tArray[n][j][i] * l, l, l);

			}
			transparency[j] = transparency[j] - 1;

		}
	}
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        float currentSample = osc.getSample(currentWave);
        //process envelope every sample
        envelope->process();
		//smooth the frequency and set the oscillator with current frequency
        frequency.currentValue = frequency.smoother->process(frequency.targetValue);
        osc.setFrequency(frequency.currentValue);
        
        //currentSample *= current amplitude value
        currentSample *= envelope->getValue();
		//writing to the left channel
        buffer[i*nChannels+0] = currentSample;
		//writing to the right channel
        buffer[i*nChannels+1] = currentSample;
    }
}

void ofApp::playsound(int i) {
	//map the y value of selected pixel to midi note 
	int note = ofMap(i, 0, 28, 72, 60);
	//ofLog() << "the note is " << ofToString(note);
	//use this note to set target value for frequency
	frequency.targetValue = mtof(note);
	//turns th envelope on
	envelope->setGate(1);
}

void ofApp::stopsound() {
	//turns the envelope off
	envelope->setGate(0);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case 'a':
            frequency.targetValue = mtof(60);
            envelope->setGate(1);
            break;
        case 's':
            frequency.targetValue = mtof(62);
            envelope->setGate(1);
            break;
        case 'd':
            frequency.targetValue = mtof(64);
            envelope->setGate(1);
            break;
        case 'f':
            frequency.targetValue = mtof(65);
            envelope->setGate(1);
            break;
        case 'g':
            frequency.targetValue = mtof(67);
            envelope->setGate(1);
            break;
        case 'h':
            frequency.targetValue = mtof(69);
            envelope->setGate(1);
            break;
        case 'j':
            frequency.targetValue = mtof(71);
            envelope->setGate(1);
            break;
        case 'k':
            frequency.targetValue = mtof(72);
            envelope->setGate(1);
            break;

		//change sound wave
		case 'z':
			currentWave = "sine";
			break;
		case 'x':
			currentWave = "tri";
			break;
		case 'c':
			currentWave = "saw";
			break;
		case 'v':
			currentWave = "square";
			break;

		//change pic
		case '1':
			pic = 0;
			break;
		case '2':
			pic = 1;
			break;
		case '3':
			pic = 2;
			break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch(key){
        case 'a':
            envelope->setGate(0);
            break;
        case 's':
            envelope->setGate(0);
            break;
        case 'd':
            envelope->setGate(0);
            break;
        case 'f':
            envelope->setGate(0);
            break;
        case 'g':
            envelope->setGate(0);
            break;
        case 'h':
            envelope->setGate(0);
            break;
        case 'j':
            envelope->setGate(0);
            break;
        case 'k':
            envelope->setGate(0);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//change the speed of line
	speed = ofMap(float(x), 0.0f, ofGetWidth(), 0, 2.0f);
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
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}
