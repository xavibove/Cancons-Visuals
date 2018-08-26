////
//  PMMotionExtractor.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#ifndef PMMotionExtractor_hpp
#define PMMotionExtractor_hpp

#pragma once

#include "ofMain.h"
#include "Defaults.h"
#include "ofxKinectForWindows2.h"
#if ENABLE_REMOTE_KINECT
#include "ofxOsc.h"
#include "OSCSettings.h"
#endif

struct KinectElement
{
	ofPoint pos;
	ofPoint v;
	float a;
};
struct KinectInfo
{
	KinectElement leftHand;
	KinectElement rightHand;
	KinectElement leftKnee;
	KinectElement rightKnee;
	KinectElement head;
	KinectElement torso;
};

class PMMotionExtractor
{
public:
	/**
	* getInstance()
	* Returns singleton instance
	*/
	static PMMotionExtractor &getInstance()
	{
		static PMMotionExtractor instance;
		return instance;
	}

	PMMotionExtractor() {};
	~PMMotionExtractor() {};

	bool setup();
	void update(ofEventArgs & a);
	void draw(int x = 0, int y = 0, int width = ofGetWidth(), int height = ofGetHeight(), bool drawHands = false, bool drawBody = false);
	void exit();

	void start() {};
	void stop() {};
	void saveSettings();

	bool reset(bool kinectActivated);
	bool isTracking() {
		return hasUser;
	};

	void computeVelocity(int meanSize);
	ofPixels getColorPixels();

	KinectInfo *getKinectInfo();
	void resetUsers() {};

	ofxKFW2::Data::Body findClosestBody(vector<ofxKFW2::Data::Body> bodies);

	ofEvent<bool> eventUserDetection;
	ofEvent<bool> eventUserPositioned;
	void increaseDistance();
	void decreaseDistance();
	//void keyPressed(ofKeyEventArgs &e);

private:
	ofxKFW2::Device kinect;
	KinectInfo kinectOut;
	KinectInfo handsInfo;
	bool hasUser, hasKinect;

	//for computing velocity
	deque<ofPoint> rHandPosHist;
	deque<ofPoint> lHandPosHist;

	deque<ofPoint> rKneePosHist;
	deque<ofPoint> lKneePosHist;

	//positioning variable
	int positionDetectedCounter;
	ofXml XML;

	float maxTrackingDistance = 3.0;
#if ENABLE_REMOTE_KINECT
	ofxOscReceiver receiver;
#endif
};

#endif /* PMMotionExtractor_hpp */