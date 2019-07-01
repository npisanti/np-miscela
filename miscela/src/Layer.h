
#pragma once 

#include "ofMain.h"
#include "DotFrag.h"
#include "np-pixelscript.h"

namespace np{ namespace miscela {

class Layer{

public:

    Layer();

    void load( std::string path );

    void render( ofFbo & fbo );
    
    void setControlA( float value );
    void setControlB( float value );
    void setButtonA( bool value );
    void setButtonB( bool value );
    
    void setColorA( ofColor color );
    void setColorB( ofColor color );
    void setPosition( const glm::vec3 & position );
    void setSpeed( float value );
    void setModulation( float value );
    void setTime( float value );
    
    bool isFragment(){ return mode==0; }
    bool requiresClear(){ return mode==0; }
    
    void draw( int x, int y );
    
    int getWidth() const { return width; };
    int getHeight() const { return height; };
    
private:
    
    int mode;
    
    np::miscela::DotFrag  frag;
    ofImage               image;
    ofVideoPlayer         video;
    
    np::PixelScript uscript;
   
    bool loaded;
    
    int width;
    int height;
};  

}}
