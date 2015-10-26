#ifndef __baseApp__
#define __baseApp__

#include "ofMain.h"
#include "baseState.h"
#include "assets.h"

class BaseApp
{
    
protected:
    class BaseState *current_state;
    Assets *assets;
    
public:
    BaseApp();
    
    void setCurrentState(BaseState *s);
    void keyPressed(ofKeyEventArgs& eventArgs);
    void update(ofEventArgs &args);
    virtual void keyPressed(int key)=0;
    void update();
    void draw();
    void next();
    
    Assets *getAssets();
};

#endif