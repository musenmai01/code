#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);

    mBallCapture.setup();
    
    // open an outgoing connection to HOST:PORT
    mSender.setup(HOST, PORT);

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
    
    
    if(mBallCapture.getDetectedNumBalls()>0 && mBallCapture.bDetectedNewBall())
    {
        // 検出したかどうかを送信
        {
            ofxOscMessage m;
            m.setAddress("/mouse/button");
            m.addIntArg(1);
            mSender.sendMessage(m, true);
        }
        
        // 位置を送信
        {
            vector<ofVec3f> poses = mBallCapture.getDetectedBallPoses();
            
            for(auto& p : poses){
                cout << p.x << "," << p.y << endl;
                ofxOscMessage m;
                m.setAddress("/mouse/position");
                m.addFloatArg(ofMap(p.x, 0, 640, 0.f, 1.f, true));
                m.addFloatArg(ofMap(p.y, 0, 480, 0.f, 1.f, true));
                mSender.sendMessage(m, false);
            }
        }
        
        //mRing.play();
    }else{
        // 検出したかどうかを送信
        {
            ofxOscMessage m;
            m.setAddress("/mouse/button");
            m.addIntArg(0);
            mSender.sendMessage(m, true);
        }
        
        // 位置を送信
        {
            vector<ofVec3f> poses = mBallCapture.getDetectedBallPoses();
            
            for(auto& p : poses){
                cout << p.x << "," << p.y << endl;
                ofxOscMessage m;
                m.setAddress("/mouse/position");
                m.addFloatArg(ofMap(0, 0, 640, 0.f, 1.f, true));
                m.addFloatArg(ofMap(0, 0, 480, 0.f, 1.f, true));
                mSender.sendMessage(m, false);
            }
        }
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
