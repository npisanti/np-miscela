
#pragma once

#include "ofMain.h"
#include "ofxDotFrag.h"
#include "SandBox.h"

namespace np{ namespace miscela {
    
class DotFrag : public ofx::dotfrag::Live, public SandBox {
    
public:
    DotFrag(){
        timewarp();
        pingpong();
        uniform( control, "u_control" );
        uniform( position, "u_position" );
        uniform( colorA, "u_color_a" );
        uniform( colorB, "u_color_b" );
        uniform( modulation.set("modulation", 0.0f, 0.0f, 1.0f), "u_modulation" );
    }
    
};
    
}}
