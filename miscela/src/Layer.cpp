
#include "Layer.h"

np::miscela::Layer::Layer(){
    loaded = false;
    mode = -1;
    width = 0;
    height = 0;
}

void np::miscela::Layer::load( std::string path ){
    std::string ext = ofFilePath::getFileExt( path );
    
    if( ext == "frag" ){
        loaded = true;
        frag.load( path );
        mode = 0;
    }else if( ext == "jpg" || ext == "png" 
           || ext == "bmp" || ext == "gif" ){
        loaded = true;
        image.load( path );
        mode = 2;
    }else if( ext == "mov" || ext == "mp4" ){
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

            case 2: // image
            {
                ofSetColor(255);
                ofRectangle fborect( 0, 0, fbo.getWidth(), fbo.getHeight() );
                ofRectangle imgrect( 0, 0, image.getWidth(), image.getHeight() );
                imgrect.scaleTo( fborect, OF_ASPECT_RATIO_KEEP );
                
                ofPushStyle();
                ofDisableAlphaBlending();
                fbo.begin();
                    image.draw( imgrect.x, imgrect.y, imgrect.width, imgrect.height );
                fbo.end();
                ofPopStyle();
            }
            break;
            
            case 3: // video
            {
                ofSetColor(255);
                ofRectangle fborect = ofRectangle( 0, 0, fbo.getWidth(), fbo.getHeight() );
                ofRectangle vidrect = ofRectangle( 0, 0, video.getWidth(), video.getHeight() );
                vidrect.scaleTo( fborect, OF_ASPECT_RATIO_KEEP );

                video.update();
                
                ofPushStyle();
                ofDisableAlphaBlending();
                fbo.begin();
                    ofSetColor(255);
                    video.draw( vidrect.x, vidrect.y, vidrect.width, vidrect.height  );
                fbo.end();
                ofPopStyle();
            }
            break;
            
            default: break;
        }
        
    }
}
    
