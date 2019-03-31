
#pragma once

#include "ofMain.h"

namespace np{ namespace miscela {
    
class SandBox{

public:
    SandBox();

    ofParameter<float> controlA;
    ofParameter<float> controlB;
    ofParameter<bool> buttonA;
    ofParameter<bool> buttonB;
    
    ofParameter<glm::vec3> position;
    ofParameter<ofColor> colorA;
    ofParameter<ofColor> colorB;
    ofParameter<float> modulation;
    
};
    
    
}}
