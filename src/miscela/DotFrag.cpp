
#include "DotFrag.h"
#include <boost/filesystem.hpp>

int np::miscela::DotFrag::constructed = 0;
const float np::miscela::DotFrag::cMult = 1.0f / 255.0f;

np::miscela::DotFrag::DotFrag() {
    
    vertexSrc.str(std::string());
#ifdef __ARM_ARCH
    vertexSrc  << "attribute vec4 position;\n";
    vertexSrc  << "attribute vec2 texcoord;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "varying vec2 st;\n";
    vertexSrc  << "uniform mat4 modelViewProjectionMatrix;\n";
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\tgl_Position = modelViewProjectionMatrix * position;\n";
    vertexSrc  << "\ttexcoord0 = texcoord;\n";
    vertexSrc  << "\tst = texcoord0/u_resolution.xy;\n";
    vertexSrc  << "}\n";
#else
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "varying vec2 st;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\ttexcoord0 = gl_Vertex.xy;\n";
    vertexSrc  << "\tst = texcoord0/u_resolution.xy;\n";
    vertexSrc  << "\tgl_Position = ftransform();\n";
    vertexSrc  << "}\n";
#endif

    bIndex = 0;
    bPingPong = false;
    buffers.resize(1);

    uniforms.reserve(12);

    ofDisableArbTex();
    if(constructed==0){
        ofLogNotice()<<"[np::miscela::DotFrag] disabling ARB textures for shaders\n";
    } 
    constructed++;

    fullname = ".frag";
    
    parameters.add( active.set("active", true) );

    bTimeWarp = false;

    clock = 0.0f;
    before = 0.0f;
    filepath = "";
    
    // ----------- miscela dotfrag ---------------------
    timewarp();
    pingpong();
    uniform( control, "u_control" );
    uniform( position, "u_position" );
    uniform( colorA, "u_color_a" );
    uniform( colorB, "u_color_b" );
    uniform( modulation.set("modulation", 0.0f, 0.0f, 1.0f), "u_modulation" );
}

void np::miscela::DotFrag::updateUniforms( float w, float h ){

    if( bTimeWarp ){
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        shader.setUniform1f( "u_time", clock );
    }else{
        shader.setUniform1f( "u_time", ofGetElapsedTimef() );
    }

    shader.setUniform2f( "u_resolution", w, h );

    for( size_t i=0; i<uniforms.size(); ++i ){
        switch( uniforms[i].type ){
            case 0:
                shader.setUniform1f( uniforms[i].name, *(uniforms[i].fp) );
            break;

            case 1:
                shader.setUniform1i( uniforms[i].name, *(uniforms[i].ip) );
            break;

            case 2: // bool can be used as shaders
                if( *(uniforms[i].bp) ){
                    shader.setUniform1f( uniforms[i].name, 1.0f );
                }else{
                    shader.setUniform1f( uniforms[i].name, 0.0f );
                }

            break;

            case 3:
                shader.setUniform3f( uniforms[i].name, uniforms[i].cp->get().r*cMult, uniforms[i].cp->get().g*cMult, uniforms[i].cp->get().b*cMult );
            break;

            case 4:
                shader.setUniform2f( uniforms[i].name, uniforms[i].v2p->get().x, uniforms[i].v2p->get().y );
            break;
            
            case 5:
                shader.setUniform3f( uniforms[i].name, uniforms[i].v3p->get().x, uniforms[i].v3p->get().y, uniforms[i].v3p->get().z );
            break;

            case 6:
                shader.setUniform4f( uniforms[i].name, uniforms[i].v4p->get()[0], uniforms[i].v4p->get()[1], uniforms[i].v4p->get()[2], uniforms[i].v4p->get()[3] );
            break;
        }
    }
}

void np::miscela::DotFrag::pingpong(){
    buffers.resize( 2 );
    bPingPong = true;
}

void np::miscela::DotFrag::timewarp(){
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    bTimeWarp = true;
}

void np::miscela::DotFrag::uniform( ofParameter<float> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 0;
    uniforms.back().fp = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<int> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 1;
    uniforms.back().ip = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<bool> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 2;
    uniforms.back().bp = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<ofColor> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 3;
    uniforms.back().cp = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec2> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 4;
    uniforms.back().v2p = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec3> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 5;
    uniforms.back().v3p = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec4> & param, std::string uniformName, bool addToParameters ){
    if( addToParameters ) parameters.add( param );
    uniforms.emplace_back();
    uniforms.back().name = uniformName;
    uniforms.back().type = 6;
    uniforms.back().v4p = &param;
}

void np::miscela::DotFrag::uniform( ofParameter<float> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<bool> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<int> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<ofColor> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec2> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec3> & param ){
    uniform( param, param.getName() );
}

void np::miscela::DotFrag::uniform( ofParameter<glm::vec4> & param ){
    uniform( param, param.getName() );
}


const std::string & np::miscela::DotFrag::path() const{
    return filepath;
}

void np::miscela::DotFrag::reload(){
    if( filepath!="" ){
        shader.setupShaderFromSource( GL_VERTEX_SHADER, vertexSrc.str() );
        shader.setupShaderFromFile( GL_FRAGMENT_SHADER, filepath );
        shader.bindDefaults();
        shader.linkProgram();
    }
}

void np::miscela::DotFrag::source( std::string sourcestring ){
    shader.setupShaderFromSource( GL_VERTEX_SHADER, vertexSrc.str() );
    shader.setupShaderFromSource( GL_FRAGMENT_SHADER, sourcestring );
    shader.bindDefaults();
    shader.linkProgram();
}

void np::miscela::DotFrag::stop(){
    speed = 0.0f;
    clock = 0.0f;
}

void np::miscela::DotFrag::pause(){
    speed = 0.0f;
}

void np::miscela::DotFrag::play( float speed ){
    this->speed = speed;
}

void np::miscela::DotFrag::update( ofFbo & fbo ) {

    allocate( fbo );

    buffers[bIndex].begin();
        ofClear(0,0,0,0);
        if(active){
            draw( fbo );
        }else{
            fbo.draw(0,0);
        }
    buffers[bIndex].end();

    if(bPingPong){
        bIndex++;
        if(bIndex>=buffers.size()) bIndex = 0;
    }
}

void np::miscela::DotFrag::draw( ofFbo & fbo  ){
    shader.begin();
    updateUniforms( fbo.getWidth(), fbo.getHeight() );
    shader.setUniformTexture("u_tex0", fbo.getTexture(), fbo.getTexture().getTextureData().textureID );
    if(bPingPong){
        int dIndex = (bIndex == 0 ) ? 1 : 0;
        shader.setUniformTexture("u_tex1", buffers[dIndex].getTexture(), buffers[dIndex].getTexture().getTextureData().textureID );
    }
    ofSetColor(255, 255, 255, 255);
    ofFill();
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight() );
    shader.end();
}

void np::miscela::DotFrag::apply( ofFbo & fbo ){
    if(active){
        
        ofPushStyle();
        ofDisableAlphaBlending();

        update( fbo );

        fbo.begin();
            ofClear(0,0,0,0);
            ofSetColor(255, 255, 255, 255);
            int now = bIndex-1;
            if(now<0) now+=buffers.size();
            buffers[now].draw(0,0);
        fbo.end();

        
        ofPopStyle();
    }
}

void np::miscela::DotFrag::allocate( ofFbo & fbo ) {
    allocate( fbo.getWidth(), fbo.getHeight() );
}

void np::miscela::DotFrag::allocate( int w, int h ) {
    for(size_t i=0; i<buffers.size(); ++i ){
        if( buffers[i].getWidth()!=w || buffers[i].getHeight()!=h ){
            buffers[i].allocate( w, h );
            buffers[i].begin();
                ofClear(0, 0, 0, 0);
            buffers[i].end();
            ofLogVerbose() <<"["<<fullname<<"] allocating buffer "<<i<<"\n";
        }
    }
}

void np::miscela::DotFrag::flush(){
    for(size_t i=0; i<buffers.size(); ++i ){
        buffers[i].begin();
            ofClear( 0, 0, 0, 0 );
        buffers[i].end();
    }
}


ofParameterGroup & np::miscela::DotFrag::label( std::string name ){
    parameters.setName( name );
    return parameters;
}

