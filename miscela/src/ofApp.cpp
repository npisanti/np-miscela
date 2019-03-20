
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    combo.setup( ofGetWidth(), ofGetHeight(), downsample );
    combo.layers.reserve( 12 );
    for( auto & path : paths ){
        combo.add( path );
    }
    
    std::string title = "miscela : " + ofFilePath::getFileName( paths[0] );             
    for( size_t i=1; i<paths.size(); ++i ){
        title += " >> ";
        title +=  ofFilePath::getFileName( paths[i] );
    }
    ofSetWindowTitle( title );

    //-------------------------------------
    position = glm::vec3( 0.5, 0.5, 0.0 );
    mod = 0.0f;

    bResize = false;
    
    int numPalettes = 2;
    palette.setup( numPalettes, 2 );
    
	gui.setup("miscela", "settings.xml", 20, 20 );
    
    gui.add( speed.set( "speed control", 1.0f, 0.0f, 2.0f) );
    
    controls.resize( combo.layers.size() );
    for( size_t i=0; i<controls.size(); ++i ){
        gui.add( controls[i].set("control "+ ofToString(i), 0.5f, 0.0f, 1.0f ) );
    }
    
    gui.add( palette.parameters );
    gui.add( invertPalette.set("invert palette", false) );
    gui.add( useCamTexture.set("use cam texture", false) );

    analyzer.band( "audio in", 0 );
    analyzer.setup( 2 ); // audio device id

    audioMap.setName("audio mod");
    
    audioMap.add( audioMeter.set("audio in", 0.0f, 0.0f, 1.0f) );
    audioMap.add( lowThreshold.set("low threshold", 0.0f, 0.0f, 1.0f) );
    audioMap.add( highThreshold.set("high threshold", 1.0f, 0.0f, 1.0f) );
    audioMap.add( modMeter.set("mod level", 0.0f, 0.0f, 1.0f) );
    gui.add( audioMap );
    gui.add( analyzer.parameters );

    gui.add( saveFrames.set("save frames", 1, 1, 60*10 ) );
    gui.add( saveCountDown.set("countdown", 0, 0, 60*5 ) );

	gui.minimizeAll();
    gui.loadFromFile( "settings.xml" ); 
    bDrawGui = false;
    ofHideCursor();
    
    useCamTexture.addListener( this, &ofApp::onUseCamTexture );
    
    bResize=true;
    resizeCounter=0;
    
    bSave = false;
    saveCounter = 0;
    
    if( camID != -1 ){
        openCam( camID, camW, camH );
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    if(resizeCounter>0){
        resizeCounter--;
    }
    
    if( bResize && resizeCounter==0 ){
        combo.resize( ofGetWidth(), ofGetHeight() );
        bResize = false;
    }

    mod = ofMap(analyzer.meter(), lowThreshold, highThreshold, 0.0f, 1.0f, true );
    
    int ca = invertPalette ? 1 : 0; 
    int cb = invertPalette ? 0 : 1;
    
    combo.setColorA( palette.color( ca ) );    
    combo.setColorB( palette.color( cb ) );    
    combo.setModulation( mod );
    combo.setSpeed( speed );
    combo.setPosition( position );
    
    if( camID != -1 ){
        if( cam.isInitialized() ){ cam.update(); }
        
        combo.fbo.begin();
            ofClear( 0, 0, 0, 0 );
            ofSetColor( 255 );
            
            switch( camMode ){
                case 0:
                    cam.draw( 0, 0, combo.fbo.getWidth(), combo.fbo.getHeight() );
                break;
                
                case 1:
                {
                    float mult =  float(combo.fbo.getWidth()) / float(cam.getWidth());
                    float h = cam.getHeight() * mult;
                    float y = (combo.fbo.getHeight()-h)*0.5;
                    cam.draw( 0, y, combo.fbo.getWidth(), h );
                }
                break;
                
                case 2:
                {
                    float mult =  float(combo.fbo.getHeight()) / float(cam.getHeight());
                    float w = cam.getWidth() * mult;
                    float x = (combo.fbo.getWidth()-w)*0.5;
                    cam.draw( x, 0, w, combo.fbo.getHeight() );
                }
                break;
            }
        combo.fbo.end();            
    }

    combo.update();
    
    if( bSave ){
        if( saveCounter < saveFrames ){
            ofPixels pixels;
            combo.fbo.readToPixels( pixels );
            ofSaveImage(pixels, "frames/frame"+ofToString(ofGetFrameNum())+".png" );            
        }
        saveCounter--;
        if(saveCounter==0) bSave = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    combo.draw( 0, 0 );
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    if( bDrawGui ){ 
        audioMeter = analyzer.meter();
        modMeter = mod;
        gui.draw(); 
    }   
    
    if( bShowFrameRate || bDrawGui ){
        ofSetColor( 0 );
        ofDrawBitmapString( "fps = " + ofToString(ofGetFrameRate()), ofGetWidth()-120, 24 );
        ofSetColor( 255 );
        ofDrawBitmapString( "fps = " + ofToString(ofGetFrameRate()), ofGetWidth()-120, ofGetHeight()-20 );
    }   
    
    if( saveCounter > saveFrames){
        int remaining = saveCounter - saveFrames;
        ofDrawBitmapString( "countdown = " + ofToString( remaining ), ofGetWidth()-120, 20 );
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofLogNotice() << "closing analyzer...";
    ofSleepMillis( 50.0f );
}

//--------------------------------------------------------------
void ofApp::openCam( int index, int w, int h ){
    cam.setDeviceID( index );
    cam.setDesiredFrameRate(60);
    switch( index ){
        default: cam.initGrabber(w, h); break;
    }
    useCamTexture = true;
}
		
void ofApp::onUseCamTexture( bool & value ){
    if( value && !cam.isInitialized() ){
        useCamTexture = false;
    }
}    

void ofApp::keyPressed(int key){
	switch(key){
		case 'g': 
        {
            bDrawGui = !bDrawGui;
            if( bDrawGui ){
                ofShowCursor();
            }else{
                ofHideCursor();
            }
        } 
        break;
        
		case 'f': bShowFrameRate = !bShowFrameRate; break;
        
        case 'r': bResize=true; break;
        
        case 's':   
            bSave = true;
            saveCounter = saveFrames + saveCountDown;
        break;
    }
}

void ofApp::windowResized(int w, int h){
    resizeCounter = 8;
    bResize = true;
}

void ofApp::xyControl( float x, float y, int button ){
    switch( button ){
        default:
            position.x = x / float( ofGetWidth() );
            position.y = y / float( ofGetHeight() );
            position.z = float( ofGetMousePressed() );        
        break;
        
        case 2:
            float control = x / ofGetWidth();
            if( control < 0.0f ){ control = 0.0f; }
            if( control > 1.0f ){ control = 1.0f; }
            combo.setControl( control );
        break;
    }
}

void ofApp::mouseDragged(int x, int y, int button){
    xyControl( x, y, button );
}
void ofApp::mousePressed(int x, int y, int button){
    xyControl( x, y, button );
}
void ofApp::mouseReleased(int x, int y, int button){
    xyControl( x, y, button );
}

//--------------------------------------------------------------
