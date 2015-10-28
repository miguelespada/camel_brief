#include "app.h"
#include "infoState.h"
#include "infoState.h"



App::App():BaseApp(){
    player_0.color = ofColor(0, 0, 255);
    player_1.color = ofColor(255);
    reset();
    
    SPEED = Assets::getInstance()->getSpeed();
    DECAY = Assets::getInstance()->getDecay();
}

void App::reset(){
    score = 50;
    inc = 0;
    
}

void App::keyPressed (int key){
    switch (key) {
        case 'n':
            current_state->next();
            break;
        case 'c':
            Assets::getInstance()->hitSound.play();
            break;
            
        case 'i':
            setCurrentState(new InfoState(this));
            break;
            
        case '1':
            inc = SPEED;
            Assets::getInstance()->hitSound.play();
            break;
            
        case '2':
            inc = -SPEED;
            Assets::getInstance()->hitSound.play();
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

void App::longPushButton(){
    current_state->reset();
}

void App::updatePlayers(){
    if(inc > 0){
        score ++;
        inc -= 2;
    }
    if(inc < 0){
        score --;
        inc += 2;
    }
    
    if(score > 100 || score < 0){
        current_state->next();
    }
        
    
    if(score > 51){
        score *= DECAY;
    }
    else if (score < 49){
        score = 100 - (100 - score) * DECAY;
    }
    
    if(score > 50 && score < 51)
        score = 50;
    
    if(score > 49 && score < 50)
        score = 50;
    
    if(player_0.isHit()){
        inc = SPEED;
    }
    if(player_1.isHit()){
        inc = -SPEED;
    }
}

void App::drawScore(){
    
    ofTrueTypeFont *font;
    
    ofPushStyle();
    ofClear(player_1.color);
    
    ofSetColor(player_0.color);
    ofRect(0, 0, ofGetWidth() * score / 100., ofGetHeight());
    
    ofSetColor(player_1.color);
    font = Assets::getInstance()->getFont(int(score) * 3);
    
    string s = ofToString(int(score));
    int pos = ofMap(score, 0, 100, 0, ofGetWidth()) / 2;
    font->drawString(s, pos - (font->stringWidth(s)/2),
                     (ofGetHeight()/2) + (font->stringHeight(s)/2) );

    
    ofSetColor(player_0.color);
    font = Assets::getInstance()->getFont(int(100 - score) * 3);
    s = ofToString(int(100 - score));
    
    pos = ofGetWidth() - ofMap(100 - score, 0, 100, 0, ofGetWidth()) / 2;
    font->drawString(s, pos - (font->stringWidth(s)/2),
                     (ofGetHeight()/2) + (font->stringHeight(s)/2));
    
    
    ofSetColor(player_1.color);
    font->drawString(ofToString(score), 0, 0);
    ofPopStyle();
}

void App::drawWiinner(){
    
    ofTrueTypeFont *font;
    string s;
    
    if(score > 50){
        ofClear(player_0.color);
        ofSetColor(player_1.color);
        s = "PLAYER 1 WINS!";
    }
    else{
        ofClear(player_1.color);
        ofSetColor(player_0.color);
        s = "PLAYER 2 WINS!";
    }
    
    font = Assets::getInstance()->getFont(30 * 3);
    
    font->drawString(s, ofGetWidth()/2 - (font->stringWidth(s)/2),
                     (ofGetHeight()/2) + (font->stringHeight(s)/2));
}
