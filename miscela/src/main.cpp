#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char *argv[] ){

    if( argc>1 ){		

        ofParameterGroup config;
            ofParameterGroup webcam;
                ofParameter<int> webcamW;
                ofParameter<int> webcamH;
                ofParameter<int> webcamID;
                ofParameter<int> webcamMode;
            ofParameterGroup canvas;
                ofParameter<int> cWidth;
                ofParameter<int> cHeight;
                ofParameter<int> cFrameRate;
                ofParameter<bool> cShowFrameRate;
                ofParameter<int> cDownSample;      
                ofParameter<int> cDoNotResize;      
        config.setName("config");  
        canvas.setName("canvas");
            canvas.add( cWidth.set( "width", 800, 0, 5000) );
            canvas.add( cHeight.set( "height", 480, 0, 5000) );
            canvas.add( cDownSample.set( "downsample", 1, 1, 8) );
            canvas.add( cFrameRate.set( "framerate", 60, 1, 120) );
            canvas.add( cShowFrameRate.set( "show_fps", false) );
            canvas.add( cDoNotResize.set( "do_not_resize", false) );
        config.add( canvas );
        webcam.setName("webcam");
            webcam.add( webcamW.set("width", 640, 0, 5000) );
            webcam.add( webcamH.set("height", 480, 0, 5000) );
            webcam.add( webcamID.set("ID", -1, -1, 12) );
            webcam.add( webcamMode.set("mode", 0, 0, 12) );
        config.add( webcam );

        std::vector<std::string> paths;
 
        for( int i=1; i<argc; ++i ){
                            
            std::string path = std::string( argv[i] );
            std::string ext = ofFilePath::getFileExt( path );
            
            if( ext == "json" ){
                ofJson json = ofLoadJson( path );
                ofDeserialize( json, config );
            }else{
                paths.push_back( path );
            }
        }
        
#ifdef __ARM_ARCH
        ofGLESWindowSettings settings;
        settings.glesVersion = 2;
#else
        ofGLFWWindowSettings settings;
        settings.resizable = true;
#endif

        settings.setSize( cWidth, cHeight );        
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

        shared_ptr<ofApp> mainApp(new ofApp);
        mainApp->paths = paths;
        mainApp->bShowFrameRate = cShowFrameRate;
        mainApp->downsample = cDownSample;
        mainApp->camID = webcamID;
        mainApp->camW = webcamW;
        mainApp->camH = webcamH;
        mainApp->camMode = webcamMode;
        mainApp->framerate = cFrameRate;
        mainApp->width = cWidth;
        mainApp->height = cHeight;
        mainApp->resizable = !cDoNotResize;

        ofSetFrameRate( cFrameRate );
        
        ofRunApp(mainWindow, mainApp);
        ofRunMainLoop();

	}else{
        ofLogError() << "[ miscela ] NO INPUT ARGUMENTS!\n";
    }
        
}
