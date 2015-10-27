#ifndef __app__
#define __app__

#include "baseApp.h"
#include "player.h"

class App: public BaseApp
{
    
public:
    App();
    ~App(){};
    void keyPressed(int key);
    void set(int idx, int v);
    
    void pushButton();
    
    void updatePlayers();
    
    Player player_0;
    Player player_1;
    
};


#endif
