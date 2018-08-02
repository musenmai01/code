#include "ballCapture.h"

//--------------------------------------------------------------
void ballCapture::setup(){
    
    mKinect.setRegistration(true);
    
    mKinect.init();
    mKinect.open();
    
    // print the intrinsic IR sensor values
    if(mKinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << mKinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << mKinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << mKinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << mKinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(mKinect.width, mKinect.height);
    grayImage.allocate(mKinect.width, mKinect.height);
    grayThreshNear.allocate(mKinect.width, mKinect.height);
    grayThreshFar.allocate(mKinect.width, mKinect.height);

    nearThreshold = 230;
    farThreshold = 70;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
//    angle = 0;
//    mKinect.setCameraTiltAngle(angle);
    
    // start from the front
    bDrawPointCloud = false;
}

//--------------------------------------------------------------
void ballCapture::update(){
    
    mPrevNumBall = getDetectedNumBalls();
    
    ofBackground(100, 100, 100);
    
    mKinect.update();
    
    // there is a new frame and we are connected
    if(mKinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(mKinect.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (mKinect.width*mKinect.height)/2, 20, false);
    }
}

//--------------------------------------------------------------
void ballCapture::draw(){
    ofSetColor(255, 255, 255);
    
    if(bDrawPointCloud) {
        easyCam.begin();
        //drawPointCloud();
        easyCam.end();
    } else {
        // draw from the live kinect
        mKinect.drawDepth(10, 10, 400, 300);
        mKinect.draw(420, 10, 400, 300);
        
        grayImage.draw(10, 320, 400, 300);
        contourFinder.draw(10, 320, 400, 300);
        
    }
    
    // draw instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    if(mKinect.hasAccelControl()) {
        reportStream << "accel is: " << ofToString(mKinect.getMksAccel().x, 2) << " / "
        << ofToString(mKinect.getMksAccel().y, 2) << " / "
        << ofToString(mKinect.getMksAccel().z, 2) << endl;
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
    << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    << ", fps: " << ofGetFrameRate() << endl
    << "press c to close the connection and o to open it again, connection is: " << mKinect.isConnected() << endl;
    
    if(mKinect.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
        << "press 1-5 & 0 to change the led mode" << endl;
    }
    
    ofDrawBitmapString(reportStream.str(), 20, 652);
    

}

//--------------------------------------------------------------
void ballCapture::exit()
{
    mKinect.setCameraTiltAngle(0); // zero the tilt on exit
    mKinect.close();

}

//--------------------------------------------------------------
void ballCapture::setNearThreshold(int val)
{
    if (val > 255) val = 255;
    nearThreshold = val;
}

//--------------------------------------------------------------
void ballCapture::setFarThreshold(int val)
{
    if (val > 255) val = 255;
    farThreshold = val;
}

//--------------------------------------------------------------
int ballCapture::getDetectedNumBalls()
{
    return contourFinder.nBlobs;
}

//--------------------------------------------------------------
bool ballCapture::bDetectedNewBall()
{
    if(mPrevNumBall != getDetectedNumBalls()){
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------
vector<ofVec3f> ballCapture::getDetectedBallPoses()
{
    vector<ofVec3f> poses;
    for(auto &n : contourFinder.blobs)
    {
        poses.push_back(n.centroid);
    }
    return poses;
}

//--------------------------------------------------------------
void ballCapture::keyPressed (int key) {
    switch (key) {
        case ' ':
            bThreshWithOpenCV = !bThreshWithOpenCV;
            break;
            
        case'p':
            bDrawPointCloud = !bDrawPointCloud;
            break;
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
            
        case 'w':
            mKinect.enableDepthNearValueWhite(!mKinect.isDepthNearValueWhite());
            break;
            
        case 'o':
            mKinect.setCameraTiltAngle(angle); // go back to prev tilt
            mKinect.open();
            break;
            
        case 'c':
            mKinect.setCameraTiltAngle(0); // zero the tilt
            mKinect.close();
            break;
            
        case '1':
            mKinect.setLed(ofxKinect::LED_GREEN);
            break;
            
        case '2':
            mKinect.setLed(ofxKinect::LED_YELLOW);
            break;
            
        case '3':
            mKinect.setLed(ofxKinect::LED_RED);
            break;
            
        case '4':
            mKinect.setLed(ofxKinect::LED_BLINK_GREEN);
            break;
            
        case '5':
            mKinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
            break;
            
        case '0':
            mKinect.setLed(ofxKinect::LED_OFF);
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            mKinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            mKinect.setCameraTiltAngle(angle);
            break;
    }
}


