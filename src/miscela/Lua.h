
#pragma once

#include "ofMain.h"
#include "SandBox.h"
#include "ofxLua/src/ofxLua.h"

#include "nanovg/src/nanovg.h"

#include "FileWatcher.h"

namespace np{ namespace miscela {
    
class Lua : public SandBox, public FileWatcher, public ofxLuaListener {
    
public:
    Lua();
    ~Lua();
    
    void draw( ofFbo & fbo );

    void playhead( float clock ){ this->clock = clock; }

    ofParameter<float> speed;
        
private:

    bool loaded;

    ofxLua lua;    
    
    std::string filename;

    void errorReceived(std::string& msg);
    
    void reload() override;
    float clock;
    float before;

    static int constructed;
    
    float aspect;
};
    
}}
