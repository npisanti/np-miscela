
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    combo.setup( width, height, downsample );
    combo.layers.reserve( 12 );
    for( auto & path : paths ){
        combo.add( path );
    }
    
    std::string title = ofFilePath::getFileName( paths[0] );             
    for( size_t i=1; i<paths.size(); ++i ){
        title += " >> ";
        title +=  ofFilePath::getFileName( paths[i] );
    }
    ofSetWindowTitle( title );

    //-------------------------------------
    mod = 0.0f;

    bResize = false;
    
	gui.setup("miscela", "settings.xml", 20, 20 );
    
    gui.add( speed.set( "speed control", 1.0f, 0.0f, 2.0f) );
    gui.add( controlX.set("control X", 0.5f, 0.0f, 1.0f ) );
    gui.add( controlY.set("control Y", 0.5f, 0.0f, 1.0f ) );
    gui.add( buttonA.set( "button A", false) );
    gui.add( buttonB.set( "button B", false) );
    
    gui.add( useCamTexture.set("use cam texture", false) );

    analyzer.band( "audio in", 0 );
    analyzer.setup( 0 ); // audio device id

    audioMap.setName("audio mod");
    
    audioMap.add( audioMeter.set("audio in", 0.0f, 0.0f, 1.0f) );
    audioMap.add( lowThreshold );
    audioMap.add( highThreshold.set("high threshold", 1.0f, 0.0f, 1.0f) );
    audioMap.add( modMeter.set("mod level", 0.0f, 0.0f, 1.0f) );
    audioMap.add( audio2speed );
    gui.add( audioMap );
    gui.add( analyzer.parameters );

    gui.add( saveFrames.set("save frames", 1, 1, 60*10 ) );
    gui.add( saveCountDown.set("countdown", 0, 0, 60*5 ) );
    gui.add( saveStart.set("start second", 0, 0, 60 ) );

    analyzer.setBandLowPitch( freqLow );
    analyzer.setBandHighPitch( freqHigh );

	gui.minimizeAll();
    //gui.loadFromFile( "settings.xml" ); 
    bDrawGui = false;
    
    bShowCursor = false;
    ofHideCursor();
    
    useCamTexture.addListener( this, &ofApp::onUseCamTexture );
    
    bResize = resizable;
    resizeCounter=0;
    if( !resizable ){ combo.resize( width, height ); }
    
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

    //mod = ofMap(analyzer.meter(), lowThreshold, highThreshold, 0.0f, 1.0f, true );
    
    combo.setColorA( colorA );    
    combo.setColorB( colorB );    
    combo.setModulation( mod );
    combo.setSpeed( speed + (mod * audio2speed) );
    combo.setControlX( controlX );
    combo.setControlY( controlY );
    combo.setButtonA( buttonA );
    combo.setButtonB( buttonB );
    
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
        if( saveCounter <= saveFrames ){
            float frametime = ( saveFrames-saveCounter ) / float(saveFrames );
            frametime *= saveFrames / framerate ;
            frametime += float( saveStart );
            combo.setTime( frametime );
            
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
        case ' ':
            buttonA = true;
        break;
        
        case OF_KEY_RETURN:
            buttonB = true;
        break;
        
        case 'c':
            bShowCursor = !bShowCursor;
            if( bShowCursor ){
                ofShowCursor();
            }else{
                ofHideCursor();
            }
        break;
        
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
            speed = 0.0f;
        break;
    }
}

void ofApp::keyReleased(int key){
	switch(key){
        case ' ':
            buttonA = false;
        break;
        
        case OF_KEY_RETURN:
            buttonB = false;
        break;
        
    }
}

void ofApp::windowResized(int w, int h){
    if( resizable ){
        resizeCounter = 8;
        bResize = true;        
    }
}

void ofApp::xyControl( float x, float y ){
    float cx = x / ofGetWidth();
    float cy = y / ofGetHeight();
    if( cx < 0.0f ){ cx = 0.0f; }
    if( cx > 1.0f ){ cx = 1.0f; }
    if( cy < 0.0f ){ cy = 0.0f; }
    if( cy > 1.0f ){ cy = 1.0f; }
    controlX = cx;
    controlY = cy;
}

void ofApp::mouseDragged(int x, int y, int button){
    xyControl( x, y );
}

void ofApp::mousePressed(int x, int y, int button){
    xyControl( x, y );
    switch( button ){
        default: buttonA = true; break;
        case 2:  buttonB = true; break;
    }
}
void ofApp::mouseReleased(int x, int y, int button){
    xyControl( x, y );
    switch( button ){
        default: buttonA = false; break;
        case 2:  buttonB = false; break;
    }
}

//--------------------------------------------------------------
