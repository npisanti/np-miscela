
#include "Combination.h"

void np::miscela::Combination::setup( int w, int h, int downsample, int multisampling ){
    this->downsample = downsample;

    ofFboSettings settings;
    settings.width = w/downsample;
    settings.height = h/downsample;
    #ifndef __ARM_ARCH
    settings.numSamples = multisampling;
    #endif
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    fbo.allocate( settings );
  
    this->multisampling = multisampling;
    
    clear();
}

void np::miscela::Combination::clear(){
    fbo.begin();
        ofClear( 0, 0, 0, 255 );
    fbo.end();
}

void np::miscela::Combination::add( std::string path ){
    
    layers.emplace_back();
    layers.back().load( path );

    if(fbo.getWidth()==0 || fbo.getHeight()==0){
        ofLogError() << "[np::miscela::Combination] added script without calling setup() first, undefined behavior\n";
    }        

}

void np::miscela::Combination::update(){
    for( size_t i=0; i<layers.size(); ++i ){
        layers[i].render( fbo );
    }
}

void np::miscela::Combination::resize( int w, int h ){
    ofFboSettings settings;
    settings.width = w/downsample;
    settings.height = h/downsample;
    #ifndef __ARM_ARCH
    settings.numSamples = multisampling;
    #endif
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    fbo.allocate( settings );
}
    
void np::miscela::Combination::setControlA( float value ){
    for( auto & layer : layers ){
        layer.setControlA( value );
    }
}
    
void np::miscela::Combination::setControlB( float value ){
    for( auto & layer : layers ){
        layer.setControlB( value );
    }
}
    
void np::miscela::Combination::setButtonA( bool value ){
    for( auto & layer : layers ){
        layer.setButtonA( value );
    }
}
    
void np::miscela::Combination::setButtonB( bool value ){
    for( auto & layer : layers ){
        layer.setButtonB( value );
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

void np::miscela::Combination::setTime( float value ){
    for( auto & layer : layers ){
        layer.setTime( value );
    }
}
