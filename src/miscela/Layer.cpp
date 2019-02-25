
#include "Layer.h"

np::miscela::Layer::Layer(){
    loaded = false;
    mode = -1;
    width = 0;
    height = 0;
}

void np::miscela::Layer::resize( int width, int height ){
    this->width = width;
    this->height = height;
    lua.allocate( width, height );
}

void np::miscela::Layer::load( std::string path ){
    std::string ext = ofFilePath::getFileExt( path );
    if( ext == "frag" ){
        loaded = true;
        frag.load( path );
        mode = 0;
    }else if( ext == "lua" ){
        loaded = true;
        lua.load( path );
        mode = 1;
    }else{
        loaded = false;
        mode = -1;
    }
}

void np::miscela::Layer::render( ofFbo & fbo ){
    if( loaded ){
        switch( mode ){
            case 0: // shader
                frag.apply( fbo );
            break;
            
            case 1: // lua
                lua.setBoundaries( ofRectangle( 0, 0, fbo.getWidth(), fbo.getHeight()) );
                
                lua.update();
                
                fbo.begin();
                    lua.draw();
                fbo.end();
            break;
            
            default: break;
        }
    }
}
    
void np::miscela::Layer::setControl( float value ){
    switch( mode ){
        case 0: frag.control = value; break;
        case 1: lua.control = value; break;
        default: break;
    }
}

void np::miscela::Layer::setModulation( float value ){
    switch( mode ){
        case 0: frag.modulation = value; break;
        case 1: lua.modulation = value; break;
        default: break;
    }
}

void np::miscela::Layer::setSpeed( float value ){
    switch( mode ){
        case 0: frag.speed = value; break;
        case 1: lua.speed = value; break;
        default: break;
    }
}

void np::miscela::Layer::setColorA( ofColor color ){
    switch( mode ){
        case 0: frag.colorA = color; break;
        case 1: lua.colorA = color; break;
        default: break;
    }
}

void np::miscela::Layer::setColorB( ofColor color ){
    switch( mode ){
        case 0: frag.colorB = color; break;
        case 1: lua.colorB = color; break;
        default: break;
    } 
}

void np::miscela::Layer::setPosition( const glm::vec3 & position ){
    switch( mode ){
        case 0: frag.position = position; break;
        case 1: lua.position = position; break;
        default: break;
    }
}


