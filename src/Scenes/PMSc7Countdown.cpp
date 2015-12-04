//
//  PMSc7Countdown.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc7Countdown.hpp"
#include "PMSettingsManagerGeneral.h"


PMSc7Countdown::PMSc7Countdown() : PMBaseScene("Scene 7")
{
//    setFadeOut(0);
}

void PMSc7Countdown::setup()
{

}

void PMSc7Countdown::updateEnter()
{
    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif

    countdown.set();
    countdown.setAlarm(countdownTime * 1000);
    PMBaseScene::updateEnter();
}

void PMSc7Countdown::update()
{
//    cout<<(int)countdown.getDiff()/1000<<endl;
    if(countdown.alarm()){
        string toScene="Scene 8";
        ofNotifyEvent(goToSceneEvent, toScene, this);
    }
}

void PMSc7Countdown::draw()
{
    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif

    drawCenteredFont(baseFont, ofToString(countdownTime-(int)countdown.getDiff()/1000), ofGetWidth()/2, ofGetHeight()/2);
}

void PMSc7Countdown::updateExit()
{
    
}