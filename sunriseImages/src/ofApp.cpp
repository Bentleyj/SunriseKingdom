#include "ofApp.h"

//--------------------------------------------------------------
bool compareImagePaths(string p1, string p2) {
    vector<string> s1 = ofSplitString(p1, "/");
    vector<string> s2 = ofSplitString(p2, "/");
    int year1 = ofToInt(s1[1]);
    int year2 = ofToInt(s2[1]);
    int month1 = ofToInt(s1[2]);
    int month2 = ofToInt(s2[2]);
    vector<string> s12 = ofSplitString(s1[4], "-");
    vector<string> s22 = ofSplitString(s2[4], "-");
    int day1 = ofToInt(s12[0]);
    int day2 = ofToInt(s22[0]);
    vector<string> s13 = ofSplitString(s12[1], ".");
    vector<string> s23 = ofSplitString(s22[1], ".");
    int frame1 = ofToInt(s13[0]);
    int frame2 = ofToInt(s23[0]);
    
    if(year1 == year2) {
        if(month1 == month2) {
            if(day1 == day2) {
                return frame1 < frame2;
            } else {
                return (day1 < day2);
            }
        } else {
            return (month1 < month2);
        }
    } else {
        return (year1 < year2);
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    //organizeImages("Images"); Already done!
    ofxNestedFileLoader loader;
    imgPaths = loader.load("Large");
    cout<<"Total Images: " <<imgPaths.size()<<endl;
    sort(imgPaths.begin(), imgPaths.end(),compareImagePaths);
//    renameImages(imgPaths);
    y = x = 0;
    ofSetBackgroundAuto(false);
}



//--------------------------------------------------------------
void ofApp::renameImages(vector<string> paths) {
    for(int i = 0; i < paths.size(); i++) {
        ofFile f = ofFile(imgPaths[i], ofFile::ReadOnly);
        string n = f.getFileName();
        vector<string> s = ofSplitString(n, "-");
        if(s.size() < 2) {
            string newN = f.getEnclosingDirectory() + "New/" + "0-" + s[0];
            cout<<newN<<endl;
            f.renameTo(newN, true, true);
        } else {
            vector<string> s2 = ofSplitString(s[1], ".");
            string newN = f.getEnclosingDirectory() + "New/" + s2[0] + "-" + s[0] + ".jpg";
            cout<<newN<<endl;
            f.renameTo(newN, true, true);
        }
    }
}


//--------------------------------------------------------------
void ofApp::organizeImages(string root) {
    ofxNestedFileLoader loader;
    cout<<"Loading all image paths"<<endl;
    vector<string> imgPaths = loader.load(root);
    cout<<"Image Paths Loaded"<<endl;
    for(int i = 0; i < imgPaths.size(); i++) {
        ofFile f = ofFile(imgPaths[i], ofFile::ReadOnly);
        string n = f.getFileName();
        if(n.find("768x") != string::npos) {
            string encDir = f.getEnclosingDirectory();
            int p = encDir.find("Images/");
            string newPos = encDir.substr(0, p) + "Small/" + encDir.substr(p) + n;
            cout<<newPos<<endl;
            f.moveTo(newPos);
        } else if(n.find("1920x") != string::npos) {
            string encDir = f.getEnclosingDirectory();
            int p = encDir.find("Images/");
            string newPos = encDir.substr(0, p) + "Medium/" + encDir.substr(p) + n;
            cout<<newPos<<endl;
            f.moveTo(newPos);
        } else {
            string encDir = f.getEnclosingDirectory();
            int p = encDir.find("Images/");
            string newPos = encDir.substr(0, p) + "Large/" + encDir.substr(p) + n;
            cout<<newPos<<endl;
            f.moveTo(newPos);
        }
    }
    cout<<"Done!"<<endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    img.load(imgPaths[index]);
    cout<<"Loading Image "<<index<<endl;
    int width = 3840;
    int height = 600;
    float scale = 1;
    img.draw(0, 0, width / scale, height / scale);
    index++;
    if(index == imgPaths.size()) {
        index = 0;
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
