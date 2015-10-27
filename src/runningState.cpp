#include "runningState.h"
#include "standbyState.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
};

RunningState::~RunningState(){
};

void RunningState::draw(){
    ofPushMatrix();
    ofClear(255, 255, 0);
    ofPopMatrix();
};

void RunningState::update(){
};

void RunningState::next(){
    
    app->setCurrentState(new StandbyState(app));
    delete this;
};
