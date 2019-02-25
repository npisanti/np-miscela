
#pragma once

#include "ofMain.h"

namespace np{ namespace miscela {
    
class SandBox{

public:
    SandBox();

    ofParameter<float> control;
    ofParameter<glm::vec3> position;
    ofParameter<ofColor> colorA;
    ofParameter<ofColor> colorB;
    
    ofParameter<float> modulation;
    
    const ofRectangle & getBoundaries(){ return boundaries; }
    void setBoundaries( const ofRectangle & box );
    void move( float x, float y );
    void resize( float w, float h );
    
    virtual void onResize( float w, float h){};
    
protected:
    ofRectangle boundaries;
    
};
    
    
}}
