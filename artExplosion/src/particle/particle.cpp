//
//  particle.cpp
//  particle
//
//  Created by 北原 勝行 on 2018/07/30.
//

#include "particle.hpp"

//コンストラクタ
Particle::Particle(){
    for(int i =0;i<NUM;i++){
        pos[i] = ofPoint(ofRandom(-10,10), ofRandom(-10, 10)); //位置の指定
        radius[i] = ofRandom(1,10); //半径の指定
        speed[i] = ofPoint(ofRandom(-5, 5),ofRandom(-5, 5));//移動スピード初期化
        
        //円の色
        red[i] = ofRandom(0,255);
        green[i] = ofRandom(0,255);
        blue[i] = ofRandom(0,255);
        
        gravity = 0.1;//重力の初期値
        friction = 0.999;//摩擦力の初期値
    }
        
}

void Particle::update(){
    //円を描く
    for(int i=0;i<NUM;i++){
        //色の設定
        ofSetColor(red[i], green[i], blue[i],127);
        ofDrawCircle(pos[i].x, pos[i].y, radius[i]); //画面の中心に円を描く
    }
    
}

void Particle::draw(){
    for(int i=0;i<NUM;i++){
        speed1[i].x = speed[i].x * friction;//x軸の方向の摩擦量の影響を計算
        speed1[i].y = speed[i].y * friction;//y軸の方向の摩擦量の影響を計算
        speed1[i].y = speed[i].y + gravity;//重力の影響を計算
        //座標を更新
        pos[i] +=speed1[i];
    }
}

//posセッター
void Particle::setPos(ofPoint _pos){
    for(int i=0;i<NUM;i++){
        pos[i] = _pos;
    }
}

//posゲッター
ofPoint Particle::getPos(){
    for(int i=0;i<NUM;i++){
        return pos[i];
    }
}

