
#ifndef __running__state__
#define __running__state__

#include "baseState.h"
#include "app.h"

class RunningState: public BaseState
{
    
public:
    RunningState(App *a);
    ~RunningState();
    std::string toString() { return "running"; }
    void update();
    void draw();
    void next();
};

#endif