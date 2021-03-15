#pragma once

struct localize {

	inline auto find( char const* token_name ) {

		return g_utils.call_v_func< wchar_t* >( this, 11, token_name );

	}

};