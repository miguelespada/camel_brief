//
//  arduino.h
//  camel_brief
//
//  Created by miguel on 23/10/15.
//
//

#ifndef __camel_brief__arduino__
#define __camel_brief__arduino__


#include "ofMain.h"
#include "app.h"

class Arduino {
    ofArduino	ard;
    bool		bSetupArduino;			// flag variable for setting up arduino once
    
    App *app;
    
public:
    Arduino(App *a);
    ~Arduino();
    
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    void update(ofEventArgs &args);
    
};

#endif /* defined(__camel_brief__arduino__) */
