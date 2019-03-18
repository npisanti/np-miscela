
#include "Lua.h"

np::miscela::Lua::Lua(){
    loaded = false;

	//lua.init(true); // true because we want to stop on an error
	    
	lua.addListener(this);
    before = 0.0f;
    speed = 1.0f;
    
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    parameters.add( control );
    parameters.add( position );
    parameters.add( colorA );
    parameters.add( colorB );
    
    clock = 0.0f;
    
}

np::miscela::Lua::~Lua(){
    if(loaded){
        lua.scriptExit();
    }    
    lua.clear();
    
}

void np::miscela::Lua::reload(){
    if(loaded){
        lua.scriptExit();
    }
    lua.init(true);
    lua.doScript( filepath, true);
    lua.scriptSetup();
    loaded = true;
    before = ofGetElapsedTimef();
    
    filename = ofFilePath::getFileName( filepath ); 
}
    
void np::miscela::Lua::draw( ofFbo & fbo ){
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;

    lua.setNumber( "clock", (lua_Number) clock );
    lua.setNumber( "width", (lua_Number) fbo.getWidth() );
    lua.setNumber( "height", (lua_Number) fbo.getHeight() );
    lua.setNumber( "control", (lua_Number) control );
    lua.setNumber( "modulation", (lua_Number) modulation );
    lua.setNumber( "position_x", (lua_Number) position.get().x * fbo.getWidth() );
    lua.setNumber( "position_y", (lua_Number) position.get().y * fbo.getHeight() );
    lua.setNumber( "position_z", (lua_Number) position.get().z );

    fbo.begin();
        lua.scriptUpdate();
        lua.scriptDraw();
    fbo.end();

}

void np::miscela::Lua::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
