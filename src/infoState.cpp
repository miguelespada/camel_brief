#include "infoState.h"
#include "standbyState.h"

InfoState::InfoState(App *a):BaseState(a){
    BaseState::initialize();
};

InfoState::~InfoState(){
};


void InfoState::draw(){
    ofClear(0);
    ofPushMatrix();
    ofTranslate(20, 40);
    ofSetColor(255, 0, 0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    
    
    ofSetColor(255, 0, 255);
    app->player_0.drawValues();
    
    ofSetColor(0, 255, 255);
    app->player_1.drawValues();
    
    ofSetColor(255);
    app->player_1.drawThreshold();
    ofPopMatrix();
};

void InfoState::update(){
    
};

void InfoState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};

void InfoState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}