#include "runningState.h"
#include "standbyState.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
};

RunningState::~RunningState(){
};

void RunningState::draw(){
    ofPushMatrix();
    ofTranslate(20, 40);
    ofSetColor(255, 0, 0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    font->drawString(ofToString(app->value), 0, 0);
    
    ofPopMatrix();
};

void RunningState::update(){
};

void RunningState::next(){
    
    app->setCurrentState(new StandbyState(app));
    delete this;
};
