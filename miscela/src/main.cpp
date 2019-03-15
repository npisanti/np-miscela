#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char *argv[] ){

    if( argc>1 ){		
        std::vector<std::string> paths;
 
        for( int i=1; i<argc; ++i ){
            paths.push_back( std::string( argv[i] ) );
        }
        
#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
#else
        ofGLFWWindowSettings settings;
        settings.resizable = true;
#endif
        settings.setSize( 480, 480 );

        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

        shared_ptr<ofApp> mainApp(new ofApp);
        mainApp->paths = paths;

        ofRunApp(mainWindow, mainApp);
        ofRunMainLoop();

	}else{
        ofLogError() << "[ miscela ] NO INPUT ARGUMENTS!\n";
    }
        
}
