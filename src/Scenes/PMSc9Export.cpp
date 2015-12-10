//
//  PMSc9Export.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc9Export.hpp"
#include "PMMotionExtractor.hpp"

PMSc9Export::PMSc9Export() : PMBaseScene("Scene 9")
{
    painting.load("TempRender.png");
    bigFont.load("fonts/NeutraTextTF-Book.otf", 40, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 30, true, true, false, 0.3, 72);
    textInput="Eduard Frigola";
}

void PMSc9Export::setup()
{
    ofClear(0,0,0);
    timestamp=ofGetElapsedTimef()-1;
    isSlash=false;
}

void PMSc9Export::update()
{
    if(ofGetElapsedTimef()-timestamp>0.7){
        timestamp=ofGetElapsedTimef();
        isSlash=!isSlash;
    }
}

void PMSc9Export::draw()
{
    ofBackground(0);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(ofColor::red);
//    plantilla.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    ofSetColor(ofColor::white);
//    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
    drawCenteredFont(bigFont, "Enhorabona!", ofGetWidth()/2, 145);
    drawCenteredFont(bigFont, "Aquesta és la teva interpretació!", ofGetWidth()/2, 190);
    drawCenteredFont(bigFont, "Si us plau, introdueix el teu nom", ofGetWidth()/2, 265);
    drawCenteredFont(bigFont, "i emporta't una impressió de la teva obra!", ofGetWidth()/2, 315);
    drawCenteredFont(smallFont, "(màxim 25 caràcters)", ofGetWidth()/2, 550);
    if(isSlash)
        bigFont.drawString(textInput, 140, 495);
    else
        bigFont.drawString(textInput+'|', 140, 495);
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofSetLineWidth(3);
    ofDrawRectangle(ofGetWidth()/2, 480, 850, 85);
//    ofDrawRectangle(ofGetWidth()/2, 1200, ofGetWidth()/1.7, ofGetHeight()/1.7);
    painting.draw(ofGetWidth()/2, 1200, ofGetWidth()/1.7, ofGetHeight()/1.7);
    ofPopStyle();
}

void PMSc9Export::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_DEL:
        case OF_KEY_BACKSPACE:
        {
            textInput=textInput.substr(0, textInput.length()-1);
            break;
        }
        default:
        {
            textInput.append(1, (char)key);
        }
            break;
    }
}
