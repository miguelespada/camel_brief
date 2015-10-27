#include "app.h"
#include "infoState.h"

App::App():BaseApp(){
    for(int i = 0; i < N; i++)
        values.push_back(0);
    
    for(vector<int>::iterator it = values.begin(); it != values.end(); ++it)
        (*it) = 0;

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
    if(idx == 1) {
        values.push_back(v);
        if(values.size() > N)
            values.erase(values.begin());
    }
    
    
}

void App::pushButton(){
    current_state->start();
}

void App::drawValues(){
    ofPushStyle();
    ofSetColor(255, 0, 0);
    int i = 0;
    for(vector<int>::iterator it = values.begin() + 1; it != values.end(); ++it){
        float v0 = (* (it - 1));
        float v1 = (*it);
        
        v1 = ofMap(v1, 0, 1024, 0, ofGetHeight());
        v0 = ofMap(v0, 0, 1024, 0, ofGetHeight());
        
        ofLine(i, v0, i+1, v1);
        i++;
    }
    
    ofPopStyle();
}
