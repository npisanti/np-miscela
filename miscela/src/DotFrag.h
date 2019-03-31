
#pragma once
#include "ofMain.h"

#include "dotfrag/Live.h"
#include "SandBox.h"

namespace np { namespace miscela {

class DotFrag : public SandBox, public ofx::dotfrag::Live {

public:

    DotFrag(){
        timewarp();
        pingpong();
        uniform( controlA, "u_control_a" );
        uniform( controlB, "u_control_b" );
        uniform( buttonA, "u_button_a" );
        uniform( buttonB, "u_button_b" );
        uniform( position, "u_position" );
        uniform( colorA, "u_color_a" );
        uniform( colorB, "u_color_b" );
        uniform( modulation.set("modulation", 0.0f, 0.0f, 1.0f), "u_modulation" );
    }
    
};

}} // end namespaces
