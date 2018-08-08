#pragma once

#include "ofMain.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"

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
        void organizeImages(string root);
        void renameImages(vector<string> paths);

        ofxPanel gui;
        ofParameter<float> middleLeft, middleRight;
        vector<string> imgPaths;
        ofFbo buffer;
        ofImage img;
        ofImage screen;
        bool takeShots;
        int x, y, index;
		
};
