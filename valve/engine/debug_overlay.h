#pragma once

#include "../../other/math/datatypes/vec_3.h"
#include "../../other/color/color.h"

struct debug_overlay {

	inline auto screen_position( const vec_3& point, vec_3& screen ) {

		return g_utils.call_v_func< int, const vec_3&, vec_3& >( this, 13, point, screen );

	}

	inline auto draw_pill( const vec_3& mins, const vec_3& maxs, float& diameter, const color& color, float duration ) {

		return g_utils.call_v_func< void, const vec_3&, const vec_3&, float&, int, int, int, int, float, int, int >( this, 23, mins, maxs, diameter, color.r, color.g, color.b, color.a, duration, 0, 0 );

	}

};