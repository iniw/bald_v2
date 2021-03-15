#pragma once

struct mdl_cache {

	inline auto begin_lock( ) {

		return g_utils.call_v_func< void >( this, 33 );

	}

	inline auto end_lock( ) {

		return g_utils.call_v_func< void >( this, 34 );

	}

};