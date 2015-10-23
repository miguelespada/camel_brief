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
    ofAddListener(ard.EDigitalPinChanged, this, &Arduino::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &Arduino::analogPinChanged);

}

//--------------------------------------------------------------
void Arduino::digitalPinChanged(const int & pinNum) {
     cout << "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum)) << endl;
}


//--------------------------------------------------------------
void Arduino::analogPinChanged(const int & pinNum) {
    app->set(pinNum, ard.getAnalog(pinNum));
 }
