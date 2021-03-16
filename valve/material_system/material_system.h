#pragma once

#include "material.h"

struct material_system {

	inline auto find_material( char const* material_name, const char* texture_group_name, bool complain = true, const char* complain_prefix = 0 ) {

		return g_utils.call_v_func< material* >( this, 84, material_name, texture_group_name, complain, complain_prefix );

	}

};