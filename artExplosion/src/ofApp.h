#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "particle/particle.hpp"

// listening port
#define PORT 12345

// max number of strings to display
#define NUM_MSG_STRINGS 20

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
    
        void setupReciever();
        void updateReciever(bool& ballEvent, ofVec2f& ballPos);
        ofxOscReceiver receiver;
    
    
        bool mIsBallEvent; // ボールが壁にぶつかったかどうか
        ofVec2f mBallPos;  // ボールがぶつかった位置
    
        // ----------
        // 北原さんのプロジェクト
        // ----------
        static const int CIRCLE_NUM = 1000;
        //位置ベクトル
        Particle particle[CIRCLE_NUM];
        //音のクラス
        ofSoundPlayer mySound;
        //画像のクラス
        ofImage myImageSpace;
        ofImage myImageAlien;

};
