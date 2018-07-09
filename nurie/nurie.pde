int num=100;
float[]lastX= new float[num];
float[]lastY= new float[num];
float t=0;

//num=0は真ん中の円
//num=1は右の円

void setup() {
  fullScreen(P2D);
  background(0, 15, 30);
  
  //========ここから真ん中の円を書く
 for(int s=0;s<360;s++){
    float radius=180;
    float[]x=new float[num];
    float[]y=new float[num];
    //基本ここだけいじって画像を作ってください
    x[0] = width/2+ radius*(1+cos(radians(s)))*cos(radians(s));
    y[0] = height/2+ radius* (1+cos(radians(s)))*sin(radians(s));
    stroke(128);
    if (lastX[0]!= 0) {
      strokeWeight(1);
      line(x[0], y[0], lastX[0], lastY[0]);
    }
    lastX[0] = x[0];
    lastY[0] = y[0];
    s++;
  }
  
  //=================ここまで円
  
  for(int s=0;s<360;s++){
    float radius=180;
    float[]x=new float[num];
    float[]y=new float[num];
    //基本ここだけいじって画像を作ってください
    x[1] = width+ radius*cos(radians(s));
    y[1] = height+ radius*sin(radians(s));
    stroke(128);
    if (lastX[1]!= 0) {
      strokeWeight(1);
      line(x[1], y[1], lastX[1], lastY[1]);
    }
    lastX[1] = x[1];
    lastY[1] = y[1];
    s++;
  }
}


void draw() {
  
}
