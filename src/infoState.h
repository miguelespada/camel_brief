
#ifndef __info__state__
#define __info__state__

#include "baseState.h"
#include "app.h"

class InfoState: public BaseState
{
    
public:
    InfoState(App *a);
    ~InfoState();
    std::string toString() { return "info"; }
    void update();
    void draw();
    void next();
};

#endif