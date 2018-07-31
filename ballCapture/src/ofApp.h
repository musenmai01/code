#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ballCapture.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 12345


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
        void exit();
    
        // ボールをキャプチャするための機能
        ballCapture mBallCapture;
    
        // Kinectの近接/遠方の値の設定
        ofxIntSlider mNearThreshold;
        ofxIntSlider mFarThreshold;
        void nearThresholdChanged(int &val);
        void farThresholdChanged(int &val);

        // GUI
        ofxPanel mGui;
    
        // 検出された音を流す変数
        ofSoundPlayer mRing;
    
        ofxOscSender mSender;
};
