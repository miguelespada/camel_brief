#include "arduino.h"
#include "assets.h"

#define SHORT_PUSH_TIME 50
#define LONG_PUSH_TIME 1000

Arduino::Arduino(App *a){
    app = a;
    ofLogNotice() << "[Arduino of RASP]" << Assets::getInstance()->getArduino();
    #ifdef TARGET_RASPBERRY_PI
        ard.connect(Assets::getInstance()->getArduino(), 57600);
    #else
        ard.connect("/dev/tty.usbmodem1411", 57600);//57600);
    #endif
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &Arduino::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    ofAddListener(ofEvents().update, this, &Arduino::update);

    bButton = 1;
}


//--------------------------------------------------------------
void Arduino::update(ofEventArgs &args){
    ard.update();
}


//--------------------------------------------------------------
void Arduino::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &Arduino::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    ard.sendDigitalPinMode(2, ARD_INPUT);  // pin 21 if using StandardFirmata from Arduino 0022 or older
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    ard.sendDigital(2, ARD_HIGH);
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    
    ofAddListener(ard.EDigitalPinChanged, this, &Arduino::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &Arduino::analogPinChanged);

}

//--------------------------------------------------------------
void Arduino::digitalPinChanged(const int & pinNum) {
    cout << ard.getDigital(pinNum) << endl;
    if(pinNum == 2){
        int v = ard.getDigital(pinNum);
        if(bButton == 0 && v == 1){
            if(ofGetElapsedTimeMillis() > pressedTime + LONG_PUSH_TIME) {
                cout << "Long push" << endl;
                app->longPushButton();
            }
            else if(ofGetElapsedTimeMillis() > pressedTime + SHORT_PUSH_TIME){
                cout << "Short push" << endl;
                app->pushButton();
            }
        }
        
        
        if(bButton == 1 && v == 0){
            pressedTime = ofGetElapsedTimeMillis();
        }
        bButton = v;
        
    }
    
}


//--------------------------------------------------------------
void Arduino::analogPinChanged(const int & pinNum) {
    
    cout << ard.getAnalog(pinNum) << endl;
    
    app->set(pinNum, ard.getAnalog(pinNum));
 }
