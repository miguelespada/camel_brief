#include "standbyState.h"
#include "winnerState.h"

WinnerState::WinnerState(App *a):BaseState(a){
    BaseState::initialize();
};

WinnerState::~WinnerState(){
};

void WinnerState::draw(){
    app->drawWiinner();
};

void WinnerState::update(){
    if(isDone(5))
        next();
};

void WinnerState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};

void WinnerState::start(){
    next();
}


