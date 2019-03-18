
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "np-extra.h"

#include "miscela/Combination.h"

#include "components/Analyzer.h"

#define OVERSAMPLING 0

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void exit();
		
		void keyPressed(int key);
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
        std::vector<ofParameter<float>> controls;

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
            
        bool bShowFrameRate;
            
        bool                bSave;
        ofParameter<int>    saveFrames;
        ofParameter<int>    saveCountDown;
        int                 saveCounter;
};
