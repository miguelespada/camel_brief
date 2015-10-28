#include "runningState.h"
#include "standbyState.h"
#include "winnerState.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
    app->reset();
};

RunningState::~RunningState(){
};

void RunningState::draw(){
    ofPushMatrix();
    app->drawScore();
    ofPopMatrix();
};

void RunningState::update(){
    app->updatePlayers();
};

void RunningState::next(){
    app->setCurrentState(new WinnerState(app));
    delete this;
};

void RunningState::reset(){
    app->setCurrentState(new StandbyState(app));
    delete this;
}
