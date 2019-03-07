
#pragma once 

#include "ofMain.h"
#include "Layer.h"

namespace np{ namespace miscela {

class Combination : public FileWatcher {

public:
    void setup( int w, int h, int multisampling=0 );
    void clear();
    void add( std::string path );
    void update();
    
    void resize( int w, int h );
    
    void setControl( float value );
    void setColorA( ofColor color );
    void setColorB( ofColor color );
    void setPosition( const glm::vec3 & position );
    void setSpeed( float value );
    void setModulation( float value );
    
    void draw( int x, int y ){ fbo.draw( x, y ); }

    std::vector<Layer> layers;

    ofFbo fbo;
    
    int getRequiredWebcam(){ return webcamID; };
    int getWebcamWidth(){ return webcamW; };
    int getWebcamHeight(){ return webcamH; };
    int getWebcamMode(){ return webcamMode; };
    
private:

    int multisampling;

    bool bConfigAutoload;   
     
    ofParameterGroup config;
        ofParameterGroup webcam;
            ofParameter<int> webcamW;
            ofParameter<int> webcamH;
            ofParameter<int> webcamID;
            ofParameter<int> webcamMode;
        ofParameterGroup canvas;
            ofParameter<int> cWidth;
            ofParameter<int> cHeight;
            
    void reload() override;

};  

}}
