
#include "Layer.h"

np::miscela::Layer::Layer(){
    loaded = false;
    mode = -1;
    width = 0;
    height = 0;
}

std::string _getAbsolute( const std::string & path ){
    std::string filename = ofFilePath::getFileName( path ); 

    if( ! ofFilePath::isAbsolute( path )){
        std::string filepath = ofFilePath::getCurrentWorkingDirectory() + "/" + path;
        return filepath;
    }
    return path;
}

void np::miscela::Layer::load( std::string path ){
    std::string ext = ofFilePath::getFileExt( path );
    
    if( ext == "frag" ){
        loaded = true;
        frag.load( path );
        mode = 0;
    }else if( ext == "lua" ){
        loaded = true;
        uscript.load( path );
        mode = 1;
    }else if( ext == "jpg" || ext == "png" 
           || ext == "bmp" || ext == "gif" ){
        path = _getAbsolute( path );
        loaded = true;
        image.load( path );
        mode = 2;
    }else if( ext == "mov" || ext == "mp4" ){
        path = _getAbsolute( path );
        loaded = true;
        video.load( path );
        video.setLoopState(OF_LOOP_NORMAL);
        video.play();
        mode = 3;
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
            
            case 1: // lua script
                uscript.render( fbo );
            break;

            case 2: // image
            {
                ofSetColor(255);
                ofRectangle fborect( 0, 0, fbo.getWidth(), fbo.getHeight() );
                ofRectangle imgrect( 0, 0, image.getWidth(), image.getHeight() );
                //imgrect.scaleTo( fborect, OF_ASPECT_RATIO_KEEP );
                imgrect.alignTo( fborect );
                
                fbo.begin();
                    image.draw( imgrect.x, imgrect.y, imgrect.width, imgrect.height );
                fbo.end();
            }
            break;
            
            case 3: // video
            {
                ofSetColor(255);
                ofRectangle fborect = ofRectangle( 0, 0, fbo.getWidth(), fbo.getHeight() );
                ofRectangle vidrect = ofRectangle( 0, 0, video.getWidth(), video.getHeight() );
                vidrect.scaleTo( fborect, OF_ASPECT_RATIO_KEEP );

                video.update();

                fbo.begin();
                    ofSetColor(255);
                    video.draw( vidrect.x, vidrect.y, vidrect.width, vidrect.height  );
                fbo.end();
            }
            break;
            
            default: break;
        }
    }
}

void np::miscela::Layer::setControlX( float value ){
    switch( mode ) {
        case 0: 
            frag.controlX = value; 
        break;
        
        case 1:
            uscript.variable( "control_x", value );
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setControlY( float value ){
    switch( mode ) {
        case 0: 
            frag.controlY = value; 
        break;
        
        case 1:
            uscript.variable( "control_y", value );
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setButtonA( bool value ){
    switch( mode ) {
        case 0: 
            frag.buttonA = value; 
        break;
        
        case 1:
            uscript.variable( "button_a", value );
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setButtonB( bool value ){
    switch( mode ) {
        case 0: 
            frag.buttonB = value; 
        break;
        
        case 1:
            uscript.variable( "button_b", value );
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setColorA( ofColor color ){ 
    switch( mode ) {
        case 0: 
            frag.colorA = color; 
        break;
        /*
        case 1:
            px::setColorA( color.r / 255.0f, color.g / 255.0f, color.b / 255.0f );
        break;
        */
        default: break;
    }
}

void np::miscela::Layer::setColorB( ofColor color ){ 
    switch( mode ) {
        case 0: 
            frag.colorB = color; 
        break;
        /*
        case 1:
            px::setColorB( color.r / 255.0f, color.g / 255.0f, color.b / 255.0f );
        break;
        */
        default: break;
    }
}


void np::miscela::Layer::setSpeed( float value ){ 
    switch( mode ) {
        case 0: 
            frag.speed = value; 
        break;
        
        case 1: 
            uscript.speed = value; 
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setModulation( float value ){ 
    switch( mode ) {
        case 0: 
            frag.modulation = value; 
        break;
        
        case 1:
            uscript.variable( "modulation", value );
        break;
        
        default: break;
    }
}

void np::miscela::Layer::setTime( float value ){ 
    switch( mode ) {
        case 0: 
            frag.setTime( value );
        break;
        
        case 1: 
            uscript.setTime( value );
        break;

        default: break;
    }
}
    
