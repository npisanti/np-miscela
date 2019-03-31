
#include "SandBox.h"

np::miscela::SandBox::SandBox(){
    
    controlA.set("control A", 0.5f, 0.0f, 1.0f );
    controlB.set("control B", 0.5f, 0.0f, 1.0f );
    buttonA.set( "button A", false );
    buttonB.set( "button B", false );
    
    position.set("position", glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
    colorA.set("color A", ofColor(255), ofColor(0), ofColor(255) );
    colorB.set("color B", ofColor(120), ofColor(0), ofColor(255) );
    
    modulation = 0.0f;
}
