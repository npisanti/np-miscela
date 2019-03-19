
#pragma once 

#include "ofMain.h"
#include "DotFrag.h"

namespace np{ namespace miscela {

class Layer{

public:

    Layer();

    void load( std::string path );

    void render( ofFbo & fbo );
    
    void setControl( float value ){ frag.control = value; }
    void setColorA( ofColor color ){ frag.colorA = color; }
    void setColorB( ofColor color ){ frag.colorB = color; }
    void setPosition( const glm::vec3 & position ){ frag.position = position; }
    void setSpeed( float value ){ frag.speed = value; }
    void setModulation( float value ){ frag.modulation = value; }
    
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
   
    bool loaded;
    
    int width;
    int height;
};  

}}
