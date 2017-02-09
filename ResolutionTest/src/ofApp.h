#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNestedFileLoader.h"

#define FOURKWIDTH 3840
#define FOURKHEIGHT 2160


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVideoPlayer player;

		ofShader flipWindow;

		ofxPanel gui;

		ofParameter<float> x;
		ofParameter<float> y;
		ofParameter<float> width;
		ofParameter<float> height;
		ofParameter<float> diagonal;
		ofParameter<float> screenWidth;
		ofParameter<float> screenHeight;
		ofParameter<bool> videoOn;
		ofParameter<int> imageIndex;

		vector<ofImage> imgs;
};
