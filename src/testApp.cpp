#include "testApp.h"
#include "standbyState.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(30);

    ofLogNotice() << "Running app";
    
    
    app.setCurrentState(new StandbyState(&app));
    
    arduino = new Arduino(&app);
    ofHideCursor();
    ofSetFullscreen(true);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    app.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch (key) {
        case 'f':
            setFullScreen(true);
            break;
        case 'F':
            setFullScreen(false);
            break;
            
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  }

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

void testApp::setFullScreen(bool bFull){
    if(bFull){
        ofSetFullscreen(true);
        ofSetWindowPosition(1440, 0);
        ofHideCursor();
    }
    else{
        ofSetFullscreen(false);
        ofSetWindowPosition(0, 0);
    }
    
}
