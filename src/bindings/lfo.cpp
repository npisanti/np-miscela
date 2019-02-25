
#include "lfo.h"

namespace lfo{
    double playhead;
    double _ipart;
    
    void setPlayHead( double value ){
        playhead = value;
    }
     
    double triangle( double speed ){
        return abs( (modf(playhead*speed, &_ipart) * 2.0) - 1.0 );
    }
    
    double ramp( double speed ){
        return modf(playhead*speed, &_ipart);
    }
    
    double saw( double speed ){
        return 1.0f - modf(playhead*speed, &_ipart);
    }
    
    double sine( double speed ){
        return (sin(playhead*speed*TWO_PI)*0.5 + 0.5);
    }
    
    double pulse( double speed, double width ){
        double phase = modf(playhead*speed, &_ipart);
        double value = ( phase<width ) ? 1.0 : 0.0;
        return value;
    }
    
    double square( double speed ){
        double phase = modf(playhead*speed, &_ipart);
        double value = ( phase<0.5 ) ? 1.0 : 0.0;
        return value;
    }
    

    double triangle( double speed, double phase ){
        double value = triangle( speed );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
    
    double ramp( double speed, double phase ){
        double value = triangle( speed );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
    
    double saw( double speed, double phase ){
        double value = saw( speed );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
    
    double sine( double speed, double phase ){
        double value = sine( speed );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
    
    double pulse( double speed, double width, double phase ){
        double value = pulse( speed, width );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
    
    double square( double speed, double phase ){
        double value = square( speed );
        value += phase;
        double rebound = value - 1.0;
        if( value >= 1.0 ){ value = rebound; }
        return value;
    }
}
