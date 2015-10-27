#ifndef __app__
#define __app__

#include "baseApp.h"

#define N 100
#define THRESHOLD 50
class App: public BaseApp
{
    
public:
    App();
    ~App(){};
    void keyPressed(int key);
    void set(int idx, int v);
    
    void pushButton();

    vector<int> values;
    
    void drawValues();
    bool bBallOn;
    float ballOnTime;
    bool isHit();
};


#endif
