#pragma once

struct color {

	color( ) : r( 0 ), g( 0 ), b( 0 ), a( 0 ) { }

	color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 ) : r( r ), g( g ), b( b ), a( a ) { }

	unsigned char r, g, b, a;

};