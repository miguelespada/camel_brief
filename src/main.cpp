#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(800,600, OF_WINDOW);			// <-------- setup the GL context
    #ifdef TARGET_RASPBERRY_PI
        system("sudo amixer cset numid=3 1");
    #endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
