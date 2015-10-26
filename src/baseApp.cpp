#include "baseApp.h"


BaseApp::BaseApp(){
    
    ofLogNotice() << "Initializing app...";
    
    assets = (Assets *)Assets::getInstance();
    
    // Register events and actions
    ofAddListener(ofEvents().keyPressed, this, &BaseApp::keyPressed);
    ofAddListener(ofEvents().update, this, &BaseApp::update);
    
    current_state = NULL;
    
    
}

void BaseApp::setCurrentState(BaseState *s){
    current_state = s;
}

void BaseApp::next(){
    if(current_state)
        current_state->next();
}


void BaseApp::update(){
    if(current_state)
        current_state->update();
}

void BaseApp::update(ofEventArgs &args){
    update();
}

void BaseApp::keyPressed (ofKeyEventArgs& eventArgs){
    keyPressed(eventArgs.key);
}

void BaseApp::draw(){
    ofPushStyle();
    ofPushMatrix();
    
    ofSetWindowShape( assets->getWidth() * assets->getScale(),  assets->getHeight() * assets->getScale());
    ofScale(assets->getScale(), assets->getScale());
    
    if(current_state)
        current_state->draw();
    ofPopMatrix();
    ofPopStyle();
}

Assets * BaseApp::getAssets(){
    return assets;
}