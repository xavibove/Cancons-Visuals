//
//  PMSc6Kinect_Detect.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc6Kinect_Detect.hpp"
#include "PMMotionExtractor.hpp"

PMSc6Kinect_Detect::PMSc6Kinect_Detect() : PMBaseScene("Scene 6")
{

}

void PMSc6Kinect_Detect::setup()
{

}

void PMSc6Kinect_Detect::update()
{
#if ENABLE_KINECT
    PMMotionExtractor::getInstance().update();
    if (PMMotionExtractor::getInstance().isReady())
    {
        string sceneToChange = "Scene 7";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
#else
    string sceneToChange="Scene 7";
    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
#endif
}

void PMSc6Kinect_Detect::draw()
{
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    ofScale(scaleX, scaleY);
    drawCenteredFont(baseBoldFont, "Detecció de cos", 1080/2, 100);
    drawCenteredFont(baseBoldFont, "Si us plau, mira endavant i obre els braços", 1080/2, 150);
    ofPopMatrix();
    
#if ENABLE_KINECT
    PMMotionExtractor::getInstance().draw();
#endif
}
