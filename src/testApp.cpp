#include "testApp.h"
#include "standbyState.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	//ofSetFrameRate(60);

    ofLogNotice() << "Running app";
    
    
    app.setCurrentState(new StandbyState(&app));
    
    arduino = new Arduino(&app);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofClear(0);
    app.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

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
