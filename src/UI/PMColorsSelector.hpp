//
//  PMColorsSelector.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMColorsSelector_hpp
#define PMColorsSelector_hpp

#include <stdio.h>
#include "ofMain.h"
#include "PMColorContainer.hpp"
#include "PMTextContainer.hpp"
#include "ofxJSON.h"

struct colorPalette{
    string name;
    vector <ofColor> colors;
};

class PMColorsSelector
{
public:
    
    static PMColorsSelector &getInstance()
    {
        static PMColorsSelector instance;
        return instance;
    }
    
    void init(ofTrueTypeFont &font);
    void update();
    void draw();
    
    ofColor getColor(int layer){return colorPalettes[indexChoosed].colors[layer];};
    void checkMousePassed(int x, int y);
    bool checkMousePressed(int x, int y);
    
private:
    vector<PMColorContainer > colorContainers;
    ofxJSONElement  json;
    vector<colorPalette> colorPalettes;
    colorPalette tempPalette;
    vector<PMColorContainer > rectSelector;
    vector<PMTextContainer > paletteNames;
    int originalWidth, originalHeight;
    
    int indexChoosed;
};

#endif /* PMColorsSelector_hpp */
