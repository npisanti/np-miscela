
#pragma once 

#include "ofMain.h"
#include "miscela/DotFrag.h"
#include "miscela/Lua.h"

namespace np{ namespace miscela {

class Layer{
public:
    Layer();

    void load( std::string path );

    void render( ofFbo & fbo );
    
    void setControl( float value );
    void setColorA( ofColor color );
    void setColorB( ofColor color );
    void setPosition( const glm::vec3 & position );
    void setSpeed( float value );
    void setModulation( float value );
    
    bool isFragment(){ return mode==0; }
    bool requiresClear(){ return mode==0; }
    
    void draw( int x, int y );
    
    int getWidth() const { return width; };
    int getHeight() const { return height; };
    
private:
    int mode;
    np::miscela::DotFrag  frag;
    np::miscela::Lua      lua;
    ofImage         image;
    ofVideoPlayer   video;
   
    bool loaded;
    
    int width;
    int height;
};  

}}
