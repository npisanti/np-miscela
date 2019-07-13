
#pragma once

#include "ofMain.h"

namespace np{ namespace miscela {
    
class SandBox{

public:
    SandBox();

    ofParameter<float> controlX;
    ofParameter<float> controlY;
    ofParameter<bool> buttonA;
    ofParameter<bool> buttonB;

    ofParameter<ofColor> colorA;
    ofParameter<ofColor> colorB;
    ofParameter<float> modulation;
    
};
    
    
}}
