#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include <math.h>

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofImage				bgImage;
	ofImage				logoImage;
	ofTrueTypeFont		font;
    ofTrueTypeFont      smallFont;
    ofTrueTypeFont      bigFont;
	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once

    //Player control
    int treshold1;                      //int value behind we consider a hit
    int treshold2;
    float darkTime, darkIniP1, darkIniP2;   //dark timer, global and per player
    bool isDarkP1, isDarkP2;            //boolean that control, whith te darkIni, a new posible hit.
    int pointsP1, pointsP2;
    bool simP1, simP2;                  //Simulated hit by keyboard
    float xCoord;                       //max y coord of rect
    float scale;
    int sign;
    enum gameScreen { waitingArduino, attrackMode, inGame, gameOver, debug};
    gameScreen actualScreen;
    float timeButton;
    bool p1GetPoint, p2GetPoint;
    int pointDesp;

    void restartGame();
private:

    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();

    string buttonState;
    string potValue;

};

