#ifndef __app__
#define __app__

#include "baseApp.h"

class App: public BaseApp
{
    
public:
    App();
    ~App(){};
    void keyPressed(int key);
    void set(int idx, int v);
    
    void pushButton();

    int value; 
    
};


#endif
