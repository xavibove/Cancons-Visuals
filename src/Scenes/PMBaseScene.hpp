//
//  PMBaseScene.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#ifndef PMBaseScene_hpp
#define PMBaseScene_hpp

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxSceneManager.h"
#include "ofxScene.h"
#include "Defaults.h"

class PMBaseScene : public ofxFadeScene
{
public:

    PMBaseScene(const string &name);

    virtual void setup() = 0;
    virtual void update() = 0;
    
    
    virtual void updateEnter();
    virtual void updateExit()=0;
    
    virtual void draw()=0;
    
    virtual void drawCenteredFont(ofTrueTypeFont &font, string s, int x, int y);
    virtual void drawSettingsNumbers(int currentNumber);

    void keyReleased(int key) {};

    ofEvent<string> goToSceneEvent;

protected:

    ofColor backgroundColor;
    ofImage backgroundImage;

    ofTrueTypeFont  baseFont;
    ofTrueTypeFont  baseBoldFont;
    ofTrueTypeFont  numberFont;
    ofTrueTypeFont  numberBoldFont;
};

#endif /* PMBaseScene_hpp */
