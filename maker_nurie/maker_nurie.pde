import processing.sound.*;
SoundFile sd1,sd2,sd3,sd4,sd5,sd6,sd7;

import netP5.*;
import oscP5.*;

//OSCP5クラスのインスタンス
OscP5 oscP5;
//mouseの位置ベクトル
PVector mouseLoc;
//kinectで完治したかを検知
int clicked;

PImage Penguin;
PImage tako;
PImage hitodeRight;
PImage hitodeLeft;
PImage aseRight;
PImage aseLeft;
PImage green;
PImage blue;
PImage orange;



boolean peng=false;
boolean takoBool=false;
boolean hitodeR=false;
boolean hitodeL=false;
boolean aseR=false;
boolean aseL=false;
boolean gre=false;
boolean blu=false;
boolean ora=false;


float pengLength=500;
float takoLength=200;
float hitodeRLength=200;
float hitodeLLength=150;
float aseRLength=170;
float aseLLength=150;
float greenLength=250;
float blueLength=200;
float orangeLength=100;

void setup(){
  //noCursor();
  //OSC受信のとこ----------------------
  oscP5=new OscP5(this, 12345);
  //mouseの位置の初期設定
  mouseLoc=new PVector(width/2, height/2);
  //mouseClickの初期化
  clicked=0;
  
  Penguin=loadImage("pengin.jpg");
  tako=loadImage("tako.jpg");
  hitodeRight=loadImage("hitodeRight.jpg");
  hitodeLeft=loadImage("hitodeLeft.jpg");
  aseRight=loadImage("aseRight.jpg");
  aseLeft=loadImage("aseLeft.jpg");
  green=loadImage("green.jpg");
  blue=loadImage("blue.jpg");
  orange=loadImage("orange.jpg");
  
  
  fullScreen();
  imageMode(CENTER);
  
  
  //ペンギン鳴き声
  sd1 = new SoundFile(this,"110388__soundscalpel-com__animals-cat-meow-001.wav");
  //タコ
  sd2 = new SoundFile(this,"179309__martian__cute-creature-look-out.aiff");
  //ヒトデ（星の音）
  sd3 = new SoundFile(this,"411460__inspectorj__power-up-bright-a.wav");
  //汗右（水しぶき音1）
  sd4 = new SoundFile(this,"416710__inspectorj__splash-small-a.wav");
  //汗左（水しぶき音2）
  sd5 = new SoundFile(this,"398032__swordofkings128__splash.wav");
  //玉の音
  sd6 = new SoundFile(this,"146266__setuniman__bubbling-boing-0-h16j.wav"); 
  //ハズレ音
  sd7 = new SoundFile(this,"405548__raclure__cancel-miss-chime.wav"); 
  
}


void draw(){
  background(255);
  //ペンギンのやつ---------------------
  if(peng==true){
    tint(255,255);
    image(Penguin,width/2,height/2,pengLength,pengLength);
  }else{
    tint(255,50);
    image(Penguin,width/2,height/2,pengLength,pengLength);
  }
  
  //タコのやつ--------------------------
  if(takoBool==true){
    tint(255,255);
    image(tako,width*3/4,height/4,takoLength,takoLength);
  }else{
    tint(255,50);
    image(tako,width*3/4,height/4,takoLength,takoLength);
  }
  //ヒトデの右のやつ----------------------
  if(hitodeR==true){
    tint(255,255);
    image(hitodeRight,width/4,height*3/4,hitodeRLength,hitodeRLength);
  }else{
    tint(255,50);
    image(hitodeRight,width/4,height*3/4,hitodeRLength,hitodeRLength);
  }
  //ヒトデの左のやつ----------------------
  if(hitodeL==true){
    tint(255,255);
    image(hitodeLeft,width/8,height*5/6,hitodeLLength,hitodeLLength);
  }else{
    tint(255,50);
    image(hitodeLeft,width/8,height*5/6,hitodeLLength,hitodeLLength);
  }
  //汗の右のやつ----------------------
  if(aseR==true){
    tint(255,255);
    image(aseRight,width*4.5/7,height*4.2/5,aseRLength,aseRLength);
  }else{
    tint(255,50);
    image(aseRight,width*4.5/7,height*4.2/5,aseRLength,aseRLength);
  }
  //汗の左のやつ----------------------
  if(aseL==true){
    tint(255,255);
    image(aseLeft,width*2.3/7,height/6,aseLLength,aseLLength);
  }else{
    tint(255,50);
    image(aseLeft,width*2.3/7,height/6,aseLLength,aseLLength);
  }

  //緑たま---------------------
  if(gre==true){
    tint(255,255);
    image(green,width*1/7,height*1.1/3,greenLength,greenLength);
  }else{
    tint(255,50);
    image(green,width*1/7,height*1.1/3,greenLength,greenLength);
  }
    //青たま---------------------
  if(blu==true){
    tint(255,255);
    image(blue,width*6.5/8,height*2/3,blueLength,blueLength);
  }else{
    tint(255,50);
    image(blue,width*6.5/8,height*2/3,blueLength,blueLength);
  }
    //オレンジたま---------------------
  if(ora==true){
    tint(255,255);
    image(orange,width*7.2/8,height*6.7/8,orangeLength,orangeLength);
  }else{
    tint(255,50);
    image(orange,width*7.2/8,height*6.7/8,orangeLength,orangeLength);
  }
  
  if(clicked==1){
     paint(mouseLoc.x,mouseLoc.y);
  }
}

void mouseReleased(){
  mouseLoc.x = mouseX;
  mouseLoc.y = mouseY;
  paint(mouseLoc.x,mouseLoc.y);
}

void paint(float locx, float locy){
  //ペンギンのやつ------------------------
  if(width/2-pengLength/2<locx&&locx<width/2+pengLength/2&&height/2-pengLength/2<locy&&locy<height/2+pengLength/2){
     if(peng==false){
        peng=true;
        sd1.play();        
     }
  
  //タコのやつ--------------------------------------
  } else if(width*3/4-takoLength/2<locx&&locx<width*3/4+takoLength/2&&height/4-takoLength/2<locy&&locy<height/4+takoLength/2){
     if(takoBool==false){
        takoBool=true;
        sd2.play();    
     }
  
  //ヒトデ右のやつ--------------------------------------
  } else if(width/4-hitodeRLength/2<locx&&locx<width/4+hitodeRLength/2&&height*3/4-hitodeRLength/2<locy&&locy<height*3/4+hitodeRLength/2){
     if(hitodeR==false){
        hitodeR=true;
        sd3.play();        
     }
     
  //ヒトデ左のやつ--------------------------------------
  } else if(width/8-hitodeLLength/2<locx&&locx<width/8+hitodeLLength/2&&height*5/6-hitodeLLength/2<locy&&locy<height*5/6+hitodeRLength/2){
     if(hitodeL==false){
        hitodeL=true;
        sd3.play();        
     }
     
  //汗右のやつ--------------------------------------
  } else if(width*4.5/7-aseRLength/2<locx&&locx<width*4.5/7+aseRLength/2&&height*4.2/5-aseRLength/2<locy&&locy<height*4.2/5+aseRLength/2){
     if(aseR==false){
        aseR=true;
        sd4.play();        
     }

  //汗左のやつ--------------------------------------
  } else if(width*2.3/7-aseLLength/2<locx&&locx<width*2.3/7+aseLLength/2&&height/6-aseLLength/2<locy&&locy<height/6+aseRLength/2){
     if(aseL==false){
        aseL=true;
        sd5.play();        
     }

  // 緑たま--------------------------------------
  } else if(width*1/8-greenLength/2<locx&&locx<width*1/8+greenLength/2&&height*1.1/3-greenLength/2<locy&&locy<height*1.1/3+greenLength/2){
     if(gre==false){
        gre=true;
        sd6.play();        
     }

  //青たま--------------------------------------
  }else if(width*6.5/8-blueLength/2<locx&&locx<width*6.5/8+blueLength/2&&height*2/3-blueLength/2<locy&&locy<height*2/3+blueLength/2){
     if(blu==false){
        blu=true;
        sd6.play();        
     }
     
  //オレンジたま--------------------------------------
   } else if(width*7.2/8-orangeLength/2<locx&&locx<width*7.2/8+orangeLength/2&&height*6.7/8-orangeLength/2<locy&&locy<height*6.7/8+orangeLength/2){
     if(ora==false){
        ora=true;
        sd6.play();        
     }
     
  //ハズレ
  } else {
        sd7.play();
  }
}

void keyPressed(){
  if(key=='r'||key=='R'){
     reset(); 
  }
}

void reset() {
  peng=false;
  takoBool=false;
  hitodeR=false;
  hitodeL=false;
  aseR=false;
  aseL=false;
  gre=false;
  blu=false;
  ora=false;
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
