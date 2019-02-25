
#pragma once

#include "ofMain.h"
#include "SandBox.h"
#include "ofxLua/src/ofxLua.h"
#include "ofxWatchFile.h"

#include "nanovg/src/nanovg.h"


namespace np{ namespace miscela {
    
class Lua : public SandBox, ofxLuaListener, ofxWatchFile {
    
public:
    Lua();
    ~Lua();

    void allocate( int width, int height );    
    void load( std::string path );
    
    void draw();
    void update();
    
    void playhead( float clock ){ this->clock = clock; }

    ofParameterGroup parameters;
        ofParameter<float> speed;
        
private:

    bool loaded;

    ofxLua lua;    

    std::string path;
    std::string filename;

    void errorReceived(std::string& msg);
    
    bool reload(ofFile &file) override;
    float clock;
    float before;
    
    ofFbo fbo;

    static int constructed;
    
    float aspect;
};
    
}}
