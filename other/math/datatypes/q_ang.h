#pragma once

#include <cmath>
#include <algorithm>

struct q_ang {

	q_ang( float pitch = 0.f, float yaw = 0.f, float roll = 0.f ) : pitch( pitch ), yaw( yaw ), roll( roll ) { }

	q_ang( const float* arr ) : pitch( arr[ 0 ] ), yaw( arr[ 1 ] ), roll( arr[ 2 ] ) { }

	inline q_ang operator+( const q_ang& a ) const {

		return q_ang( pitch + a.pitch, yaw + a.yaw, roll + a.roll );

	}

	inline q_ang operator-( const q_ang& a ) const {

		return q_ang( pitch - a.pitch, yaw - a.yaw, roll - a.roll );

	}

	inline q_ang operator*( const float& a ) const {

		return q_ang( pitch * a, yaw * a, roll * a );

	}

	inline void init( float pitch = 0.f, float yaw = 0.f, float roll = 0.f ) {

		this->pitch = pitch; this->yaw = yaw; this->roll = roll;

	}

	inline float length( ) const {

		return std::sqrtf( std::powf( pitch, 2 ) + std::powf( yaw, 2 ) + std::powf( roll, 2 ) );

	}

	inline float length_sqr( ) const {

		return std::powf( pitch, 2 ) + std::powf( yaw, 2 ) + std::powf( roll, 2 );

	}

	inline float dot( const q_ang& dot ) const {

		return pitch * dot.pitch + yaw * dot.yaw + roll * dot.roll;

	}

	inline q_ang normalize( ) {

		pitch = std::isfinite( pitch ) ? std::remainderf( pitch, 360.f ) : 0.f;
		yaw   = std::isfinite( yaw ) ? std::remainderf( yaw, 360.f ) : 0.f;
		roll  = std::clamp( roll, -50.f, 50.f );

		return *this;

	}

	inline void clamp( ) {

		pitch = std::clamp( pitch, -89.f, 89.f );
		yaw   = std::clamp( yaw, -180.f, 180.f );
		roll  = std::clamp( roll, -50.f, 50.f );

	}

	inline q_ang sanitize( ) {

		this->normalize( );
		this->clamp( );

		return *this;
	}

	float pitch, yaw, roll;

};