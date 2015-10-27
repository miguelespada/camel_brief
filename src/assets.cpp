#include "assets.h"

void Assets::loadAssets(){
    testSound.loadSound("Skid.wav");
}


int Assets::getThreshold(){
    return getData("threshold").asInt();
}