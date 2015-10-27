#include "app.h"
#include "infoState.h"



App::App():BaseApp(){

}


void App::keyPressed (int key){
    switch (key) {
        case 'n':
            current_state->next();
            break;
        case 'c':
            Assets::getInstance()->testSound.play();
            break;
            
        case 'i':
            setCurrentState(new InfoState(this));
            break;
            
        default:
            break;
    }
}

void App::set(int idx, int v){
    if(idx == 0)
        player_0.addValue(v);
    
    if(idx == 1)
        player_1.addValue(v);
    
}

void App::pushButton(){
    current_state->start();
}

void App::updatePlayers(){
    player_0.isHit();
    player_1.isHit();
}


