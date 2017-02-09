#include "ofApp.h"

string convertInchesToFeetInches(float inches) {
	int feet = (int)inches / 12;
	int inchesOverFeet = (int)inches % 12;
	return (ofToString(feet) + "'" + ofToString(inchesOverFeet) + "''");
}

//--------------------------------------------------------------
void ofApp::setup(){
	player.load("videos/SunriseTest1280x720.mp4");
	player.play();
	player.setLoopState(OF_LOOP_NORMAL);

	ofxNestedFileLoader loader;
	vector<string> imageNames = loader.load("images");
	for (int i = 0; i < imageNames.size(); i++) {
		ofImage img;
		img.load(imageNames[i]);
		imgs.push_back(img);
	}

	gui.setup();
	gui.add(x.set("X", 0.0, 0.0, FOURKWIDTH));
	gui.add(y.set("Y", 0.0, 0.0, FOURKHEIGHT));
	gui.add(width.set("X Resolution", FOURKWIDTH, 0.0, FOURKWIDTH));
	gui.add(height.set("Y Resolution", FOURKHEIGHT, 0.0, FOURKHEIGHT));
	gui.add(diagonal.set("Diagonal ''", 86, 0, 100));
	gui.add(screenWidth.set("Screen Width ''", 0, 0, 100));
	gui.add(screenHeight.set("Screen Height ''", 0, 0, 100));
	gui.add(videoOn.set("VideoOn", false));
	gui.add(imageIndex.set("Image Index", 0, 0, imgs.size()-1));

	flipWindow.load("shaders/flipWindow");




}

//--------------------------------------------------------------
void ofApp::update(){
	if (videoOn) {
		player.update();
	}

	if (x + width > ofGetWidth()) {
		width = ofGetWidth() - x;
	}
	if (y + height > ofGetHeight()) {
		height = ofGetHeight() - y;
	}
	float ratio = height / width;
	screenWidth = sqrt(diagonal*diagonal / (ratio* ratio + 1));
	screenHeight = ratio * screenWidth;
}

//--------------------------------------------------------------
void ofApp::draw(){
	flipWindow.begin();
	flipWindow.setUniform2f("cropPos", x, y);
	flipWindow.setUniform2f("cropResolution", width, height);
	if (videoOn) {
		flipWindow.setUniformTexture("diffuseTexture", player, 0);
		flipWindow.setUniform2f("vidResolution", player.getWidth(), player.getHeight());
	} else {
		flipWindow.setUniformTexture("diffuseTexture", imgs[imageIndex], 0);
		flipWindow.setUniform2f("vidResolution", imgs[imageIndex].getWidth(), imgs[imageIndex].getHeight());
	}
	flipWindow.setUniform2f("windowResolution", ofGetWidth(), ofGetHeight());
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	flipWindow.end();

	gui.draw();

	ofDrawBitmapStringHighlight("Diagonal: " + convertInchesToFeetInches(diagonal), gui.getPosition().x + gui.getWidth() + 10, 20);
	ofDrawBitmapStringHighlight("Width: " + convertInchesToFeetInches(screenWidth), gui.getPosition().x + gui.getWidth() + 10, 40);
	ofDrawBitmapStringHighlight("Height: " + convertInchesToFeetInches(screenHeight), gui.getPosition().x + gui.getWidth() + 10, 60);
	ofDrawBitmapStringHighlight("Resolution X: " + ofToString(ofGetWidth()), gui.getPosition().x + gui.getWidth() + 10, 80);
	ofDrawBitmapStringHighlight("Resolution Y: " + ofToString(ofGetHeight()), gui.getPosition().x + gui.getWidth() + 10, 100);


	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
