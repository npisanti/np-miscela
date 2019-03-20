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
        config.setName("config");  
        canvas.setName("canvas");
            canvas.add( cWidth.set( "width", -1, 0, 5000) );
            canvas.add( cHeight.set( "height", -1, 0, 5000) );
            canvas.add( cDownSample.set( "downsample", 1, 1, 8) );
            canvas.add( cFrameRate.set( "framerate", -1, 1, 120) );
            canvas.add( cShowFrameRate.set( "show_fps", false) );
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

        int width = 800; 
        int height = 480;
        if( cWidth != -1 ){ width = cWidth; }
        if( cHeight != -1 ){ height = cHeight; }
        settings.setSize( width, height );
        
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

        shared_ptr<ofApp> mainApp(new ofApp);
        mainApp->paths = paths;
        mainApp->bShowFrameRate = cShowFrameRate;
        mainApp->downsample = cDownSample;
        mainApp->camID = webcamID;
        mainApp->camW = webcamW;
        mainApp->camH = webcamH;
        mainApp->camMode = webcamMode;

        ofRunApp(mainWindow, mainApp);
        ofRunMainLoop();

	}else{
        ofLogError() << "[ miscela ] NO INPUT ARGUMENTS!\n";
    }
        
}
