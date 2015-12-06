//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER1_H
#define PMCANCONS_VISUALS_PMLAYER1_H

#include "PMBaseLayer.h"

class PMLayer1 : public PMBaseLayer
{
public:

    PMLayer1(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);
    
    void setup();
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
};


#endif //PMCANCONS_VISUALS_PMLAYER1_H