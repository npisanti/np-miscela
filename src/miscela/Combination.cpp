
#include "Combination.h"

void np::miscela::Combination::setup( int w, int h, int multisampling ){
    
    bConfigAutoload = true;
    
    config.setName("config");  
    canvas.setName("canvas");
        canvas.add( cWidth.set( "width", -1, 0, 5000) );
        canvas.add( cHeight.set( "height", -1, 0, 5000) );
        canvas.add( cFrameRate.set( "framerate", -1, 1, 120) );
    config.add( canvas );
    webcam.setName("webcam");
        webcam.add( webcamW.set("width", -1, 0, 5000) );
        webcam.add( webcamH.set("height", -1, 0, 5000) );
        webcam.add( webcamID.set("ID", -1, -1, 12) );
        webcam.add( webcamMode.set("mode", -1, 0, 12) );
    config.add( webcam );
        
    ofFboSettings settings;
    settings.width = w;
    settings.height = h;
    settings.numSamples = 0;
    settings.useStencil = true;
    settings.numSamples = multisampling;
    fbo.allocate( settings );
  
    this->multisampling = multisampling;
    
    clear();
}

void np::miscela::Combination::reload(){
    ofJson json = ofLoadJson( filepath );
    ofDeserialize( json, config );

    if( cWidth!=-1 && cHeight!=-1 ){
        ofSetWindowShape( cWidth, cHeight );
    }

    if( cFrameRate!=-1 ){
        ofSetFrameRate( cFrameRate );
    }
}

void np::miscela::Combination::clear(){
    fbo.begin();
        ofClear( 0, 0, 0, 255 );
    fbo.end();
}

void np::miscela::Combination::add( std::string path ){
    
    std::string ext = ofFilePath::getFileExt( path );
    
    if( ext == "json" ){
        load( path, bConfigAutoload );
    }else{
        layers.emplace_back();
        layers.back().load( path );

        if(fbo.getWidth()==0 || fbo.getHeight()==0){
            ofLogError() << "[np::miscela::Combination] added script without calling setup() first, undefined behavior\n";
        }        
    }    
}

void np::miscela::Combination::update(){
    for( size_t i=0; i<layers.size(); ++i ){
        layers[i].render( fbo );
    }
}

void np::miscela::Combination::resize( int w, int h ){
    fbo.allocate( w, h, GL_RGBA, multisampling );
}
    
void np::miscela::Combination::setControl( float value ){
    for( auto & layer : layers ){
        layer.setControl( value );
    }
}

void np::miscela::Combination::setColorA( ofColor color ){
    for( auto & layer : layers ){
        layer.setColorA( color );
    }
}

void np::miscela::Combination::setColorB( ofColor color ){
    for( auto & layer : layers ){
        layer.setColorB( color );
    }
}

void np::miscela::Combination::setPosition( const glm::vec3 & position ){
    for( auto & layer : layers ){
        layer.setPosition( position );
    }
}

void np::miscela::Combination::setSpeed( float value ){
    for( auto & layer : layers ){
        layer.setSpeed( value );
    }
}

void np::miscela::Combination::setModulation( float value ){
    for( auto & layer : layers ){
        layer.setModulation( value );
    }
}
