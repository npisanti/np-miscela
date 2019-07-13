
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
        uniform( controlX, "u_control_x" );
        uniform( controlY, "u_control_y" );
        uniform( buttonA, "u_button_a" );
        uniform( buttonB, "u_button_b" );
        uniform( colorA, "u_color_a" );
        uniform( colorB, "u_color_b" );
        uniform( modulation.set("modulation", 0.0f, 0.0f, 1.0f), "u_modulation" );
    }
    
};

}} // end namespaces
