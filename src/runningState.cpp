#include "runningState.h"
#include "standbyState.h"
#include "winnerState.h"
#include "assets.h"

RunningState::RunningState(App *a):BaseState(a){
    BaseState::initialize();
    app->reset();
    Assets::getInstance()->sound.play();
    Assets::getInstance()->sound.setLoop(true);
    
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
    
    Assets::getInstance()->sound.stop();
    app->setCurrentState(new WinnerState(app));
    delete this;
};

void RunningState::reset(){
    Assets::getInstance()->sound.stop();
    app->setCurrentState(new StandbyState(app));
    delete this;
}
