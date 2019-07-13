
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "np-extra.h"

#include "Combination.h"

#include "np-analyzer.h"

#define OVERSAMPLING 0

class ofApp : public ofBaseApp{
    
	public:
		void setup();
		void update();
		void draw();
    
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

        void xyControl( float x, float y );
                
        np::miscela::Combination combo;
        std::vector<std::string> paths;

        float mod;
        bool bResize;
        int resizeCounter;

        bool		bDrawGui;
        ofxPanel 	gui;

        ofParameter<float> speed;
        ofParameter<float> controlX;
        ofParameter<float> controlY;
        ofParameter<bool> buttonA;
        ofParameter<bool> buttonB;

        ofParameter<ofColor> colorA;
        ofParameter<ofColor> colorB;
        
        ofParameter<bool>   useCamTexture;
        void                onUseCamTexture( bool & value );        
        void                openCam( int index, int w, int h );
        ofVideoGrabber      cam;        
        
        np::Analyzer analyzer;
        ofParameterGroup audioMap;
            ofParameter<float> lowThreshold;
            ofParameter<float> highThreshold;
            ofParameter<float> audioMeter;
            ofParameter<float> modMeter;
            ofParameter<float> audio2speed;
            
        bool                bSave;
        ofParameter<int>    saveFrames;
        ofParameter<int>    saveCountDown;
        ofParameter<int>    saveStart;
        int                 saveCounter;
        
        bool bShowFrameRate;
        bool bShowCursor;
        int downsample;
        int camMode;
        int camID;
        int camW;
        int camH;
        float framerate;
        int width;
        int height;
        bool resizable;
        float freqLow;
        float freqHigh;
};
