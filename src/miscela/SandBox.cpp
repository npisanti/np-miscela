
#include "SandBox.h"

np::miscela::SandBox::SandBox(){
    control.set("control", 0.5f, 0.0f, 1.0f );
    position.set("position", glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
    colorA.set("color A", ofColor(255), ofColor(0), ofColor(255) );
    colorB.set("color B", ofColor(120), ofColor(0), ofColor(255) );
    
    modulation = 0.0f;
}


void np::miscela::SandBox::setBoundaries( const ofRectangle & box ){
    boundaries = box;
    onResize( boundaries.width, boundaries.height );
}

void np::miscela::SandBox::move( float x, float y ){
    boundaries.x = x;
    boundaries.y = y;
}

void np::miscela::SandBox::resize( float w, float h ){
    boundaries.width = w;
    boundaries.height = w;    
    onResize( boundaries.width, boundaries.height );
}
