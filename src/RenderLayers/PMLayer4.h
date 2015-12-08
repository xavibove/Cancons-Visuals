//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER4_H
#define PMCANCONS_VISUALS_PMLAYER4_H

#include "PMBaseLayer.h"

//static const int MARGIN = -50;
//static const int INITIAL_SHAKE_SPEED = 30;
//static const float SPEED_DECREMENT = 0.3;
//static const int SIZE_DECREMENT = 1;
//static const int INITIAL_SHAKE_SIZE = BRUSH_MAX_SIZE*4;
//static const int    DIR_HISTORY_SIZE = 10;

class PMLayer4 : public PMBaseLayer
{
public:

    PMLayer4(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup(ofPoint initialPosition);
    void update();
    void draw();

    //Audio listeners
    void pitchChanged(pitchParams &pitchParams) override;
    void energyChanged(energyParams &energyParams) override;
    void silenceStateChanged(silenceParams &silenceParams) override;
    void pauseStateChanged(pauseParams &_auseParams) override;
    void onsetDetected(onsetParams &onsetParams) override;
    void shtDetected(shtParams &shtParams) override;
    void melodyDirection(melodyDirectionParams &melodyDirectionParams) override;
    void melBandsChanged(melBandsParams &melBandsParams) override;
    
private:
    bool didShake;
    float       beginShakeTime;
    deque<ofPoint> directionHistory;
};


#endif //PMCANCONS_VISUALS_PMLAYER4_H
