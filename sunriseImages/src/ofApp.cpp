#include "ofApp.h"

//--------------------------------------------------------------
bool compareImagePaths(string p1, string p2) {
    vector<string> file = ofSplitString(p1, "/");
    vector<string> date = ofSplitString(file[1], ".");
    vector<string> dateSplit = ofSplitString(date[0], "-");
    float yea1 = ofToFloat(dateSplit[0]);
    float mon1 = ofToFloat(dateSplit[1]);
    float day1 = ofToFloat(dateSplit[2]);
    float hou1 = ofToFloat(dateSplit[3]);
    float min1 = ofToFloat(dateSplit[4]);
    float sec1 = ofToFloat(dateSplit[5]);

    file = ofSplitString(p1, "/");
    date = ofSplitString(file[1], ".");
    dateSplit = ofSplitString(date[0], "-");
    float yea2 = ofToFloat(dateSplit[0]);
    float mon2 = ofToFloat(dateSplit[1]);
    float day2 = ofToFloat(dateSplit[2]);
    float hou2 = ofToFloat(dateSplit[3]);
    float min2 = ofToFloat(dateSplit[4]);
    float sec2 = ofToFloat(dateSplit[5]);

    if(yea1 == yea1) {
        if(mon1 == mon2) {
            if(day1 == day2) {
                if(hou1 == hou2) {
                    if(min1 == min2) {
                        return sec1 < sec2;
                    } else {
                        return min1 < min2;
                    }
                } else {
                    return hou1 < hou2;
                }
            } else {
                return day1 < day2;
            }
        } else {
            return mon1 < mon2;
        }
    } else {
        return yea1 < yea2;
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    //organizeImages("Images"); Already done!
    ofxNestedFileLoader loader;
    imgPaths = loader.load("Brooklyn");
    cout<<"Total Images: " <<imgPaths.size()<<endl;
    sort(imgPaths.begin(), imgPaths.end(),compareImagePaths);
    y = x = 0;
//    ofSetBackgroundAuto(false);
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Settings", settingsPath);
    gui.add(middleLeft.set("MidPoint Left", 6900, 0, 15360/2));
    gui.add(middleRight.set("MidPoint Right", 6900, 15360/2, 15360));

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    img.load(imgPaths[index]);
    cout<<"Loading Image "<<index<<endl;
    int width = 15360;
    int height = 1920;
    float scale = 4;
    
    float outX1 = 0;
    float outY1 = 0;
    float outWidth1 = middleLeft / scale;
    float outHeight1 = 1920 / scale;
    
    float inX1 = 160;
    float inY1 = 0;
    float inWidth1 = middleLeft-160;
    float inHeight1 = 1920;
    
    float inX2 = middleRight;
    float inY2 = 0;
    float inWidth2 = middleRight-160;
    float inHeight2 = 1920;
    
    float outX2 = outWidth1;
    float outY2 = 0;
    float outWidth2 = inWidth2 / scale;
    float outHeight2 = 1920 / scale;
    

    
    img.drawSubsection(outX1, outY1, outWidth1, outHeight1, inX1, inY1, inWidth1, inHeight1);
    img.drawSubsection(outX2, outY2, outWidth2, outHeight2, inX2, inY2, inWidth2, inHeight2);

    //img.draw(0, 0, width / scale, height / scale);
    index++;
    if(index == imgPaths.size()) {
        index = 0;
    }
    
    gui.draw();
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
