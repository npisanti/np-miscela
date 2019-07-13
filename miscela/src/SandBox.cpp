
#include "SandBox.h"

np::miscela::SandBox::SandBox(){
    
    controlX.set("control X", 0.5f, 0.0f, 1.0f );
    controlY.set("control Y", 0.5f, 0.0f, 1.0f );
    buttonA.set( "button A", false );
    buttonB.set( "button B", false );

    colorA.set("color A", ofColor(255), ofColor(0), ofColor(255) );
    colorB.set("color B", ofColor(120), ofColor(0), ofColor(255) );
    
    modulation = 0.0f;
}
