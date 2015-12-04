//
//  PMSc8Main.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc8Main.hpp"
#include "PMSongSelector.hpp"
#include "PMSettingsManagerGeneral.h"


PMSc8Main::PMSc8Main() : PMBaseScene("Scene 8")
{
#ifdef OF_DEBUG
    showGUI= PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene8();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene8();
#endif

    setSingleSetup(false);
    guiAudioAnalyzerCreated=false;
}

void PMSc8Main::setup()
{
    motionExtractor = &PMMotionExtractor::getInstance();

    ofPoint pos = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));

    PMRendererLayer1 *rendererLayer1 = new PMRendererLayer1(0);
    rendererLayer1->setup();
    rendererLayer1->setPosition(pos);
    renderers.push_back(rendererLayer1);

//    PMRendererLayer2 *rendererLayer2 = new PMRendererLayer2(0);
//    rendererLayer2->setup();
//    rendererLayer2->setPosition(pos);
//    renderers.push_back(rendererLayer2);
//
//    PMRendererLayer3 *rendererLayer3 = new PMRendererLayer3(0);
//    rendererLayer3->setup();
//    rendererLayer3->setPosition(pos);
//    renderers.push_back(rendererLayer3);
//
//    PMRendererLayer4 *rendererLayer4 = new PMRendererLayer4(0);
//    rendererLayer4->setup();
//    rendererLayer4->setPosition(pos);
//    renderers.push_back(rendererLayer4);

/*
    for(int i=0; i<1; i++){
        PMRendererLayer1 tempRender = PMRendererLayer1(i);
        tempRender.setup();
        switch (i) {
            case 0:
                tempRender.setPosition(ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
                break;
            case 1:
                tempRender.setPosition(renderers[0].getPosition());
                break;
            case 2:
                tempRender.setPosition(ofPoint(tempRender.getSize()/2,tempRender.getSize()/2));
                break;
            case 3:
                tempRender.setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
                break;
            default:
                break;
        }
        renderers.push_back(tempRender);
    }
*/

    //Audio device analyzer
    const unsigned int unsigint0=0;
    const unsigned int unsigint1=1;
    vector<unsigned int> audioChanels;
    audioChanels.push_back(0);
    audioChanels.push_back(1);
    cout<<audioChanels.size()<<endl;
    PMDeviceAudioAnalyzer *deviceAudioAnalyzer = PMAudioAnalyzer::getInstance().addDeviceAnalyzer(0, 0,
                                                                                                  2, 0, 44100, 1024, audioChanels);
    
    ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMSc8Main::pitchChanged);
    ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMSc8Main::energyChanged);
//    
//    ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMScene2::silenceStateChanged);
//    ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMScene2::pauseStateChanged);
//    ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMScene2::onsetDetected);
//    ofAddListener(deviceAudioAnalyzer->eventShtStateChanged, this, &PMScene2::shtDetected);
//    ofAddListener(deviceAudioAnalyzer->eventMelodyDirection, this, &PMScene2::melodyDirection);
}

void PMSc8Main::update()
{
    motionExtractor->update();
    kinectInfo = motionExtractor->getKinectInfo();
    if(songIsStarted){
        if (!song.isPlaying()) {
            cout<<"song_has_finished"<<endl;
            string sceneToChange="Scene 2";
//            ofNotifyEvent(goToSceneEvent, sceneToChange, this);
        }
    }
    ofSoundUpdate();
    
    for(int i=0; i<renderers.size(); i++){
        renderers[i]->update();
    }

    // Update Kinect info
    renderers[0]->setNodeReference(ofPoint(kinectInfo->rightHand_joint.x*ofGetWidth(), kinectInfo->rightHand_joint.y*ofGetHeight()));
//    renderers[1]->setNodeReference(ofPoint(kinectInfo->leftHand_joint.x*ofGetWidth(), kinectInfo->leftHand_joint.y*ofGetHeight()));
//    renderers[2]->setNodeReference(ofPoint(kinectInfo->head_joint.x*ofGetWidth(), kinectInfo->head_joint.y*ofGetHeight()));
//    renderers[3]->setNodeReference(ofPoint(kinectInfo->torso_joint.x*ofGetWidth(), kinectInfo->torso_joint.y*ofGetHeight()));
    
    
    // GUI
    {
        if (!guiAudioAnalyzerCreated)
        {
                guiAudioAnalyzer = new PMUICanvasAudioAnalyzer("AAUDIO ANALYZER", OFX_UI_FONT_MEDIUM, 0);
                guiAudioAnalyzer->init(5, 5);
                guiAudioAnalyzer->setBackgroundColor(ofColor::gray);
                guiAudioAnalyzer->setVisible(true);
        }
        guiAudioAnalyzerCreated = true;
    }
    
}

void PMSc8Main::draw()
{
    //ofBackground(255, 35, 32);
    ofSetColor(ofColor::red);
    ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
//    PMMotionExtractor::getInstance().draw();
//    KinectInfo* kinectOut=PMMotionExtractor::getInstance().getKinectInfo();
//    ofDrawEllipse(kinectOut->leftHand_joint.x*ofGetWidth(), kinectOut->leftHand_joint.y*ofGetHeight(), 10+5*kinectOut->leftHand_joint.a, 10+5*kinectOut->leftHand_joint.a);
//    ofDrawEllipse(kinectOut->rightHand_joint.x*ofGetWidth(), kinectOut->rightHand_joint.y*ofGetHeight(), 10+5*kinectOut->rightHand_joint.a, 10+5*kinectOut->rightHand_joint.a);
//    ofDrawEllipse(kinectOut->head_joint.x*ofGetWidth(), kinectOut->head_joint.y*ofGetHeight(), 10+7*kinectOut->head_joint.a, 10+7*kinectOut->head_joint.a);
//    ofDrawEllipse(kinectOut->torso_joint.x*ofGetWidth(), kinectOut->torso_joint.y*ofGetHeight(), 10+10*kinectOut->torso_joint.a, 10+10*kinectOut->torso_joint.a);
    ofColor c = ofColor(ofColor::white);
    ofClear(c);
    for(int i=0; i<renderers.size(); i++){
        renderers[i]->draw();
    }
}

void PMSc8Main::updateEnter()
{
    PMBaseScene::updateEnter();
    string songPath="songs/"+PMSongSelector::getInstance().getFilename();
    songIsStarted=false;
    loadSong(songPath);
    playSong();
    
    PMAudioAnalyzer::getInstance().start();
}

void PMSc8Main::updateExit()
{
    PMBaseScene::updateExit();
    song.stop();
}

void PMSc8Main::loadSong(string filename){
    song.load(filename);
    song.setVolume(0.75f);
    song.setMultiPlay(false);
}

void PMSc8Main::playSong()
{
    if (!song.isLoaded()){
        cout<<"Error - No loaded Sound!"<<endl;
    }
    song.play();
    songIsStarted=true;
}





//AUDIO struff

void PMSc8Main::pitchChanged(pitchParams &pitchParams)
{
//    cout<<pitchParams.midiNote<<endl;
}

void PMSc8Main::energyChanged(energyParams &energyParams)
{
    for(int i=0; i<renderers.size(); i++){
        renderers[i]->addOffset(energyParams.energy*20);
    }
}


void PMSc8Main::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);
    switch(key)
    {
        case 'g':
        case 'G':
        {
            showGUI = !showGUI;
            // TODO: There should be only 1 GUI for all the renderers. Probably need to gmove GUI to scene8.
            for (int i=0; i<renderers.size(); ++i)
                renderers[i]->showGUI(showGUI);

            ofClear(backgroundColor);

            break;
        }
        default: break;
    }
}
