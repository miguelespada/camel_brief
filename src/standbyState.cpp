#include "standbyState.h"
#include "runningState.h"
#include "infoState.h"

StandbyState::StandbyState(App *a):BaseState(a){
    BaseState::initialize();
    state = 0;
    resetCircle();
};

StandbyState::~StandbyState(){
};

void StandbyState::draw(){
    
    if(state == 0){
        ofClear(app->player_0.color);
        ofSetColor(app->player_1.color);
    }
    else{
        ofClear(app->player_1.color);
        ofSetColor(app->player_0.color);
    }
    
    ofSetCircleResolution(200);
    ofCircle(x, y, r);
    r *= 1.12;
    
    if(r > ofGetHeight() * 2){
        state = (state + 1 ) % 2;
        resetCircle();
    }
    
    
    
    ofTrueTypeFont *font;
    string s = "PRESS BUTTON TO PLAY";
    
    if(state == 0){
        ofSetColor(app->player_1.color);
    }
    else{
        ofSetColor(app->player_0.color);
    }
    
    font = Assets::getInstance()->getFont(30 * 3);
    
    font->drawString(s, ofGetWidth()/2 - (font->stringWidth(s)/2),
                     (ofGetHeight()/2) + (font->stringHeight(s)/2));
};
void StandbyState::resetCircle(){
    r = 10;
    
    if(ofRandom(1) > 0.5){
        x = ofRandom(ofGetWidth());
        y = ofRandom(-40, 40);
        if( y < 0) y = ofGetHeight() - y;
    }
    else{
        y = ofRandom(ofGetHeight());
        x = ofRandom(-40, 40);
        if( x < 0) y = ofGetWidth() - y;
    }
    
}
void StandbyState::update(){
};

void StandbyState::next(){
    app->setCurrentState(new RunningState(app));
    delete this;
};

void StandbyState::start(){
    next();
}


void StandbyState::reset(){
    app->setCurrentState(new InfoState(app));
    delete this;
}
