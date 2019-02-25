
#include "Combination.h"

void np::miscela::Combination::setup( int w, int h, int multisampling ){
    this->multisampling = multisampling;
    fbo.allocate( w, h, GL_RGBA, multisampling );
    clear();
}

void np::miscela::Combination::clear(){
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
    fbo.end();
}

void np::miscela::Combination::add( std::string path ){
    layers.emplace_back();
    layers.back().load( path );
    layers.back().resize( fbo.getWidth(), fbo.getHeight() );
    
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
    fbo.allocate( w, h, GL_RGBA, multisampling );
    for( auto & layer : layers ){
        layer.resize( fbo.getWidth(), fbo.getHeight() );
    }
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
