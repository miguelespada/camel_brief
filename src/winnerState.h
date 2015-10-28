
#ifndef __winner__state__
#define __winner__state__

#include "baseState.h"
#include "app.h"

class WinnerState: public BaseState
{
    
public:
    WinnerState(App *a);
    ~WinnerState();
    std::string toString() { return "stand by"; }
    void update();
    void draw();
    void next();
    void start();
};

#endif