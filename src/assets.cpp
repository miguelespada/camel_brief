#include "assets.h"

void Assets::loadAssets(){
    hitSound.loadSound("Skid.wav");
}

int Assets::getThreshold(){
    return getData("threshold").asInt();
}

int Assets::getSpeed(){
    int s = getData("speed").asInt();
    if( s % 2 == 1)
        s ++;
    return s;
}

float Assets::getDecay(){
    return getData("decay").asFloat();
}