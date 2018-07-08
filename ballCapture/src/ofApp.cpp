#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    mPrevDetectedStatus = false;
    
    ofSetVerticalSync(true);

    mBallCapture.setup();
    
    // setup GUI
    mNearThreshold.addListener(this, &ofApp::nearThresholdChanged);
    mFarThreshold.addListener(this, &ofApp::farThresholdChanged);

    mGui.setup(); // most of the time you don't need a name
    mGui.add(mNearThreshold.setup("near threshold", 237, 3, 255));
    mGui.add(mFarThreshold.setup("far threshold", 213, 3, 255));
    
    // 音のロード
    mRing.load("sound/ring.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
    mBallCapture.update();
    
    if(mBallCapture.getDetectedNumBalls()>0 && mPrevDetectedStatus == false)
    {
        mRing.play();
        mPrevDetectedStatus = true;
    }else{
        mPrevDetectedStatus = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    mBallCapture.draw();
    
    mGui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    mNearThreshold.removeListener(this, &ofApp::nearThresholdChanged);
    mFarThreshold.removeListener(this, &ofApp::farThresholdChanged);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    mBallCapture.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::nearThresholdChanged(int &val){
    mBallCapture.setNearThreshold(val);
}

//--------------------------------------------------------------
void ofApp::farThresholdChanged(int &val){
    mBallCapture.setFarThreshold(val);
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
