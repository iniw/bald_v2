#pragma once

struct easing {

	// https://github.com/nicolausYes/easing-functions

	inline float in_cubic( float x ) {

		return x * x * x;

	}

	inline float out_quint( float t ) {

		const float t2 = ( --t ) * t;
		return 1 + t * t2 * t2;

	}

};

inline easing g_easing;