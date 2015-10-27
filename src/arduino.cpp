#include "arduino.h"

Arduino::Arduino(App *a){
    app = a;
    
    #ifdef TARGET_RASPBERRY_PI
        ard.connect("/dev/ttyACM0", 57600);
    #else
        ard.connect("tty.usbmodem1451", 57600);//57600);
    #endif
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &Arduino::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    ofAddListener(ofEvents().update, this, &Arduino::update);

    bButton = 0;
    time = ofGetElapsedTimeMillis();
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
    
    if(pinNum == 2){
        int v = ard.getDigital(pinNum);
        if(bButton == 1 && v == 0 && ofGetElapsedTimeMillis() > time + 500){
            app->pushButton();
        }
        time = ofGetElapsedTimeMillis();
        bButton = v;
        
    }
    
}


//--------------------------------------------------------------
void Arduino::analogPinChanged(const int & pinNum) {
    app->set(pinNum, ard.getAnalog(pinNum));
 }
