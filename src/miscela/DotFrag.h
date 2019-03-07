
#pragma once
#include "ofMain.h"

#ifndef OFXDOTFRAGSOURCE
#define OFXDOTFRAGSOURCE(...) OFXDOTFRAGSOURCE_AUX(__VA_ARGS__)
#define OFXDOTFRAGSOURCE_AUX(...) #__VA_ARGS__
#endif

#ifdef __ARM_ARCH
    #ifndef GL_ES
        #define GL_ES
    #endif
#endif

#include "SandBox.h"
#include "FileWatcher.h"

namespace np { namespace miscela {

class DotFrag : public SandBox, public FileWatcher {

private:
    struct UniformPointer;

public:

    DotFrag();

    void allocate( ofFbo & fbo ); // you don't need this if you don't use apply()

    void allocate( int w, int h );

    void source( std::string sourcestring );

    void apply( ofFbo & fbo ); // apply shader to fbo, automatic allocation if fbo size changes

    ofParameter<bool>  active;
    ofParameter<float> speed;

    void flush(); // clears all the buffers
    
    void stop();
    void pause();
    void play( float speed=1.0f );

    ofParameterGroup & label( std::string name );


    const std::string & path() const;

    void uniform( ofParameter<float> & param );
    void uniform( ofParameter<int> & param );
    void uniform( ofParameter<bool> & param );
    void uniform( ofParameter<ofColor> & param );
    void uniform( ofParameter<glm::vec2> & param );
    void uniform( ofParameter<glm::vec3> & param );
    void uniform( ofParameter<glm::vec4> & param );

    void uniform( ofParameter<float> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<int> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<bool> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<ofColor> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec2> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec3> & param, std::string uniformName, bool addToParameters=true );
    void uniform( ofParameter<glm::vec4> & param, std::string uniformName, bool addToParameters=true );
    
protected:
    // access to shader
    ofShader        shader;

    void reload() override;

private:
    void pingpong(); // ping pong buffer using u_tex1 for old frame
    void timewarp(); // add controls for playback speed of u_time

    void updateUniforms( float w, float h );

    void buffersize( int num );
    void update( ofFbo & fbo ); // update, use for processing fbos

    void draw( ofFbo & fbo  );

    unsigned int    bIndex;
    std::vector<ofFbo>  	buffers;

    static int      constructed;

    std::vector<UniformPointer> uniforms;

    float before;
    float clock;

    static const float cMult;
    bool bTimeWarp;

    bool bPingPong;

    std::string fullname;
    std::stringstream vertexSrc;

    struct UniformPointer{
        UniformPointer(){
            type = -1;
            name = "";
            fp = nullptr;
            cp = nullptr;
            ip = nullptr;
            cp = nullptr;
            v2p = nullptr;
            v3p = nullptr;
            v4p = nullptr;
        }
        int type;
        std::string name;
        ofParameter<float> *    fp;
        ofParameter<int> *      ip;
        ofParameter<bool> *     bp;
        ofParameter<ofColor> *  cp;
        ofParameter<glm::vec2> *  v2p;
        ofParameter<glm::vec3> *  v3p;
        ofParameter<glm::vec4> *  v4p;
    };

    
};

}} // end namespaces
