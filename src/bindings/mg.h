
#pragma once

#include <iostream>
#include "ofMain.h"
#include "nanovg/src/nanovg.h"

namespace mg {

    void size( int w, int h );
    void clear();
    void background( int r, int g, int b, int a );
    void fade( int speed );

    void stroke( int r, int g, int b, int a );
    void strokeA( int alpha=255 );
    void strokeB( int alpha=255 );
    void stroke( int white );
    void stroke( int white, int alpha );
    void stroke();
    
    void fill( int r, int g, int b, int a );
    void fill();
    void fillA( int alpha=255 );
    void fillB( int alpha=255 );
    void fill( int white );
    void fill( int white, int alpha );
    
    void holes();
    
    void strokeWidth( double width );
    
    void setCapButt();
    void setCapRound();
    void setCapSquare();

    void setJoinMiter();
    void setJoinRound();
    void setJoinBevel();
    
    void circle( double x, double y, double radius );
	void arc( double cx, double cy, double r, double a0, double a1, int dir=1);
	void rect( double x, double y, double w, double h );
    void rect( double x, double y, double w, double h, double r );
	void ellipse( double cx, double cy, double rx, double ry );

    void poly( double cx, double cy, double radius, int N, double theta=-M_PI_2 );

    void begin();
    void close();
    
	void moveTo( double x, double y );
	void lineTo( double x, double y );
	void bezierTo( double c1x, double c1y, double c2x, double c2y, double x, double y );
	void arcTo( double x1, double y1, double x2, double y2, double radius );
    
    double map( double input, double inmin, double inmax, double outmin, double outmax );
    
    double random();
    double random( double max );
    double random( double min, double max );
    
    double noise( double x, double y );
    double noise( double x, double y, double z );
    double noise( double x, double y, double z, double w );
    bool chance( double value );

    void push();
    void pop();
    void reset();
    void translate( double x, double y );
    void rotate( double rad );
    void scale( double x, double y );
    double ratio();
    void center(); // translate to center
    

    // ---------- used from np::miscela::Lua ------------

    void init();
    void exit();
    void beginFrame( int width, int height );
    void endFrame();
    void setColorA( int r, int g, int b );
    void setColorB( int r, int g, int b );
}
