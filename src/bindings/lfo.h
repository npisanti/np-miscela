
#pragma once

#include <iostream>
#include "ofMain.h"

namespace lfo{
    
    void setPlayHead( double value );
     
    double triangle( double speed );
    double ramp( double speed );
    double saw( double speed );
    double sine( double speed );
    double pulse( double speed, double width );
    double square( double speed );
    
    double triangle( double speed, double phase );
    double ramp( double speed, double phase );
    double saw( double speed, double phase );
    double sine( double speed, double phase );
    double pulse( double speed, double width, double phase );  
    double square( double speed, double phase );  
}
