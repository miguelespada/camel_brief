//
//  player.cpp
//  camel_brief
//
//  Created by miguel on 27/10/15.
//
//

#include "player.h"
#include "assets.h"


Player::Player(){
    for(int i = 0; i < N; i++)
        values.push_back(0);
    
    for(vector<int>::iterator it = values.begin(); it != values.end(); ++it)
        (*it) = 0;
    
    bBallOn = false;
    ballOnTime = ofGetElapsedTimeMillis();
    
    threshold = Assets::getInstance()->getThreshold();
    score = 0;
}

void Player::addValue(int v){
    values.push_back(v);
    if(values.size() > N)
        values.erase(values.begin());
    
    int last = values[N - 1];
    int prev = values[N - 2];
    
    if(last < threshold && prev > threshold){
        bBallOn = true;
        ballOnTime = ofGetElapsedTimeMillis();
    }
    if(last > threshold && prev < threshold){
        bBallOn = false;
    }
}


bool Player::isHit(){
    if(bBallOn && ofGetElapsedTimeMillis() > ballOnTime + 100){
        bBallOn = false;
        updateScore();
        return true;
    }
    return false;
}


void Player::drawValues(){    int i = 0;
    for(vector<int>::iterator it = values.begin() + 1; it != values.end(); ++it){
        float v0 = (* (it - 1));
        float v1 = (*it);
        
        v1 = ofMap(v1, 0, 1024, 0, ofGetHeight());
        v0 = ofMap(v0, 0, 1024, 0, ofGetHeight());
        
        ofLine(i, v0, i+1, v1);
        i++;
    }
    
}

void Player::drawThreshold(){
    float t = ofMap(threshold, 0, 1024, 0, ofGetHeight());
    ofLine(0, t, ofGetWidth(), t);
}

void Player::drawLastValue(){
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    font->drawString(ofToString((*values.end())), 0, 0);
}

void Player::updateScore(){
    score += 1;
}

void Player::draw(){
    ofTrueTypeFont *font = Assets::getInstance()->getFont(30);
    font->drawString(ofToString(score), 0, 0);
    
}