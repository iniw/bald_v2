#pragma once

struct studio_render_context {

	inline auto set_colour_modulation( float const* color ) {

		return g_utils.call_v_func< void >( this, 27, color );

	}

	inline auto set_alpha_modulation( float alpha ) {

		return g_utils.call_v_func< void >( this, 28, alpha );

	}

};