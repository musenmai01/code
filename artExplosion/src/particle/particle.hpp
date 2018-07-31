//
//  particle.hpp
//  particle
//
//  Created by 北原 勝行 on 2018/07/30.
//
#pragma once

#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>
#include "ofMain.h"

class Particle{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y);//ここはあとで削除
    
    float loc_x;//円のx座標
    float loc_y;//円のy座標
    float speed_x;//x軸方向のスピード
    float speed_x1;//x軸の方向に摩擦係数を加えたもの
    float speed_y;//y軸方向のスピード
    float speed_y1;//y軸の方向に摩擦係数を加えてもの
    int radius;//円の半径
    int red;//redの成分
    int green;//greenの成分
    int blue;//blueの成分
    float gravity;//重力の強さを設定
    float friction;//摩擦力の強さを設定
    

};

#endif /* particle_hpp */
