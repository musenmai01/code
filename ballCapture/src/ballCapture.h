#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCV.h"

class ballCapture {

public:
    
    // kinectのセットアップ
    void setup();
    
    // ボールの認識等
    void update();

    // RGBD画像の表示
    void draw();
    
    // 終了
    void exit();
    
    // キーボード処理
    void keyPressed(int key);
    
    // 近接のしきい値
    void setNearThreshold(int val);
    
    // 遠方のしきい値
    void setFarThreshold(int val);
    
    // 検出されたボールの個数
    int getDetectedNumBalls();
    
    vector<ofVec3f> getDetectedBallPoses();
    
    // 新たにボールが検出されたかどうか
    bool bDetectedNewBall();
    
private:
    
    // kinectのインスタンス
    ofxKinect mKinect;
    
    // 画像系まとめ
    ofxCvColorImage colorImg;
    
    // 奥行きグレースケール画像
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    
    // 奥行き(近接)
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    
    // 奥行き(遠方)
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder;
    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    int mPrevNumBall;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
};
