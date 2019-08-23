#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char *argv[] ){

    if( argc>1 ){		

        // ------------- hardcoded defaults -----------------
        ofParameterGroup config;
            ofParameterGroup webcam;
                ofParameter<int> webcamW;
                ofParameter<int> webcamH;
                ofParameter<int> webcamID;
                ofParameter<int> webcamMode;
            ofParameterGroup canvas;
                ofParameter<int> cOriginX;
                ofParameter<int> cOriginY;
                ofParameter<int> cWidth;
                ofParameter<int> cHeight;
                ofParameter<int> cFrameRate;
                ofParameter<bool> cShowFrameRate;
                ofParameter<int> cDownSample;      
                ofParameter<int> cDoNotResize;  
                ofParameter<bool> cDecorate;
            ofParameterGroup colors;
                ofParameter<ofColor> cColorA;
                ofParameter<ofColor> cColorB;
            ofParameterGroup audio;
                ofParameter<int> aLow;
                ofParameter<int> aHigh;
                ofParameter<float> aThreshold;
                ofParameter<float> aToSpeed;
        config.setName("config");  
        canvas.setName("canvas");
            canvas.add( cOriginX.set( "origin_x", -1, 0, 5000) );
            canvas.add( cOriginY.set( "origin_y", -1, 0, 5000) );
            canvas.add( cWidth.set( "width", 800, 0, 5000) );
            canvas.add( cHeight.set( "height", 480, 0, 5000) );
            canvas.add( cDownSample.set( "downsample", 1, 1, 8) );
            canvas.add( cFrameRate.set( "framerate", 60, 1, 120) );
            canvas.add( cShowFrameRate.set( "show_fps", false) );
            canvas.add( cDoNotResize.set( "do_not_resize", false) );
            canvas.add( cDecorate.set( "decorate_window", true) );
        config.add( canvas );
        webcam.setName("webcam");
            webcam.add( webcamW.set("width", 640, 0, 5000) );
            webcam.add( webcamH.set("height", 480, 0, 5000) );
            webcam.add( webcamID.set("ID", -1, -1, 12) );
            webcam.add( webcamMode.set("mode", 0, 0, 12) );
        config.add( webcam );
        
        colors.setName("colors");
            colors.add( cColorA.set("color A", ofColor(255) ) );
            colors.add( cColorB.set("color B", ofColor(180) ) );
        config.add( colors );
        
        audio.setName("audio");
            audio.add( aLow.set("freq low", 100, 20, 20000 ) );
            audio.add( aHigh.set("freq high", 20000, 20, 20000 ) );
            audio.add( aThreshold.set("threshold", 0.3f, 0.0f, 1.0f ) );
            audio.add( aToSpeed.set("to speed", 0.0f, 0.0f, 1.0f ) );
        config.add( audio );
        
        // enable to generate defaults
        //ofJson json;
        //ofSerialize( json, config );
        //ofSavePrettyJson( "defaults.json", json );     


        // --------------- user defaults -----------------
        std::string defaults = ofFilePath::getUserHomeDir() + "/.config/miscela.json";
        ofFile file( defaults );

        if( file.exists() ){
            ofLogNotice() << "loading user defaults...";
            ofJson json = ofLoadJson( defaults );
            ofDeserialize( json, config );
        }    


        // --------------- file inputs  ------------------
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
        if( cOriginX != -1 && cOriginY != -1 ){
            settings.setPosition( glm::vec2( cOriginX, cOriginY ) );   
        }
        settings.setSize( cWidth, cHeight );     
        settings.decorated = cDecorate;   
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
        mainApp->colorA = cColorA;
        mainApp->colorB = cColorB;
        mainApp->colorA.setName( "color A");
        mainApp->colorB.setName( "color B");
        mainApp->freqLow = pdsp::f2p( aLow );
        mainApp->freqHigh = pdsp::f2p( aHigh );
        mainApp->audio2speed.set("audio to speed", aToSpeed.get(), 0.0f, 1.0f);
        mainApp->lowThreshold.set("low threshold", aThreshold.get(), 0.0f, 1.0f);

        ofSetFrameRate( cFrameRate );
        
        ofRunApp(mainWindow, mainApp);
        ofRunMainLoop();

	}else{
        ofLogError() << "[ miscela ] NO INPUT ARGUMENTS!\n";
    }
        
}
