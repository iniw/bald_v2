#pragma once

#include "../../other/math/vec_3.h"

struct debug_overlay {

	inline auto screen_position( const vec_3& point, vec_3& screen ) {

		return g_utils.call_v_func< int, const vec_3&, vec_3& >( this, 13, point, screen );

	}

};