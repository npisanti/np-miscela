
#pragma once

#include "ofMain.h"

namespace np{ namespace miscela {
    
class SandBox{

public:
    SandBox();

    ofParameter<float> control;
    ofParameter<glm::vec3> position;
    ofParameter<ofColor> colorA;
    ofParameter<ofColor> colorB;
    ofParameter<float> modulation;
    
};
    
    
}}
