
#ifndef __standby__state__
#define __standby__state__

#include "baseState.h"
#include "app.h"

class StandbyState: public BaseState
{
    
public:
    StandbyState(App *a);
    ~StandbyState();
    std::string toString() { return "stand by"; }
    void update();
    void draw();
    void next();
    void start();
    void reset();
    int r;
    int state;
    int x,y;
    void resetCircle();
};

#endif