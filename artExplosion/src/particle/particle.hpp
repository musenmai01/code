//
//  particle.hpp
//  particle
//
//  Created by 北原 勝行 on 2018/07/30.
//
#pragma once

#ifndef particle_hpp
#define particle_hpp
#define NUM 1000

#include <stdio.h>
#include "ofMain.h"

class Particle{
private:
    ofPoint pos[NUM];//円の位置
    float radius[NUM];//円の半径
    ofPoint speed[NUM];//円の移動スピード
    ofPoint speed1[NUM];//円の移動スピード
    float phase;//円の伸縮連動の位相
    float phaseSpeed;//円の伸縮スピード
    float strechedRadius;//伸縮した結果の半径
    int red[NUM];//redの成分
    int green[NUM];//greenの成分
    int blue[NUM];//blueの成分
    float gravity;//重力の強さを設定
    float friction;//摩擦力の強さを設定
    
public:
    Particle();//コンストラクタ
    void draw(); //円を描く
    void update();//円の移動
    void setRadius(float radius);//radiusのセッター
    float getRadius();//radiusのゲッター
    void setPos(ofPoint pos);//posのセッター
    ofPoint getPos();//posのゲッター
    void setSpeed(ofPoint speed);//speedセッター
    ofPoint getSpeed();//speedゲッター
    void mousePressed(int x, int y);

};

#endif /* particle_hpp */
