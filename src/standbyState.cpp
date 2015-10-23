#include "standbyState.h"
#include "runningState.h"

StandbyState::StandbyState(App *a):BaseState(a){
    BaseState::initialize();
};

StandbyState::~StandbyState(){
};

void StandbyState::draw(){
    ofClear(0, 255, 0);
    ofPushMatrix();
    ofTranslate(20, 40);
    ofPopMatrix();
};

void StandbyState::update(){
};

void StandbyState::next(){
    app->setCurrentState(new RunningState(app));
    delete this;
};
