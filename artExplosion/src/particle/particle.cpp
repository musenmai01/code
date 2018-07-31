//
//  particle.cpp
//  particle
//
//  Created by 北原 勝行 on 2018/07/30.
//

#include "particle.hpp"

void Particle::setup(){
    //円の位置
    loc_x = ofGetWidth() / 2;//円のx座標の初期値
    loc_y = ofGetHeight() / 2;//円のy座標の初期値
    speed_x = ofRandom(-10, 10);
    speed_y = ofRandom(-10, 10);
    
    //半径
    radius = ofRandom(1, 10);
    
    //円の色
    red = ofRandom(0,255);;
    green = ofRandom(0,255);;
    blue = ofRandom(0,255);;
    
    gravity = 0.1;//重力の初期値
    friction = 0.999;//摩擦力の初期値
        
}

void Particle::update(){
    //円の座標を更新
    speed_x1 = speed_x * friction;//x軸の方向の摩擦量の影響を計算
    speed_y1 = speed_y * friction;//y軸の方向の摩擦量の影響を計算
    speed_y1 = speed_y1 + gravity;//重力の影響を計算
    
    loc_x = loc_x + speed_x1;//円のx座標を更新
    loc_y = loc_y + speed_y1;//円のy座標を更新
    
}

void Particle::draw(){
    //色の設定
    ofSetColor(red, green, blue,127);
    //ランダムな位置に円を描画
    ofDrawCircle(loc_x,loc_y, radius);

}

//ここはあとで削除
void Particle::mousePressed(int x, int y){
    loc_x = x;
    loc_y = y;
}

