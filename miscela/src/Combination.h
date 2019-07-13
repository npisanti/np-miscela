
#pragma once 

#include "ofMain.h"
#include "Layer.h"

namespace np{ namespace miscela {

class Combination {

public:
    void setup( int w, int h, int downsample=1, int multisampling=0 );
    void clear();
    void add( std::string path );
    void update();
    
    void resize( int w, int h );
    
    void setControlX( float value );
    void setControlY( float value );
    void setButtonA( bool value );
    void setButtonB( bool value );
    
    void setColorA( ofColor color );
    void setColorB( ofColor color );
    void setSpeed( float value );
    void setModulation( float value );
    void setTime( float value );
    
    void draw( int x, int y ){ fbo.draw( x, y, fbo.getWidth()*downsample, fbo.getHeight()*downsample ); }

    std::vector<Layer> layers;

    ofFbo fbo;
    
private:

    int multisampling;
    int downsample;
};  

}}
