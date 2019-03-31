
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "np-extra.h"

#include "Combination.h"

#include "components/Analyzer.h"

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

        void xyControl( float x, float y, int button );
                
        np::miscela::Combination combo;
        std::vector<std::string> paths;

        float mod;
        glm::vec3 position;
        bool bResize;
        int resizeCounter;

        bool		bDrawGui;
        ofxPanel 	gui;

        ofParameter<float> speed;
        ofParameter<float> controlA;
        ofParameter<float> controlB;
        ofParameter<bool> buttonA;
        ofParameter<bool> buttonB;
        
        np::PaletteTable palette;
        ofParameter<bool> invertPalette;
        
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
            
        bool                bSave;
        ofParameter<int>    saveFrames;
        ofParameter<int>    saveCountDown;
        ofParameter<int>    saveStart;
        int                 saveCounter;
        
        
        bool bShowFrameRate;
        int downsample;
        int camMode;
        int camID;
        int camW;
        int camH;
        float framerate;
        int width;
        int height;
        bool resizable;
};
