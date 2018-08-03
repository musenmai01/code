#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // recieverの初期化
    setupReciever();
    
    // 爆発の初期化
    // ここに追加してください
    
    //基本設定
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);//背景色は黒
    ofSetFrameRate(60);//フレームレイトの設定
    ofSetCircleResolution(64);//円の解像度の設定
    ofEnableAlphaBlending();//透過の設定
    mySound.load("destruction.mp3");//爆発音の設定
    myImageSpace.load("space.jpg");//背景設定を設定
    myImageAlien.load("alien.png");//ボールの当てる的の設定
    
    //円の位置
    for(int i = 0;i < CIRCLE_NUM;i++){
        particle[i].setup();
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //円の座標を更新
    for(int i = 0;i < CIRCLE_NUM;i++){
        particle[i].update();
    }

    // recieverの更新
    // mIsBallEvent: ボールが壁にぶつかったかどうか
    // mBallPos: ぶつかったときの壁の位置(x, y)
    updateReciever(mIsBallEvent, mBallPos);
    
    if(mIsBallEvent){
        // 爆発を追加
        // ここに追加してください
        
        cout << "ball event detected" << endl;
        cout << mBallPos.x << "," << mBallPos.y << endl;
        
        
        //サウンド再生開始
        mySound.play();
        
        //マウスを押したら爆発        
        for(int i = 0;i < CIRCLE_NUM;i++){
            particle[i].mousePressed(mBallPos.x,mBallPos.y);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    // 爆発を描画
    // ここに追加してください
    
    //塗りつぶし
    ofSetColor(255,255,255,23);
    //宇宙の背景を配置
    myImageSpace.draw(0, 0, ofGetWidth(), ofGetHeight());
    myImageAlien.draw(ofGetWidth()/2-250, ofGetHeight()/2-150, 500, 500);
    
    //ランダムな位置に円を描画
    for(int i = 0;i < CIRCLE_NUM;i++){
        particle[i].draw();
    }

    
    ofDrawCircle(mBallPos.x, mBallPos.y, 10);
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
    //サウンド再生開始
    mySound.play();
    
    //マウスを押したら爆発
    for(int i = 0;i < CIRCLE_NUM;i++){
        particle[i].mousePressed(x,y);
    }
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
void ofApp::setupReciever()
{
    // listen on the given port
    ofLog() << "listening for osc messages on port " << PORT;
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::updateReciever(bool& ballEvent, ofVec2f& ballPos)
{
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/mouse/position"){
            
            // both the arguments are floats
            ballPos.x = ofMap(m.getArgAsFloat(0), 0.0f, 1.0, 0.0, ofGetWidth());
            ballPos.y = ofMap(m.getArgAsFloat(1), 0.0f, 1.0, 0.0, ofGetHeight());
        }
        
        // check for mouse button message
        else if(m.getAddress() == "/mouse/button"){
            
            // first argument is int32, second is a string
            ballEvent = m.getArgAsInt32(0);
        }
    }
}


