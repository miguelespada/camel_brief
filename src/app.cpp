#include "app.h"

App::App():BaseApp(){
    value = 0;
}


void App::keyPressed (int key){
    switch (key) {
        case 'n':
            current_state->next();
            break;
        case 'c':
            Assets::getInstance()->testSound.play();
            break;
        
        default:
            break;
    }
}

void App::set(int idx, int v){
    if(idx == 0) value = v;
    
}

void App::pushButton(){
    current_state->start();
}
