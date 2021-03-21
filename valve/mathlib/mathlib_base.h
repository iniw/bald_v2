#pragma once

#include <corecrt_math.h>

struct mathlib_base {

	inline float anglemod( float a ) {

		// c casting :)
		a = ( 360.f / 65536 ) * ( ( int )( a * ( 65536.f / 360.f ) ) & 65535 );

		// references? lol cmon valve
		return a;

	}

	inline float angle_normalize( float angle ) {

		return std::remainderf( angle, 360.f );

	}

	inline float approach_angle( float target, float value, float speed ) {

		target = anglemod( target );
		value = anglemod( value );

		float m_delta = angle_normalize( target - value );

		if ( speed < 0 )
			speed = -speed;

		if ( m_delta > speed )
			value += speed;
		else if ( m_delta < -speed )
			value -= speed;
		else
			value = target;

		return value;
	}

	inline float angle_diff( float dest, float source ) {

		float m_delta = std::fmodf( dest - source, 360.f );

		if ( dest > source ) {

			if ( m_delta >= 180 )
				m_delta -= 360;

		} else {

			if ( m_delta <= -180 )
				m_delta += 360;

		}

		return m_delta;

	}

	inline float bias( float x, float bias_amt ) {

		return std::pow( x, std::log( bias_amt ) * -1.4427 );

	}

};

inline mathlib_base g_mathlib_base;