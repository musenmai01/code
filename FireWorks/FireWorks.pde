import processing.sound.*;
SoundFile sd1;

import netP5.*;
import oscP5.*;

//OSCP5クラスのインスタンス
OscP5 oscP5;
//mouseの位置ベクトル
PVector mouseLoc;
//kinectで完治したかを検知
int clicked;

//花火のarrayListの作成
ArrayList<Fireworks> fireworks=new ArrayList<Fireworks>();      

int power=180;

void setup () {
  noCursor();
  //OSC受信のとこ----------------------
  oscP5=new OscP5(this, 12345);
  //mouseの位置の初期設定
  mouseLoc=new PVector(width/2, height/2);
  //mouseClickの初期化
  clicked=0;

  fullScreen(P3D);
  frameRate(55); 
  hint(DISABLE_DEPTH_TEST);
  blendMode(ADD);
  imageMode(CENTER);
  
  sd1 = new SoundFile(this,"109736__soundcollectah__double-hit.aiff"); 
}

void draw () {
  background(0, 0, 30);
  for (int i=0; i<fireworks.size(); i++) {
    Fireworks art=fireworks.get(i);
    if (art.centerPosition.y-art.radius>height) {
      fireworks.remove(i);
    }
    art.display();
    art.update();
  }
  
  if(clicked==1){
    fireworks.add(new Fireworks(power));
  }
}

void mousePressed() {
  fireworks.add(new Fireworks(power));
}

//OSCメッセージを受信した際に実行するイベント
void oscEvent(OscMessage msg) {
  //もしOSCメッセージが /mouse/position だったら
  if (msg.checkAddrPattern("/mouse/position")==true) {
    //最初の値をint方としてX座標に
    mouseLoc.x = msg.get(0).floatValue()*width;
    //次の値をint方としてY座標に
    mouseLoc.y = msg.get(1).floatValue()*height;
  }
  if (msg.checkAddrPattern("/mouse/button")==true) {
    //Bool値を読み込み
    clicked = msg.get(0).intValue();
    println("msg = " + clicked);
    print("*");
  }
}


//発光表現の元となるクラス
PImage createLight(float rPower, float gPower, float bPower) {
  int side=64;
  float center=side/2.0;

  PImage img=createImage(side, side, RGB);

  for (int y=0; y<side; y++) {
    for (int x=0; x<side; x++) {
      float distance=(sq(center-x)+sq(center-y))/10.0;
      int r=int((255*rPower)/distance);
      int g=int((255*gPower)/distance);
      int b=int((255*bPower)/distance);
      img.pixels[x+y*side]=color(r, g, b);
    }
  }
  return img;
}


PImage createLightInside(float rPower, float gPower, float bPower) {
  int side=64;
  float center=side/2.0;

  PImage imgInside=createImage(side, side, RGB);

  for (int y=0; y<side; y++) {
    for (int x=0; x<side; x++) {
      float distance=(sq(center-x)+sq(center-y))/10.0;
      int r=int((255*rPower)/distance);
      int g=int((255*gPower)/distance);
      int b=int((255*bPower)/distance);
      imgInside.pixels[x+y*side]=color(r, g, b);
    }
  }
  return imgInside;
}

//花火作るぞ〜〜
class Fireworks {
  //花火の火の数
  int num=512;
  //花火の中心の初期位置
  PVector centerPosition;
  //花火の中心の初期速度
  PVector velocity=new PVector(0, 0, 0);

  PImage img;
  PImage imgInside;

  float radius;
  PVector accel=new PVector(0, 0.5, 0);
  PVector[] firePosition=new PVector[num];


  Fireworks(float r) {
    float cosTheta;
    float sinTheta;
    float phi;
    float colorchange=random(0, 5);
    mouseLoc.x = mouseX;
    mouseLoc.y = mouseY;
    centerPosition = new PVector(mouseLoc.x, mouseLoc.y, 0);
    radius=r;
    for (int i=0; i<num; i++) {
      cosTheta = random(0, 1) * 2 - 1;
      sinTheta = sqrt(1- cosTheta*cosTheta);
      phi = random(0, 1) * 2 * PI;
      firePosition[i]=new PVector(radius * sinTheta * cos(phi), radius * sinTheta * sin(phi), 0);
      firePosition[i]=PVector.mult(firePosition[i], random(1, 1.25));
    }
    //色をランダムで初期化(綺麗な色が出やすいように調整)
    if (colorchange>=3.8) {
      img=createLight(0.9, random(0.2, 0.5), random(0.2, 0.5));
    } else if (colorchange>3.2) {
      img=createLight(random(0.2, 0.5), 0.9, random(0.2, 0.5));
    } else if (colorchange>2) {
      img=createLight(random(0.2, 0.5), random(0.2, 0.5), 0.9);
    } else {
      img=createLight(random(0.5, 0.8), random(0.5, 0.8), random(0.5, 0.8));
    }

    if (colorchange>=3.8) {
      imgInside=createLightInside(0.9, random(0.2, 0.5), random(0.2, 0.5));
      sd1.play();
    } else if (colorchange>3.2) {
      imgInside=createLightInside(random(0.2, 0.5), 0.9, random(0.2, 0.5));
      sd1.play();
    } else if (colorchange>2) {
      imgInside=createLightInside(random(0.2, 0.5), random(0.2, 0.5), 0.9);
      sd1.play();
    } else {
      imgInside=createLightInside(random(0.5, 0.8), random(0.5, 0.8), random(0.5, 0.8));
      sd1.play();
    }
  }

  void display() {
    for (int i=0; i<num; i++) {
      pushMatrix();
      translate(centerPosition.x, centerPosition.y, centerPosition.z);
      translate(firePosition[i].x, firePosition[i].y, firePosition[i].z);
      image(img, 0, 0);
      popMatrix();

      if (i<num/2) {
        pushMatrix();
        translate(centerPosition.x, centerPosition.y, centerPosition.z);
        translate(firePosition[i].x/2, firePosition[i].y/2, firePosition[i].z/2);
        image(imgInside, 0, 0);
        popMatrix();
      }
      firePosition[i]=PVector.mult(firePosition[i], 1.015);
    }
  }

  void update() {
    radius=dist(0, 0, 0, firePosition[0].x, firePosition[0].y, firePosition[0].z);
    centerPosition.add(velocity);
    velocity.add(accel);
  }
}