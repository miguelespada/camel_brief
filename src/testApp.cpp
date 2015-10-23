/*
 * This is a simple example use of ofArduino
 *
 * ofArduino currently only supports the standard Arduino boards
 * (UNO, Duemilanove, Diecimila, NG, and other boards based on the
 * ATMega168 or ATMega328 microcontrollers
 * The Arduio FIO and Arduino Mini should also work.
 * The Arduino MEGA and other variants based on microcontrollers
 * other than the ATMega168 and ATMega328 are not currently supported.
 *
 * To use this example, open Arduino (preferably Arduino 1.0) and
 * navigate to File -> Examples -> Firmata and open StandardFirmata.
 * Compile and upload StandardFirmata for your board, then close
 * the Arduino application and run this application.
 *
 * If you have a servo attached, press the left arrow key to rotate
 * the servo head counterclockwise and press the right arrow key to
 * rotate the servo head clockwise.
 *
 * Clicking the mouse over any part of the application will turn the
 * on-board LED on and off.
 *
 */

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	//ofSetFrameRate(60);

	ofBackground(255,0,130);

    buttonState = "digital pin:";
    potValue = "analog pin:";

	bgImage.loadImage("background.png");
	logoImage.loadImage("logo.png");
	logoImage.setAnchorPercent(0.5, 0.5);
	font.loadFont("franklinGothic.otf", 20);
    smallFont.loadFont("franklinGothic.otf", 14);
    bigFont.loadFont("franklinGothic.otf", 200);

    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
	//ard.connect("/dev/tty.usbmodemfd121", 57600);
	#ifdef TARGET_RASPBERRY_PI
	ard.connect("/dev/ttyACM0", 57600);
	#else
	ard.connect("COM8", 57600);//57600);
    #endif
	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
	treshold1 = 80;
	treshold2 = treshold1;
	darkTime = 0.75;
	darkIniP1 = 0.f;
	darkIniP2 = 0.f;
	isDarkP1 = false;
	isDarkP2 = false;
	pointsP1 = 0;
	pointsP2 = 0;
	actualScreen = waitingArduino;
	xCoord = ofGetViewportWidth()/2;
	scale=0.1;
	sign = 1;
	p1GetPoint = false;
	p2GetPoint = false;
	timeButton = 0.f;
	pointDesp = 64;
}

//--------------------------------------------------------------
void testApp::update(){

	updateArduino();
	if (p1GetPoint){xCoord=xCoord+pointDesp;p1GetPoint=false;cout<<"Punto del player 1";}
	if (p2GetPoint){xCoord=xCoord-pointDesp;p2GetPoint=false;cout<<"Punto del player 2";}
	if (xCoord<0 || xCoord>ofGetViewportWidth()){actualScreen = gameOver;}
}

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {

	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);

    // it is now safe to send commands to the Arduino
    bSetupArduino = true;

    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)

    // set pins D2 and A5 to digital input
    ard.sendDigitalPinMode(0, ARD_INPUT);
    ard.sendDigitalPinMode(19, ARD_INPUT);  // pin 21 if using StandardFirmata from Arduino 0022 or older

    // set pin A0 to analog input
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    // set pin A1 to analog input
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    // set pin D13 as digital output
	ard.sendDigitalPinMode(13, ARD_OUTPUT);
    // set pin D12 as digital output
	ard.sendDigitalPinMode(12, ARD_OUTPUT);
    // set pin A4 as digital output
    //ard.sendDigitalPinMode(18, ARD_OUTPUT);  // pin 20 if using StandardFirmata from Arduino 0022 or older

    // set pin D11 as PWM (analog output)
	//ard.sendDigitalPinMode(11, ARD_PWM);

    // attach a servo to pin D9
    // servo motors can only be attached to pin D3, D5, D6, D9, D10, or D11
    //ard.sendServoAttach(9);

    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
    actualScreen = attrackMode;
}

//--------------------------------------------------------------
void testApp::updateArduino(){

	// update the arduino, get any data or messages.

    // the call to ard.update() is required
	ard.update();
    p1GetPoint = false;
    p2GetPoint = false;
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // fade the led connected to pin D11

		ard.sendPwm(13, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...

		if (isDarkP1 && (ofGetElapsedTimef() > darkIniP1+darkTime)){isDarkP1=false;}
        if (isDarkP2 && (ofGetElapsedTimef() > darkIniP2+darkTime)){isDarkP2=false;}

		if ((ard.getAnalog(0)<treshold1 || simP1) && !isDarkP1){
            darkIniP1 = ofGetElapsedTimef();
            isDarkP1 = true;
            pointsP1++;
            p1GetPoint = true;
            simP1=false;
		}

        if ((ard.getAnalog(1)<treshold2 || simP2) && !isDarkP2){
            darkIniP2 = ofGetElapsedTimef();
            isDarkP2 = true;
            pointsP2++;
            p2GetPoint=true;
            simP2=false;
        }
	}
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
    //cout << "DIGITAL: "<<ofToString(ard.getDigital(0))<<"\n";
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    //cout << ofToString(pinNum) <<": "<< ofToString(ard.getAnalog(pinNum))<<"\n";
    //cout << ofToString(ard.getAnalog(0))<<" - "<<ofToString(ard.getAnalog(1))<<"\n";
}


//--------------------------------------------------------------
void testApp::draw(){
    string text;
    float fontWidth;
    switch(actualScreen){
        case waitingArduino:
            ofBackground(255,255,255);
            //bgImage.draw(4*ofGetViewportHeight()/3 , ofGetViewportWidth()/2);
            logoImage.draw(ofGetViewportWidth()/2, 0.3*ofGetViewportHeight());
            ofPushMatrix();
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofScale(1, 1, 1);
                text = "Waiting Arduino";
                fontWidth = font.stringWidth(text);
                ofSetColor(0, 0, 0);
                font.drawString(text, -fontWidth/2, 0);
            ofPopMatrix();
            break;
        case attrackMode:
            ofBackground(255,255,255);
            ofSetColor(0, 0, 255);
             ofPushMatrix();
                //cout<<scale<<"\n";
                if (scale>0.4 && sign==1){sign=-1;}
                else if (scale<0.25 && sign==-1){sign=1;}
                scale=scale+ sign*.0002;
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofRotate(scale/2,0.0,0.0,1.0);
                ofScale(scale, scale, 1);
                text = "Play The Game";
                fontWidth = bigFont.stringWidth(text);
                ofSetColor(0, 0, 0);
                bigFont.drawString(text, -fontWidth/2, 0);
            ofPopMatrix();
            break;
        case inGame:
            ofBackground(255,255,255);
            ofSetColor(0, 0, 255);
            ofRect(0,0,xCoord,ofGetViewportWidth());
            break;
        case gameOver:
            ofBackground(255,255,255);
            ofSetColor(0, 0, 255);
             ofPushMatrix();
                //cout<<scale<<"\n";
                if (scale>0.4 && sign==1){sign=-1;}
                else if (scale<0.25 && sign==-1){sign=1;}
                scale=scale+ sign*.0002;
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofRotate(scale*10,0.0,0.0,1.0);
                ofScale(scale, scale, 1);
                int winner;
                winner = 2;
                if (pointsP1>pointsP2){winner = 1;}
                text = "  GAME OVER\nWIN PLAYER "+ofToString(winner);
                fontWidth = bigFont.stringWidth(text);
                ofSetColor(0, 0, 0);
                bigFont.drawString(text, -fontWidth/2, 0);
            ofPopMatrix();
            break;
            break;
        case debug:
           	bgImage.draw(0,0);

            ofEnableAlphaBlending();
            ofSetColor(0, 0, 0, 127);
            ofRect(510, 15, 275, 150);
            ofDisableAlphaBlending();

            ofSetColor(255, 255, 255);
            if (!bSetupArduino){
                font.drawString("arduino not ready...\n", 515, 40);
            } else {
                font.drawString(potValue + "\n" + buttonState ,515,40);//+
                                //"\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);

                ofSetColor(64, 64, 64);
                smallFont.drawString("If a servo is attached, use the left arrow key to rotate "
                                     "\ncounterclockwise and the right arrow key to rotate clockwise.", 200, 550);
                ofSetColor(0, 0, 0);
                smallFont.drawString("P1 Sensor: "+ofToString(ard.getAnalog(0))+"| Points: "+ofToString(pointsP1),500,200);
                smallFont.drawString("P2 Sensor: "+ofToString(ard.getAnalog(1))+"| Points: "+ofToString(pointsP2),500,250);

                ofSetColor(255, 255, 255);
            }

            break;

    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch (key) {
        case OF_KEY_F1:
           ard.sendDigital(13, ARD_HIGH);
           break;
        case OF_KEY_F2:
           ard.sendDigital(12, ARD_HIGH);
           break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_F3:
            ard.sendDigital(13, ARD_LOW);
            break;
        case OF_KEY_F4:
            ard.sendDigital(12, ARD_LOW);
            break;
        case OF_KEY_F11:
            simP1=true;
            break;
        case OF_KEY_F12:
            simP2=true;
            break;
        case OF_KEY_F5:
            if (actualScreen !=  debug){
                    actualScreen=debug;
            }else {actualScreen = attrackMode;}
            break;
        case OF_KEY_F1:
            restartGame();
            actualScreen = inGame;
            break;
        case OF_KEY_F2:
            restartGame();
            actualScreen = gameOver;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    // turn on the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_HIGH);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    // turn off the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_LOW);
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

void testApp::restartGame(){
	pointsP1 = 0;
	pointsP2 = 0;
	p1GetPoint = false;
	p2GetPoint = false;
	actualScreen = inGame;
	scale=0.1;
	sign = 1;
	xCoord = ofGetViewportWidth()/2;
}
