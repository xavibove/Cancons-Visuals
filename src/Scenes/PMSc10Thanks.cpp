//
//  PMSc10Thanks.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc10Thanks.hpp"
#include "PMMotionExtractor.hpp"

PMSc10Thanks::PMSc10Thanks() : PMBaseScene("Scene Thanks")
{
    plantilla.load("escena10.jpg");
    bigFont.load("fonts/NeutraTextTF-Book.otf", 40, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 35, true, true, false, 0.3, 72);

}

void PMSc10Thanks::setup()
{
    ofClear(0,0,0);
}

void PMSc10Thanks::update()
{
    
}

void PMSc10Thanks::draw()
{
    ofBackground(0);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(ofColor::red);
//    plantilla.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    ofSetColor(ofColor::white);
//    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
    drawCenteredFont(bigFont, "Imprimint", ofGetWidth()/2, 462);
    drawCenteredFont(bigFont, "Moltes gràcies!", ofGetWidth()/2, 508);
    drawCenteredFont(bigFont, "Cançons Visuals", ofGetWidth()/2, 938);
    drawCenteredFont(smallFont, "www.xavibove.com", ofGetWidth()/2, 988);
}