
#include "Lua.h"

#include "bindings/mg.h"
#include "bindings/lfo.h"

extern "C" {
	int luaopen_mg(lua_State* L);
    int luaopen_lfo(lua_State* L);
}


int np::miscela::Lua::constructed = 0;

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
    
    if( constructed==0 ){
        mg::init();
    }
    
    constructed++;
}

np::miscela::Lua::~Lua(){
    if(loaded){
        lua.scriptExit();
    }    
    lua.clear();
    
    constructed--;
    if(constructed==0){
        mg::exit();
    }
}

void np::miscela::Lua::reload(){
    if(loaded){
        lua.scriptExit();
    }
    lua.init(true);
    luaopen_mg(lua); 
    luaopen_lfo(lua); 
    lua.doScript( filepath, true);
    lua.scriptSetup();
    loaded = true;
    before = ofGetElapsedTimef();
    
    filename = ofFilePath::getFileName( filepath ); 
}
    
void np::miscela::Lua::draw( ofFbo & fbo ){
    
    aspect = float( fbo.getWidth() ) / float( fbo.getHeight() );
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
    lfo::setPlayHead( clock );
        
    //lua.setNumber( "time", (lua_Number) clock );
    lua.setNumber( "width", (lua_Number) fbo.getWidth() );
    lua.setNumber( "height", (lua_Number) fbo.getHeight() );
    lua.setNumber( "control", (lua_Number) control );
    lua.setNumber( "modulation", (lua_Number) modulation );
    lua.setNumber( "position_x", (lua_Number) position.get().x * aspect );
    lua.setNumber( "position_y", (lua_Number) position.get().y );
    lua.setNumber( "position_z", (lua_Number) position.get().z );

    mg::setColorA( colorA.get().r, colorA.get().g, colorA.get().b );
    mg::setColorB( colorB.get().r, colorB.get().g, colorB.get().b );
    
    fbo.begin();
        ofSetColor(255);
        mg::beginFrame( fbo.getWidth(), fbo.getHeight() );
        lua.scriptUpdate();
        lua.scriptDraw();
        mg::endFrame();
    fbo.end();

}

void np::miscela::Lua::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
