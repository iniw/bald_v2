#pragma once

#include "mathlib_base.h"

#include "../../other/math/datatypes/vec_3.h"

#include <algorithm>

struct mathlib {

	inline float simple_spline( float value ) {

		float squared_value = value * value;

		return ( 3 * squared_value - 2 * squared_value * value );

	}

	inline float simple_spline_remap_val_clamped( float val, float a, float b, float c, float d ) {

		if ( a == b )
			return val >= b ? d : c;

		float clamped_value = ( val - a ) / ( b - a );
		clamped_value = std::clamp( clamped_value, 0.f, 1.f );
		return c + ( d - c ) * simple_spline( clamped_value );

	}

	inline float lerp( float percent, float a, float b ) {

		return a + ( b - a ) * percent;

	};

	inline vec_3 approach( vec_3 target, vec_3 value, float speed ) {

		vec_3 diff = ( target - value );

		float m_delta = diff.length( );
		if ( m_delta > speed )
			value += diff.normalized( ) * speed;
		else if ( m_delta < -speed )
			value -= diff.normalized( ) * speed;
		else
			value = target;

		return value;

	}

	inline float approach( float target, float value, float speed ) {

		float m_delta = target - value;

		if ( m_delta > speed )
			value += speed;
		else if ( m_delta < -speed )
			value -= speed;
		else
			value = target;

		return value;

	}

};

inline mathlib g_mathlib;