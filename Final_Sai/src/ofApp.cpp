#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//1-OSC
	//set up osc
	receiver.setup(PORT);
	//add 12 keys all with value of 0
	keys.assign(12, 0);

	//2-KeySound
	//2.1Piano
	//create 12 sound objects
	for (int i = 0; i < keys.size(); i++) {
		ofSoundPlayer key_sound_i;
		key_sounds.push_back(key_sound_i);
	}
	//Load the 12 sound objects
	for (int i = 0; i < keys.size(); i++) {
		key_sounds[i].load("keysound/" + ofToString(i+1) + ".mp3");
		key_sounds[i].setMultiPlay(true);
	}

	//2.2Generate notes
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

	//3-Particles
	//init screen
	ofBackground(0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	img1.loadImage("particle32.png");
	img2.loadImage("dot1.png");
	//4 - HeadTracker
	video.setup(320, 240);
	finder.setup("haarcascade_frontalface_default.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

	//1-OSC
	//detect which key is pressed
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		if (receiver.getNextMessage(m)) {
			for (int i = 0; i < keys.size(); i++) {
				string adr = "/1/push" + ofToString(i+1);
				//ofLogNotice() << adr << endl;
				if (m.getAddress() == adr) {
					auto y = m.getArgAsInt(0);
					keys[i] = y;
					ofLogNotice() << "key" << i << " " << y << endl;
					if (y == 1) {
						if (change) {
							//2.1Piano
							key_sounds[i].play();
						}
						else {
							//2.2Generate notes
							playsound(i);
						}
						keyeffect(i);
						counter = 0;
					}
					else if (y == 0) {
						stopsound();
					}
				}
			}
		}
	}

	//3-Particles
	//key visulization-line width change
	//update event slowly increments the counter variable
	counter = counter + 0.033f;
	if (counter >= ofDegToRad(90)) {
		counter = ofDegToRad(90);
	}

	//update partciles
	for (int i = 0; i < particles.size(); i++) {
		particles[i].resetForce();
		particles[i].addDampingForce();
		particles[i].update();
	}
	//delete partciles
	auto ms = ofGetElapsedTimeMillis();
	if (particles.size() > 10) {
		if (ms % 20 == 0) {
			//ofLogNotice() << "delete";
			particles.erase(particles.begin());
		}
	}else if (particles.size() < 10 && particles.size() > 0) {
		if (ms % 80 == 0) {
			//ofLogNotice() << "delete2";
			//particles.pop_back();
			particles.erase(particles.begin());
		}
	}

	//4-HeadTracker
	video.update();
	finder.findHaarObjects(video.getPixels());
	for (unsigned int i = 0; i < finder.blobs.size(); i++) {
		cur = finder.blobs[i].boundingRect;
		//ofLogNotice() << "cur" << cur.x << " "<<cur.y;
		centerx = ofMap(cur.x, 200, 0, ofGetWidth() / 4, 3 * ofGetWidth()/4);
		centery = ofMap(cur.y, 50, 90, ofGetHeight() / 4, 3 * ofGetHeight() / 4);
		//ofLogNotice() << "center" << centerx << " " << centery;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	//3-Particles
	//draw particle
	ofPushStyle();
	
	for (int i = 0; i < particles.size(); i++) {
		float posx = particles[i].pos.x - 16;
		float posy = particles[i].pos.y - 16;
		float posz = particles[i].pos.z;
		loc = posx + centerx * 0.2;
		locy = posy - centery * 0.3 + 100;
		if (change) {
			ofSetColor(255,ofRandom(255),255);
			img2.draw(loc, locy, posz);
		}
		else {
			ofSetColor(255, 255, 255);
			img1.draw(loc, posy, posz);
		}
	}
	ofPopStyle();

	//draw lines
	ofPushStyle();
	if (change) {
		ofSetLineWidth(1);
		ofSetColor(255, 100, 255);
		ofDrawLine(loc + ofGetWidth() / 48, 0, loc + ofGetWidth() / 48, ofGetHeight());
	}
	else {
		ofSetLineWidth(2);
		ofSetColor(71, 136, 179);
		ofDrawLine(0, 4 * ofGetHeight() / 5, ofGetWidth(), 4 * ofGetHeight() / 5);
	}
	ofPopStyle();
	
	//draw key visualization
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_DISABLED);
	if (change) {
		ofSetColor(255, 100, 255);
		ofDrawCircle(loc+ofGetWidth() / 48, locy, 10 * cos(counter));
	}
	else {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(10 * cos(counter));
		ofDrawLine(loc, 4 * ofGetHeight() / 5, loc + ofGetWidth() / 24, 4 * ofGetHeight() / 5);
	}
	ofPopStyle();
}
void ofApp::keyeffect(int i) {
	//3-Particles
	//set new particles in random location to generate special effect
	for (int j = 0; j < 4; j++) {
		Particle myParticle;
		float vx = ofRandom(-1, 1);
		float vy = ofRandom(-8, 0);
		float vz = ofRandom(3, 10);
		myParticle.setInitialCondition(
			i * ofGetWidth() / 24 + ofGetWidth() / 4,
			4 * ofGetHeight() / 5, 0, vx, vy, vz);
		particles.push_back(myParticle);
	}
}

void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {

		float currentSample = osc.getSample(currentWave);
		//process envelope every sample
		envelope->process();
		//smooth the frequency and set the oscillator with current frequency
		frequency.currentValue = frequency.smoother->process(frequency.targetValue);
		osc.setFrequency(frequency.currentValue);

		//currentSample *= current amplitude value
		currentSample *= envelope->getValue();
		//writing to the left channel
		buffer[i*nChannels + 0] = currentSample;
		//writing to the right channel
		buffer[i*nChannels + 1] = currentSample;
	}
}

void ofApp::playsound(int i) {
	//use this note to set target value for frequency
	frequency.targetValue = mtof(60+i);
	//turns th envelope on
	envelope->setGate(1);
}

void ofApp::stopsound() {
	//turns the envelope off
	envelope->setGate(0);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//3-Particles
	//clear all of the particles
	if (key == 'd') {
		particles.clear();
		change = !change;
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
