#include "runningState.h"
#include "standbyState.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
};

RunningState::~RunningState(){
};

void RunningState::draw(){
    ofPushMatrix();
    ofClear(255);
    ofSetColor(255, 0, 0);
    ofTranslate(20, 20);
    app->player_0.draw();
    ofSetColor(0, 255, 0);
    ofTranslate(0, 100);
    app->player_1.draw();
    ofPopMatrix();
};

void RunningState::update(){
    app->updatePlayers();
};

void RunningState::next(){
    
    app->setCurrentState(new StandbyState(app));
    delete this;
};
