//
//  PMColorsSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMColorsSelector.hpp"


static const int NUM_ERASED_COLORS = 2; //for debuging purposes

void PMColorsSelector::init(ofTrueTypeFont &font)
{
    originalWidth=1080;
    originalHeight=1920;
    
    indexChoosed=0;
    
    json.open("colors/Colors.json");
    for(int i=0; json["Colors"][i]["Name"].asString()!=""; i++){
        tempPalette.name=json["Colors"][i]["Name"].asString();
        for(int j=1; j<=5; j++){
            ofColor tempColor=ofColor::fromHex(ofHexToInt(json["Colors"][i][ofToString(j)].asString()));
            tempPalette.colors.push_back(tempColor);
        }
        colorPalettes.push_back(tempPalette);
        tempPalette.colors.clear();
    }
    
    int rows=colorPalettes.size()-NUM_ERASED_COLORS;
    int columns=colorPalettes[0].colors.size();
    int x,y;
    int width,height;
    for(int i=0; i<rows; i++){
        y=(((originalHeight-150)*(i+1)/((rows)+1))+150);
        for(int j=0; j<columns; j++){
            x=(originalWidth*(j+1)/(columns+1));
            width=((originalWidth/(columns*2))-1);
            height=width;
            PMColorContainer tempContainer(x, y, width, height, colorPalettes[i].colors[j]);
            colorContainers.push_back(tempContainer);
        }
    }
    for(int i=0; i<colorContainers.size(); i=i+colorPalettes[0].colors.size()){
        int x=originalWidth/2;
        int y=colorContainers[i].getY()+20;
        int width=originalWidth-(2*colorContainers[i].getX()-colorContainers[i].getWidth())+20;
        int height=colorContainers[i].getHeight()+60;
        rectSelector.push_back(PMColorContainer(x, y, width, height, ofColor(127)));
    }
    
    for(int i=0; i<colorContainers.size(); i=i+colorPalettes[0].colors.size()){
        int x=originalWidth/2;
        int y=colorContainers[i].getY()+20+colorContainers[i].getHeight()/2;
        paletteNames.push_back(PMTextContainer(x, y, colorPalettes[i/colorPalettes[0].colors.size()].name, font));
    }
                               
                               
}

void PMColorsSelector::update()
{
    
}

void PMColorsSelector::draw()
{
    for(int i=0; i<rectSelector.size(); i++){
        rectSelector[i].draw();
    }

    for(int i=0; i<colorContainers.size(); i++){
        colorContainers[i].draw();
    }
    
    for(int i=0; i<paletteNames.size(); i++){
        paletteNames[i].draw();
    }

}

void PMColorsSelector::checkMousePassed(int x, int y)
{
    for(int i=0; i<rectSelector.size(); i++){
        int x1=rectSelector[i].getX()-rectSelector[i].getWidth()/2;
        int x2=rectSelector[i].getX()+rectSelector[i].getWidth()/2;
        int y1=rectSelector[i].getY()-rectSelector[i].getHeight()/2;
        int y2=rectSelector[i].getY()+rectSelector[i].getHeight()/2;
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
        }else{
        }
    }
}

bool PMColorsSelector::checkMousePressed(int x, int y)
{
    for(int i=0; i<rectSelector.size(); i++){
        int x1=rectSelector[i].getX()-rectSelector[i].getWidth()/2;
        int x2=rectSelector[i].getX()+rectSelector[i].getWidth()/2;
        int y1=rectSelector[i].getY()-rectSelector[i].getHeight()/2;
        int y2=rectSelector[i].getY()+rectSelector[i].getHeight()/2;
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            indexChoosed=i;
            return true;
        }
    }
    return false;
}
