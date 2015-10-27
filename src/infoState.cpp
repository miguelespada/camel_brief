#include "infoState.h"
#include "standByState.h"

InfoState::InfoState(App *a):BaseState(a){
    BaseState::initialize();
};

InfoState::~InfoState(){
};


void InfoState::draw(){
    ofPushMatrix();
    ofTranslate(20, 40);
    ofSetColor(255, 0, 0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    app->drawValues();
    ofPopMatrix();
};

void InfoState::update(){
    if(app->isHit()){
        cout << "YEAH!" << endl;
    }
};

void InfoState::next(){
    app->setCurrentState(new StandbyState(app));
    delete this;
};
