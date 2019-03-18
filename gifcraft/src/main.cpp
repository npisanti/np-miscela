
#include "ofMain.h"
#include "ofAppNoWindow.h"

class ofApp : public ofBaseApp{
public:

    ofFbo fbo;
    int width;
    int height;
    bool toAllocate = true;
    
    void initFbo( ofFbo & fbo, int w, int h){
                
        ofFbo::Settings settings;
        settings.width  = w;
        settings.height = h;
        settings.minFilter = GL_NEAREST;
        settings.maxFilter = GL_NEAREST;
        fbo.allocate( settings );
        toAllocate = false;
    }
    
    //---------------------------------------------------------------
    void setup(){

        std::string user = ofSystem("whoami");
        user.erase(std::remove(user.begin(), user.end(), '\n'), user.end());        

        ofDirectory dir;
        std::string path = "/home/";
        path += user;
        path += "/oF/apps/np-miscela/miscela/bin/data/frames";
        
        std::cout<<"getting images from is "<<path<<"\n";
        
        dir.listDir( path );
        dir.allowExt("png");
        dir.sort(); 
        
 
        if( dir.size() ){
            std::cout<<"cleaning files\n";
            for( size_t i=0; i<dir.size(); ++i ){
                ofImage image;
                image.load( dir.getPath(i) );
                
                if( toAllocate ){
                    initFbo( fbo, image.getWidth(), image.getHeight() );
                }
                
                fbo.begin();
                    ofClear( 0, 0, 0, 255 );
                    image.draw( 0, 0 );
                fbo.end();
                
                ofPixels pixels;
                fbo.readToPixels( pixels );
                std::string filename = "frame."+ofToString(i, 2, 4,'0')+".png";
                ofSaveImage(pixels, filename);
            }
            
            std::cout<<"creating gif...\n";
            
            ofSystem( "convert -loop 0 -delay 3 data/*.png data/output.gif" );
            
            ofSystem( "rm data/*.png" );
            std::cout<<"...done\n";
            
        }else{
            std::cout<<"no files in miscela/bin/data/frames folder\n";
            
        }
        

        ofExit();
    }

    //---------------------------------------------------------------
    void update() {

    }

    //---------------------------------------------------------------
    void exit(){

    }

};

//===================================================================
int main(int argc, char *argv[]){

    ofSetupOpenGL( 1920, 1080, OF_WINDOW);

    ofApp *app = new ofApp();
    
    app->width = 1280;
    app->height = 800;

    if(argc>1){		
        for( int i=1; i<argc; ++i ){
            switch( i ){
                case 1: app->width = ofToInt( argv[i] ); break;
                case 2: app->height = ofToInt( argv[i] );  break;
                default : break;
            }
        }   
    }
  
    ofRunApp( app );
}
