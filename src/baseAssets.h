
#ifndef __baseAssets__
#define __baseAssets__

#include "ofMain.h"
#include "ofxJSON.h"

#define MAX_FONT 400

class BaseAssets{
public:
    BaseAssets();
    void loadImage(ofImage *image, string filename);
    void loadVideo(ofVideoPlayer *video, string filename);
    void stopVideos();
    
    int getLocalPort();
    int getWidth();
    int getHeight();
    float getScale();
    
    string getRemoteIp();
    int getRemotePort();
    
    virtual void loadAssets()=0;
    
    ofTrueTypeFont *getFont(int size);
    void loadFont(int size);

    string default_font;
    
    Json::Value getData(string key);
    ofxJSONElement settings;
    
private:
    vector<ofVideoPlayer*> videos;
    
    
    void clearFonts();
    ofTrueTypeFont		*fonts[MAX_FONT];
    
};


#endif