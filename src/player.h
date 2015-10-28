//
//  player.h
//  camel_brief
//
//  Created by miguel on 27/10/15.
//
//

#ifndef __camel_brief__player__
#define __camel_brief__player__

#define N 100

#include "ofMain.h"

class Player
{
    
public:
    Player();
    void addValue(int v);
    
    vector<int> values;
    void draw();
    void drawValues();
    void drawLastValue();
    void drawThreshold();
    
    bool bBallOn;
    float ballOnTime;
    bool isHit();
    int threshold;

    ofColor color;
};


#endif /* defined(__camel_brief__player__) */
